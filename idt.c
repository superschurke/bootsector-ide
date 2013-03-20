#include "idt.h"
#include "super.h"

struct idt_descriptor *idt = (struct idt_descriptor *)MEM_LAYOUT_IDT;
/*
VISIBLE
void int_handler()
{
__asm__(
	"pusha\n"
	"mov $0x55, %cl\n\t"
	"call *0\n\t"
	"popa\n\t"
	"iret\n"
	);
}*/


void idt_init()
{
	struct idtr idtr = { 256 * 8 - 1, MEM_LAYOUT_IDT };

	__asm__("lidt %[idtr]\n\t" :: [idtr] "m"(idtr));

	unsigned int* stub = (unsigned int*)(MEM_LAYOUT_INT_STUBS);
	unsigned long long* idt2 = (unsigned long long*)idt; //((unsigned int*)(((unsigned char*)idt) + 2));
//	struct { unsigned int o : 16, s : 16; unsigned int f : 16, o2 : 16; } *idt2 = idt;
	int i;
	for (i = 0; i < 256; i++) {
		idt2[i] = (((unsigned int)stub) & 0xffff) | (0x0008 << 16) | ((unsigned long long)IDT_INTERRUPT_GATE << 32) | ((((unsigned int)stub) & 0xffff0000ull) << 48) ;
/*		idt2[i].o = ((unsigned int)stub) & 0xffff;
		idt2[i].s = 0x0008;
		idt2[i].f = IDT_INTERRUPT_GATE;
		idt2[i].o2 = ((unsigned int)stub) >> 16;*/
		*stub++ = 0x15ff6090; // nop, pusha, call indirect
		*stub++ = MEM_LAYOUT_VECTOR_TABLE + i * 4;
		*stub++ = 0xcf61; // popa, iret
	}
}
