#ifndef SUPER_H
#define SUPER_H

#define MEM_LAYOUT_IDT				0x8000	/* size: 0x800 */
#define MEM_LAYOUT_INT_STUBS		0x8800	/* size: 0x1000 */
#define MEM_LAYOUT_VECTOR_TABLE		0x9800	/* size: 0x400 */

#define VISIBLE			__attribute__((__externally_visible__,__used__))

extern void DEBUG_PRINT(const char *msg);

#endif /* ndef SUPER_H */
