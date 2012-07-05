#include <cpu.h>

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.
#include <machine.h>
#include <alarm.h>
#include <uart.h>
#include <mach/atmega128/uart.h>
#include <mach/atmega128/int_uart.h>
#include <tsg/tsg.h>

__USING_SYS

//Testando interrução!
//volatile unsigned char receiveChar;
//
//static void rxIntHandler(void)
//{
//    receiveChar = CPU::in8(Machine::IO::UDR0);
//    CPU::out8(Machine::IO::UDR0, receiveChar);
//    leds_off(1 << 2);
//}
//
//int main(void)
//{
//    OStream cout;
//
//    IC::int_vector(Machine::irq2int(IC::IRQ_USART0_RXC), rxIntHandler);
//    IC::enable(IC::IRQ_USART0_RXC);
//    while(true)
//    {
//        leds_on(1 << 2);
//        Alarm::delay(100000000);
//    }
//}

int main() {
    OStream cout;
    ATMega128_TSG tsg;

    while(true) {
        if (tsg.modemAvailable()) {
            tsg.serialWrite(tsg.modemRead());
        }
        if (tsg.serialAvailable()) {
            tsg.modemWrite(tsg.serialRead());
        } 
    }
 
    return 0;
}
