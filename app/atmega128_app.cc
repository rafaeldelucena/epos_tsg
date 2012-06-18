#include <cpu.h>

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.
#include <machine.h>
#include <alarm.h>
#include <sensor.h>
#include <nic.h>
#include <mach/atmega128/uart.h>
#include <tsg/tsg.h>
__USING_SYS


int main() {
	CPU::out8(Machine::IO::DDRB, 0xff);
	CPU::out8(Machine::IO::PORTB, ~0);
	//for(int i = 0; i < 0xffff; i++);
	Alarm::delay(1000000);
	ATMega128_UART uart;
	ATMega128_TSG tsg;
	tsg.config();
	Alarm::delay(1000000);
	CPU::out8(Machine::IO::PORTB, ~0);
	while(1)
	{
		tsg.keep_alive();
		uart.put(tsg.status());
	}
	 
	return 0;
	
}
