#ifndef IDT_H
#define IDT_H

struct idtr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));


struct idt_descriptor {
	unsigned short offset;
	unsigned short selector;
	unsigned short flags;
	unsigned short offset16;
} __attribute__((packed));

#define IDT_INTERRUPT_GATE  0x8E00
#define IDT_TRAP_GATE       0x8F00
#define IDT_TASK_GATE       0x8500

#define IDT_SYSCALL         0xEE00


extern void idt_init();

#endif /* ndef IDT_H */
