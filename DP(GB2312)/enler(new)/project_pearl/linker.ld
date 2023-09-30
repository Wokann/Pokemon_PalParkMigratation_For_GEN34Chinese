OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(_start)

SECTIONS
{
  . = 0x020164C0;
  .text       : { *(.text*) }
  .rodata     : { *(.rodata) }
  .data       : { *(.data) }
  .bss        : { *(.bss*) }
}
