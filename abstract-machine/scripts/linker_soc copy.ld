ENTRY(_start)
/*ENTRY*/
PHDRS { bl PT_LOAD;text PT_LOAD;rodata PT_LOAD;data_ext PT_LOAD;data PT_LOAD;bss_ext PT_LOAD;bss PT_LOAD;  }
MEMORY {
  mrom  : ORIGIN = 0x20000000, LENGTH = 4K
  sram  : ORIGIN = 0x0f000000, LENGTH = 8K
  flash : ORIGIN = 0x30000000, LENGTH = 16M
  psram : ORIGIN = 0x80000000, LENGTH = 4M
}
SECTIONS {
  . = ORIGIN(flash);
  .bl : {
  . = ALIGN(4);
    *(entry)
    *(.bl)
  . = ALIGN(4);
  }> flash : bl
  _text_section_src = .;
  .text : {
  . = ALIGN(4);
  _text_section_start = .;
    *(.text*)
    *(.text.*)
  . = ALIGN(4);
  } > psram AT> flash : text
    /* . = ALIGN(0x10); */
  _etext = .;
  .rodata : {
  . = ALIGN(4);
    *(.rodata*)
    *(.rodata.*)
    *(.srodata.*)
  . = ALIGN(4);
  }> psram AT> flash : rodata
  .data.extra : {
    *(.data.extra)
  }> psram AT> flash : data_ext
  _data_section_src = LOADADDR(.data);
  .data : {
  . = ALIGN(4);
    _data_section_start = .;
    *(.data)
    *(.data.*)
    *(.sdata)
    *(.sdata.*)
  . = ALIGN(4);
    _data_section_end = .;
  }> psram AT> flash : data
  .bss.extra : {
    *(.bss.extra)
  }> psram AT> flash : bss_ext
  .bss : {
  . = ALIGN(4);
	_bss_start = .;
    *(.bss*)
    *(.bss.*)
    *(.sbss*)
    *(.scommon)
  . = ALIGN(4);
	_bss_end = .;
  }> psram AT> flash : bss
  
  _stack_top = ORIGIN(sram);
  _stack_pointer = _stack_top + LENGTH(sram);

  . = ORIGIN(psram);
  . += _bss_end - _text_section_start;
  _heap_start = ALIGN(0x10);
  _pmem_start = . ;

}
