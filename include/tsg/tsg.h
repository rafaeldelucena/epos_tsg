// EPOS ATMega128 TSG


#ifndef __atmega128_tsg_h
#define __atmega128_tsg_h

#include <mach/atmega128/uart.h>
#include <mach/atmega128/machine.h>
#include <mach/atmega128/config.h>
#include <mach/atmega128/nic.h>

#include <utility/ostream.h>
#include <utility/queue.h>
#include <utility/string.h>

__BEGIN_SYS


class ATMega128_TSG 
{

private:
	UART * uart;
	NIC nic;
	NIC::Address addr;
	NIC::Protocol prot;

public:
ATMega128_TSG::ATMega128_TSG()
{
	CPU::out8(Machine::IO::DDRA, 0xff);
	CPU::out8(Machine::IO::PORTA, ~0);
	uart = new ATMega128_UART();

};

ATMega128_TSG::~ATMega128_TSG()
{
	delete uart;

};
	void config(){
		CPU::out8(Machine::IO::DDRB, 0xff);
	char * vivo_lshapn = "AT-LSHAPN=\"zap.com.br\",\"vivo\",\"vivo\"";
	char * vivo_lshsrv = "AT-LSHSRV=\"200.142.130.104\",\"80\"";
	
	for(int i = 0; i < 0xffff; i++);
	for(int i = 0; i < 0xffff; i++);
	
	CPU::out8(Machine::IO::PORTB, 0x01);
	for(int i = 0; i < 0xffff; i++);
	int j = 0;
	while(vivo_lshapn[j] != '\0')
	{
		uart->put(vivo_lshapn[j]);
		j++;
	}
	j = 0;
	for(int i = 0; i < 0xffff; i++);
	for(int i = 0; i < 0xffff; i++);
	CPU::out8(Machine::IO::PORTB, 0x04);
	
	while(vivo_lshsrv[j] != '\0')
	{
		uart->put(vivo_lshsrv[j]);
		j++;
	}
	};//configuração para a vivo

	void send(char * send); //enviar pacote
	
	bool status(); //retornar o status apos um envio
	
	void keep_alive();

	
};

__END_SYS

#endif
