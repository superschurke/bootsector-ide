#TOOLCHAIN_PREFIX = i586-elf-

CC = $(TOOLCHAIN_PREFIX)gcc
LD = $(TOOLCHAIN_PREFIX)ld
OBJCOPY = $(TOOLCHAIN_PREFIX)objcopy
OBJDUMP = $(TOOLCHAIN_PREFIX)objdump

CFLAGS = -fomit-frame-pointer -Os -nostdlib -m32 -flto

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: supersch

supersch: supersch.o
	$(OBJDUMP) -d $< > $@.asm
	$(OBJCOPY) -O binary $< $@

supersch.o: $(OBJS)
	$(CC) $(CFLAGS) -T link.ld -Wl,-Map=supersch.map -Wl,-melf_i386 -o $@ $(filter boot.c,$+) $(filter-out boot.c,$+)

clean:
	rm -rf supersch supersch.o $(OBJS) supersch.asm supersch.map

