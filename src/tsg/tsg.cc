
#include <tsg/tsg.h>

__USING_SYS;

ATMega128_TSG::ATMega128_TSG()
{
	CPU::out8(Machine::IO::DDRA, 0xff);
	CPU::out8(Machine::IO::PORTA, ~0);

}

void ATMega128_TSG::config()
{
	char *vivo_lshapn = "AT-LSHAPN=\"zap.com.br\",\"vivo\",\"vivo\"";
	char *vivo_lshsrv = "AT-LSHSRV=\"200.142.130.104\",\"80\"";
	//CPU::out8(Machine::IO::PORTA, ~count++);
	//uart.put(buff.b[1]);
	//uart.put(buff.b[0]);
	//buff.s = 0x0000;
	int i = 0;
	while(vivo_lshapn[i] != "\0")
	{
		uart.put(vivo_lshapn[i]);
		i++;
	}
	i = 0;
	while(vivo_lshsrv[i] != "\0")
	{
		uart.put(vivo_lshsrv[i]);
		i++;
	}

}

void ATMega128_TSG::send()
{

}

bool ATMega128_TSG::status()
{
return false;
}
