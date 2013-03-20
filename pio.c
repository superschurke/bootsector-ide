#include "pio.h"

void io_wait()
{
	__asm__ __volatile__("jmp 1f\n1:\tjmp 1f\n1:");
}

void outb(unsigned short port, unsigned char val)
{
	__asm__ __volatile__("outb %0, %1" : : "a" (val), "Nd" (port));
}

void outb_wait(unsigned short port, unsigned char val)
{
	outb(port, val);
	io_wait();
}

unsigned char inb(unsigned short port)
{
	unsigned char val;
	__asm__ __volatile__("inb %1, %0" : "=a" (val) : "Nd" (port));
	return val;
}

unsigned char inb_wait(unsigned short port)
{
	unsigned char val = inb(port);
	io_wait();
	return val;
}

void insl(unsigned short port, void *addr, unsigned int count)
{
	__asm__ __volatile__(
		"repne\n\t"
		"insl\n\t"
		:
		: "d"(port), "D"(addr), "c"(count)
		: "memory", "cc");
}

void outsl(unsigned short port, void *addr, unsigned int count)
{
	__asm__ __volatile__(
		"repne\n\t"
		"outsl\n\t"
		:
		: "d"(port), "S"(addr), "c"(count)
		: "cc");
}
