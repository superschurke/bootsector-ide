#ifndef INTR_H
#define INTR_H

extern void disable_interrupts();
extern void enable_interrupts();
extern void set_int_handler(unsigned int interrupt, void* func);

#endif /* ndef INTR_H */
