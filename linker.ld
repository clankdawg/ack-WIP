ENTRY(START)
SECTIONS
{
	. = 0x100000;
	
	.text : 
	{
		code = .;
		*(.text)
		. = ALIGN(4096);
	}
	
	.data :
	{
		data = .;
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	
	.bss :
	{
		bss = .;
		*(.bss)
		. = ALIGN(4096);
	}
	
	end = .;
}