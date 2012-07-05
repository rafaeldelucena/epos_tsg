// EPOS-- ATMega128 Interrupt Driven UART Mediator Declarations

#ifndef __atmega128_int_uart_h
#define __atmega128_int_uart_h

#include "../avr_common/uart.h"

__BEGIN_SYS

class ATMega128_INT_UART: private AVR_UART
{
protected:
    static const unsigned char buffer_size = 128; // 2, 4, 8, 16, 32, 64, 128, 256
    static const unsigned char buffer_mask = 127; // buffer_size - 1
private:
    typedef IO_Map<Machine> IO;
    static unsigned char _RX_buffer[buffer_size];
    static unsigned char _TX_buffer[buffer_size];

    static unsigned char _RX_buffer_head, _RX_buffer_tail;
    static unsigned char _TX_buffer_head, _TX_buffer_tail;

public:

    static void RX_int_handler(void) {
  	if (_RX_buffer_head == ((_RX_buffer_tail + 1) & buffer_mask)) {
            IC::disable(IC::IRQ_USART0_RXC);
        } else {
	    char tmp = _RX_buffer_tail;
            _RX_buffer_tail = (_RX_buffer_tail + 1) & buffer_mask;
            _RX_buffer[tmp] = AVR8::in8(IO::UDR0);
        }
    }

    static void TX_int_handler(void) {
	if (_TX_buffer_head == _TX_buffer_tail) {
	    IC::disable(IC::IRQ_USART0_UDRE);
	} else {
	    char tmp = _TX_buffer[_TX_buffer_head];
            _TX_buffer_head = (_TX_buffer_head + 1) & buffer_mask;
            AVR8::out8(IO::UDR0, tmp);
	}
    }

    ATMega128_INT_UART(unsigned int unit = 0) : AVR_UART(9600, 8, 0, 1, unit) {
        IC::int_vector(Machine::irq2int(IC::IRQ_USART0_RXC), RX_int_handler);
        IC::int_vector(Machine::irq2int(IC::IRQ_USART0_UDRE), TX_int_handler);
        IC::enable(IC::IRQ_USART0_RXC);
        IC::enable(IC::IRQ_USART0_UDRE);
    }
    
    ATMega128_INT_UART(unsigned int baud, unsigned int data_bits,
          unsigned int parity, unsigned int stop_bits, unsigned int unit = 0)
         : AVR_UART(baud, data_bits, parity, stop_bits, unit) {
        
        IC::int_vector(Machine::irq2int(IC::IRQ_USART0_RXC), RX_int_handler);
        IC::int_vector(Machine::irq2int(IC::IRQ_USART0_UDRE), TX_int_handler);
        IC::enable(IC::IRQ_USART0_RXC);
        IC::enable(IC::IRQ_USART0_UDRE);
    }

    char get(char * byte) {
        if (_RX_buffer_head != _RX_buffer_tail) {
             *byte  = _RX_buffer[_RX_buffer_head];
            _RX_buffer_head = (_RX_buffer_head + 1) & buffer_mask;
            IC::enable(IC::IRQ_USART0_RXC);
	    return 1;
        } else {
            return 0;
        }
    }

    char put(const char c) {
	if (_TX_buffer_head == ((_TX_buffer_tail + 1) & buffer_mask)) {
	    return 0;
	} else {
            _TX_buffer[_TX_buffer_tail] = c;
            _TX_buffer_tail = (_TX_buffer_tail + 1) & buffer_mask;
            IC::enable(IC::IRQ_USART0_UDRE);
	    return 1;
	}
    }

    char available() {
        return(_RX_buffer_tail + buffer_size - _RX_buffer_head) % buffer_size;
    }
};

unsigned char ATMega128_INT_UART::_TX_buffer_head = 0, ATMega128_INT_UART::_TX_buffer_tail = 0;
unsigned char ATMega128_INT_UART::_RX_buffer_head = 0, ATMega128_INT_UART::_RX_buffer_tail = 0;

unsigned char ATMega128_INT_UART::_TX_buffer[buffer_size];
unsigned char ATMega128_INT_UART::_RX_buffer[buffer_size];

__END_SYS

#endif
