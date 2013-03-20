#include "ide.h"
#include "intr.h"
#include "irq.h"
#include "pic.h"
#include "pio.h"
#include "super.h"


#define IDE_BSY			0x80
#define IDE_DRDY		0x40
#define IDE_DF			0x20
#define IDE_ERR			0x01

#define IDE_CMD_READ  0x20
#define IDE_CMD_WRITE 0x30


int ide_wait_ready()
{
	int r;

	do {
		r = inb(0x1f7);
	} while ((r & IDE_BSY) || !(r & IDE_DRDY));

	return r & (IDE_DF | IDE_ERR);
}


volatile char* buffer;
volatile int wait;

void ide_int_handler()
{
	wait = 0;

	if (ide_wait_ready() != 0) {
		//DEBUG_PRINT("I");
		return;
	}

	insl(0x1f0, (char*)buffer, 512 / 4);

	pic_eoi(IRQ_IDE);
}

void ide_init()
{
	set_int_handler(IRQ_BASE + IRQ_IDE, ide_int_handler);
	
	//ide_wait_ready();
	outb(0x1f6, 0xe0 | (0<<4));
}

void ide_rw(unsigned int sector, unsigned int read, unsigned char* data)
{
	unsigned int device = 0;

	ide_wait_ready();
	outb(0x3f6, 0);
	outb(0x1f2, 1);
	outb(0x1f3, sector & 0xff);
	outb(0x1f4, (sector >> 8) & 0xff);
	outb(0x1f5, (sector >> 16) & 0xff);
	outb(0x1f6, 0xe0 | ((device & 1) << 4) | ((sector >> 24) & 0x0f));
	
	if (read) {
		wait = 1;
		buffer = data;
		outb(0x1f7, IDE_CMD_READ);
	} else {
		outb(0x1f7, IDE_CMD_WRITE);
		outsl(0x1f0, data, 512/4);
	}
}

void ide_read(unsigned int sector, unsigned char* buffer)
{
	ide_rw(sector, 1, buffer);
}

void ide_write(unsigned int sector, unsigned char* buffer)
{
	ide_rw(sector, 0, buffer);
}