#ifndef PIO_H
#define PIO_H

extern void outb(unsigned short port, unsigned char val);
extern void outb_wait(unsigned short port, unsigned char val);
extern unsigned char inb(unsigned short port);
extern unsigned char inb_wait(unsigned short port);
extern void insl(unsigned short port, void *addr, unsigned int count);
extern void outsl(unsigned short port, void *addr, unsigned int count);

#endif /* ndef PIO_H */
