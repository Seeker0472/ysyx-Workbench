#include "debug.h"
// #include <assert.h>
#include <proc.h>
#include <elf.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

#if defined(__ISA_AM_NATIVE__)
#define EXPECT_TYPE EM_X86_64
#elif defined(__ISA_X86__)
#define EXPECT_TYPE EM_X86_64
#elif defined(riscv32e)
#define EXPECT_TYPE EM_RISCV
#else
#define EXPECT_TYPE EM_RISCV
// #error Unsupported ISA
//TODO!!
#endif

extern Elf_Ehdr ramdisk_start;

// 从ramdisk中`offset`偏移处的`len`字节读入到`buf`中
size_t ramdisk_read(void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {
  // TODO();
  Elf_Ehdr hader = ramdisk_start;
  Elf_Phdr *phdrs = (Elf_Phdr *)((char *)&ramdisk_start + hader.e_phoff);
  // Assert(hader.e_ident[EI_MAG0] == ELFMAG0 &&
  //        hader.e_ident[EI_MAG1] == ELFMAG1 &&
  //        hader.e_ident[EI_MAG2] == ELFMAG2 &&
  //        hader.e_ident[EI_MAG3] == ELFMAG3,"Magic Number Check Failed! Maybe
  //        not an ELF File"); // check magic number of elf
  // Assert(hader.e_machine == EXPECT_TYPE,
  //        "Elf ISA(%d) Different form os ISA:(%d)", hader.e_machine,
  //        EXPECT_TYPE); // check isa
  //
  assert(hader.e_ident[EI_MAG0] == ELFMAG0 &&
         hader.e_ident[EI_MAG1] == ELFMAG1 &&
         hader.e_ident[EI_MAG2] == ELFMAG2 &&
         hader.e_ident[EI_MAG3] == ELFMAG3); // check magic number of elf
  assert(hader.e_machine == EXPECT_TYPE); // check isa
  // printf("%x\n", &hader);
  // load program
  for (int i = 0; i < hader.e_phnum; i++) {
    Elf_Phdr ph = phdrs[i];
    if (ph.p_type == PT_LOAD) {
      ramdisk_read((void *)ph.p_vaddr, ph.p_offset, ph.p_filesz);
      for (char *empty = (char *)ph.p_vaddr + ph.p_filesz;
           empty < (char *)ph.p_vaddr + ph.p_memsz;empty++)
        *empty=0;
    }
  }
  return hader.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
