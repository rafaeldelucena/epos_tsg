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
#include <uart.h>
#include <tsg/tsg.h>
__USING_SYS

typedef union {
	int s;
	char b[2];
} __u16;

OStream cout;
unsigned char count = 1;
int gateway()
{
	CPU::out8(Machine::IO::DDRA, 0xff);
	CPU::out8(Machine::IO::DDRB, 0xff);
	CPU::out8(Machine::IO::PORTA, ~0);
	CPU::out8(Machine::IO::PORTB, ~0);
	UART uart;
	NIC nic;
	NIC::Address addr;
	NIC::Protocol prot;
	__u16 buff;
	int data_size = 0;

	while(true)
	{
		
		CPU::out8(Machine::IO::PORTB, 0x00);
		data_size = nic.receive(&addr, &prot, buff.b, 2);
		for(int i = 0; i < 0xffff; i++);
		CPU::out8(Machine::IO::PORTB, 0x04);

		if(data_size != 2) continue;

		for(int i = 0; i < 0xffff; i++);
		CPU::out8(Machine::IO::PORTB, 0x01);

		CPU::out8(Machine::IO::PORTA, ~count++);
		uart.put(buff.b[1]);
		uart.put(buff.b[0]);
		buff.s = 0x0000;
		CPU::out8(Machine::IO::PORTB, 0x04);
	}
}

int main() {
	CPU::out8(Machine::IO::DDRB, 0xff);
	CPU::out8(Machine::IO::PORTB, 0x00);
	for(int i = 0; i < 0xffff; i++);
	return gateway();
	
}
