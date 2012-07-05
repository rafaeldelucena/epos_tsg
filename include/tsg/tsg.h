// EPOS ATMega128 TSG

#ifndef __atmega128_tsg_h
#define __atmega128_tsg_h

#include <mach/atmega128/uart.h>
#include <mach/atmega128/int_uart.h>
#include <mach/atmega128/machine.h>
#include <mach/atmega128/config.h>
#include <alarm.h>

__BEGIN_SYS


class ATMega128_TSG 
{

private:
	ATMega128_INT_UART uart0, uart1;
    
    void ledsInit(unsigned char value) {
        CPU::out8(Machine::IO::DDRB, CPU::in8(Machine::IO::DDRB) | value);
    }
    
    void ledsOn(unsigned char value)
    {
        ledsInit(value);
        CPU::out8(Machine::IO::PORTB, CPU::in8(Machine::IO::PORTB) & ~value);
    }

    void ledsOff(unsigned char value)
    {
        CPU::out8(Machine::IO::PORTB, CPU::in8(Machine::IO::PORTB) | value);
    }
    
    char* readSerial(ATMega128_INT_UART* serial)
    {
        char* str;
        while(serial->available()) {
            char* c = "";
            if(serial->get(c)) {
                strcat(str, c);
            }
        }
        return str;
    }
    
    void sendSerial(ATMega128_INT_UART* serial, char* str)
    {
        int i;
        for(i = 0; i < strlen(str); i++) {
            serial->put(str[i]);
        }
    }
    

public:
	ATMega128_TSG() : uart1(9600, 8, 0, 1, 1), uart0(9600, 8, 0, 0, 0)
	{
		CPU::out8(Machine::IO::DDRD, 0xff);
	}

	void configure()
	{
		char* lshapn = "AT-LSHAPN=\"tim.br\",\"tim\",\"tim\"";
		char* lshsrv = "AT-LSHSRV=\"150.162.10.20\",\"54231\"";
	
        sendSerialMessage(lshapn);
        Alarm::delay(1000000);
        sendSerialMessage(lshsrv);
        Alarm::delay(1000000);
    } //configuração para a vivo

	void sendModemMessage(char* str)
	{	
        ledsOn(0x04);
        sendSerial(&uart1, str);
        ledsOff(0x04);
	} //enviar pacote

    void sendSerialMessage(char* str)
    {
        ledsOn(0x01);
        sendSerial(&uart0, str);
        ledsOff(0x01);
    }

    char* readModemMessage()
    {
        return readSerial(&uart1);
    }

    char* readSerialMessage()
    {
        return readSerial(&uart0);
    }

    char modemRead()
    {
        char c;
        if (uart1.get(&c)) {
            return c;
        }
    }
    
    void modemWrite(char c)
    {
        ledsOn(0x01);
        uart1.put(c);
        ledsOff(0x01);
    }

    char serialRead()
    {
        char c;
        if(uart0.get(&c)) {
            return c;    
        } 
    }
    
    void serialWrite(char c)
    {   
        ledsOn(0x04);
        uart0.put(c);
        ledsOff(0x04);
    }
    
    void sendKeepAlive()
    {
		char * keep = "AT-LSHTEST?";
	    sendModemMessage(keep);
    }

    char modemAvailable()
    {
        return uart1.available();
    }

    char serialAvailable()
    {
        return uart0.available();
    }
    
};

__END_SYS

#endif
