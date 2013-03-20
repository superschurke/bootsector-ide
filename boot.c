#include "gdt.h"
#include "ide.h"
#include "idt.h"
#include "intr.h"
#include "irq.h"
#include "pic.h"
#include "pio.h"
#include "super.h"

struct {
	struct gdtr gdtr;
	struct gdt_descriptor code, data;
}
gdt =
{
	{ sizeof(gdt) - 1, &gdt },
	{ 0xffff, 0x0000, 0x00, GDT_DPL0 | GDT_CODE_SEL, 0xcf, 0x00 },
	{ 0xffff, 0x0000, 0x00, GDT_DPL0 | GDT_DATA_SEL, 0xcf, 0x00 },
};

__asm__ (".code16\n\tjmp bmain\n\t.code32");

unsigned short * video = (unsigned short *)0xb8000;

void DEBUG_PRINT(const char *msg)
{
	while (*msg) {
		*video++ = ((unsigned char)*msg++) | 0x0700;
	}
}

VISIBLE
void default_handler(void) {}
/*
VISIBLE
void timer_handler(void)
{
	DEBUG_PRINT("timer");
	pic_eoi(IRQ_TIMER);
}

VISIBLE
void keyboard_handler(void)
{
	DEBUG_PRINT("keyb");
	inb(0x60);
	pic_eoi(IRQ_KEYBOARD);
}*/

VISIBLE
void bmain(void)
{
	__asm__ __volatile__(".code16gcc\n\t");
	disable_interrupts();
	__asm__ __volatile__(
		".code16\n\t"
		"cld\n\t"
		"xor %%ax, %%ax\n\t"		/* ax = 0x00 */
		"mov %%ax, %%ds\n\t"
		"lgdt %0\n\t"
		"inc %%ax\n\t"				/* ax = 0x01 */
		"lmsw %%ax\n\t"				/* set cr0.PE */
		"mov $0x10, %%al\n\t"		/* ax = 0x10 */
		"mov %%ax, %%ds\n\t"
		"mov %%ax, %%es\n\t"
		"mov %%ax, %%ss\n\t"
		"movzx %%sp, %%esp\n\t"
		"ljmpl $0x08, $1f\n\t"
		".code32\n"
		"1:\n\t"
		:: "m" (gdt) : "eax");
	
	idt_init();
	pic_init();

	int i = 0;
	for (i = 0; i < 256; i++)
		set_int_handler(i, default_handler);

	//set_int_handler(IRQ_BASE + IRQ_TIMER, timer_handler);
	//set_int_handler(IRQ_BASE + IRQ_KEYBOARD, keyboard_handler);

	ide_init();
	enable_interrupts();

	//char buffer[512];
	ide_read(0, 0xb8200);

	while(1);
}
