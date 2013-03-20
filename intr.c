#include "intr.h"
#include "super.h"

void disable_interrupts()
{
	__asm__ __volatile__("cli");
}

void enable_interrupts()
{
	__asm__ __volatile__("sti");
}

void set_int_handler(unsigned int interrupt, void* func)
{
	((unsigned int*)MEM_LAYOUT_VECTOR_TABLE)[interrupt] = (unsigned int)func;
}
