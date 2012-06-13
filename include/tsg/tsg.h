// EPOS ATMega128 TSG


#ifndef __atmega128_tsg_h
#define __atmega128_tsg_h

#include <mach/atmega128/uart.h>
#include <mach/atmega128/machine.h>
#include <mach/atmega128/config.h>

#include <utility/ostream.h>
#include <utility/queue.h>

__BEGIN_SYS


class ATMega128_TSG 
{

public:
	ATMega128_TSG();
	void config();//configuração para a vivo

	void send(); //enviar pacote
	
	bool status(); //retornar o status apos um envio
};

__END_SYS

#endif
