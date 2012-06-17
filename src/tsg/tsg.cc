
#include <tsg/tsg.h>

__USING_SYS;


void ATMega128_TSG::send(char * send)
{
	int i = 0;
	while(send[i] != '\0')
	{
		uart->put(send[i]);
		i++;
	}
}

bool ATMega128_TSG::status()
{
	if(uart = 0)
		return false;
	else
		return uart->get();
}

bool ATMega128_TSG::keep_alive()
{
	char * keep = "AT-LSHTEST?";
	int i = 0;
	while(keep[i] != '\0')
	{
		uart->put(keep[i]);
		i++;		
	}
}
