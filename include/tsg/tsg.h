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
	ATMega128_TSG();
	~ATMega128_TSG();
	void config();//configuração para a vivo

	void send(char * send); //enviar pacote
	
	bool status(); //retornar o status apos um envio
	
	void keep_alive();

	
};

__END_SYS

#endif
