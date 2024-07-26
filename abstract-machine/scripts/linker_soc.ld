ENTRY(_start)
/*ENTRY*/
PHDRS { text PT_LOAD; data PT_LOAD; }
MEMORY {
  mrom : ORIGIN = 0x20000000, LENGTH = 4K
  sram : ORIGIN = 0x0f000000, LENGTH = 8K
}
SECTIONS {
  . = ORIGIN(mrom);
  .text : {
    *(entry)
    *(.text*)
  } : text
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  }
  _data_section_start = .;
  .data : {
    *(.data)
  } : data
  _data_section_end = .;
  edata = .;
  _data = .;
  .bss : {
	_bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  }
  . = ORIGIN(sram);
  _data_section_dest = .;
  . +=  _data_section_end - _data_section_start;
  _stack_top = ALIGN(0x1000);
  /* _stack_top = .; */
  . = _stack_top + 0x1000;
  _stack_pointer = .;
  end = .;
  _end = .;
  _heap_start = ALIGN(0x1000);
  /* _heap_start = .; */
}
