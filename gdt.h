#ifndef GDT_H
#define GDT_H

struct gdtr {
	unsigned short limit;
	void* base;
} __attribute__((packed));

struct gdt_descriptor {
	unsigned short limit;
	unsigned short base;
	unsigned char base16;
	unsigned char access;
	unsigned char limit16;
	unsigned char base24;
} __attribute__((packed, aligned(8)));

#define GDT_CODESEG     0x0A
#define GDT_DATASEG     0x02
#define GDT_TSS         0x09
#define GDT_PRESENT     0x80
#define GDT_SEGMENT     0x10

#define GDT_DPL0        0x00
#define GDT_DPL1        0x20
#define GDT_DPL2        0x40
#define GDT_DPL3        0x60

#define GDT_CODE_SEL    (GDT_PRESENT | GDT_SEGMENT | GDT_CODESEG)
#define GDT_DATA_SEL    (GDT_PRESENT | GDT_SEGMENT | GDT_DATASEG)

#endif /* ndef GDT_H */
