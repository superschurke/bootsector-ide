SECTIONS
{
	. = 0x7c00;
	
	.boot_sector : {
		boot*(.text)
		*(.text .text.*)
		*(.data .data.*)
		*(.rdata .rdata.*)
		*(.rodata .rodata.*)
		. = 510;
	}
	.signature : {
 		BYTE(0x55)
 		BYTE(0xaa)
	}
	.bss : {
		*(.bss)
	}
	/DISCARD/ : {
		*(.eh_frame)
		*(.note.*)
		*(.comment)
	}
}
