MEMORY
{
	RAM   	(rwx): 	ORIGIN = 0x20000000,	LENGTH = 4K
	FLASH	(rx):	ORIGIN = 0x8000000,		LENGTH = 32K
}

EXTERN(vector_table);
ENTRY(reset_handler);

SECTIONS
{
	.text : {
        *(.vectors)
        *(.text*)
        . = ALIGN(4);
    } >FLASH
}
