/*
******************************************************************************
**
**  File        : LinkerScript.ld
**  Target      : STM32L073RBTx (128 KB FLASH, 20 KB RAM)
**  Features    :
**      - 120 KB for program (FLASH)
**      - 8 KB reserved for FATFS and one ROM file (STORE)
**      - Proper _end definition for sysmem.c (_sbrk)
**
******************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Memory regions */
/* DEFAULTS 
  RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 20K
  FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 128K 
*/

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 112K
    STORE (rw)  : ORIGIN = 0x0801C000, LENGTH = 16K
    RAM (rw)   : ORIGIN = 0x20000000, LENGTH = 20K
}


/* Stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Heap/Stack minimum sizes */
_Min_Heap_Size = 0x200;      /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

/* Sections */
SECTIONS
{
  /* Vector Table */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  /* Code */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  /* Read-only data */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* FATFS + ROM reserved section */
  .store (NOLOAD) :
  {
    __store_start__ = .;
    KEEP(*(.store))
    . = ALIGN(4);
    __store_end__ = .;
  } >STORE

  .ARM.extab (READONLY) :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

  .ARM (READONLY) :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* Data section */
  _sidata = LOADADDR(.data);

  .data :
  {
    _sdata = .;
    *(.data)
    *(.data*)
    *(.RamFunc)
    *(.RamFunc*)
    . = ALIGN(4);
  } >RAM AT> FLASH

  .tdata : ALIGN(4)
  {
    *(.tdata .tdata.* .gnu.linkonce.td.*)
    . = ALIGN(4);
    _edata = .;
    PROVIDE(__data_end = .);
    PROVIDE(__tdata_end = .);
  } >RAM AT> FLASH

  .tbss (NOLOAD) :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.tbss .tbss.*)
    . = ALIGN(4);
    PROVIDE(__tbss_end = .);
  } >RAM

  .bss (NOLOAD) :
  {
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
    PROVIDE(__bss_end = .);
    PROVIDE(end = .);
    PROVIDE(_end = .);
  } >RAM

  ._user_heap_stack (NOLOAD) :
  {
    . = ALIGN(8);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /DISCARD/ :
  {
    libc.a:* (*)
    libm.a:* (*)
    libgcc.a:* (*)
  }
}
