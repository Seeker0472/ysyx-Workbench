#include "am.h"
#include "debug.h"
#include "fs.h"
#include <proc.h>
#include <elf.h>
#include <stdint.h>


#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
#define Elf_Phdr Elf64_Phdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Sym Elf64_Sym
#else
# define Elf_Ehdr Elf32_Ehdr
#define Elf_Phdr Elf32_Phdr
#define Elf_Shdr Elf32_Shdr
#define Elf_Sym Elf32_Sym
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
#endif

// loads elf file from fs
static uintptr_t loader(PCB *pcb, const char *filename) {
  // read header
  Elf_Ehdr *hader = malloc(sizeof(Elf_Ehdr));
  int fd = fs_open(filename, 0, 0);
  assert(fs_read(fd, hader, sizeof(Elf_Ehdr)) == sizeof(Elf_Ehdr));
  // check magic number 
  assert(hader->e_ident[EI_MAG0] == ELFMAG0 &&
         hader->e_ident[EI_MAG1] == ELFMAG1 &&
         hader->e_ident[EI_MAG2] == ELFMAG2 &&
         hader->e_ident[EI_MAG3] == ELFMAG3); // check magic number of elf
  assert(hader->e_machine == EXPECT_TYPE);    // check isa
  // read phdrs
  Elf_Phdr *phdrs = malloc(sizeof(Elf_Phdr) * hader->e_phnum);
  fs_lseek(fd, hader->e_phoff, SEEK_SET);
  fs_read(fd, phdrs, sizeof(Elf_Phdr) * hader->e_phnum);
  // load segments
  for (int i = 0; i < hader->e_phnum; i++) {
    Elf_Phdr ph = phdrs[i];
    if (ph.p_type == PT_LOAD) {
      // read the data
      //  ramdisk_read((void *)ph.p_vaddr, ph.p_offset, ph.p_filesz);
      fs_lseek(fd, ph.p_offset, SEEK_SET);
      fs_read(fd, (void *)ph.p_vaddr, ph.p_filesz);
      for (char *empty = (char *)ph.p_vaddr + ph.p_filesz;
           empty < (char *)ph.p_vaddr + ph.p_memsz; empty++)
        *empty = 0;
    }
  }
  // find _end symbol maybe not the os work
  // Elf_Shdr *shdrs = (Elf_Shdr *)((char *)&ramdisk_start + hader.e_shoff);
  // Elf_Shdr *strtab = NULL;
  // Elf_Shdr *symtab = NULL;
  // for (int i = 0; i < hader.e_shnum; i++) {
  //   if (shdrs[i].sh_type == SHT_STRTAB &&
  //       i != hader.e_shstrndx) { // 排除sectionHeader的符号表
  //     strtab = &shdrs[i];
  //   }
  //   if (shdrs[i].sh_type == SHT_SYMTAB) {
  //     symtab = &shdrs[i];
  //   }
  // }
  // Elf_Sym *symbols = (Elf_Sym *)((char *)&ramdisk_start + symtab->sh_offset);
  // char *strtab_data = ((char *)&ramdisk_start + strtab->sh_offset);
  // for (int i = 0; i < symtab->sh_size /sizeof(Elf_Sym) ; i++) {
  //   // Log("%s", &strtab_data[symbols[i].st_name]);
  //   if (strcmp("_end", &strtab_data[symbols[i].st_name]) == 0) {
  //     // assert(0);
  //     // TODO!!!
  //     end_symbol =symbols[i].st_value;
  //     Log("find symbol_end:%x", symbols[i].st_value);
  //   }
	// }
  return hader->e_entry; //这里的entry就是在libos/crt0/start.S里面定义的_start 
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
// load,yeld?
// _start之后会调用call_main()，在如果要传递参数，应该把参数相关信息传递给call_main,然后由call_main传递给目标main函数
void context_uload(PCB *pcb,const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  //init an Context struct on top of stack
  pcb->cp = ucontext(
      &(AddrSpace){.area={},.pgsize=0,.ptr=0}, (Area){.start = pcb->stack, .end = pcb->stack + STACK_SIZE},
      (void *)entry);
  // pcb->cp->pdir=pcb;
  Log("About to Yield!");
  yield();//TODO:调度
  assert(0);
}
void context_kload(PCB *pcb, void *func,void *args) {
  pcb->cp = kcontext((Area){.start=pcb->stack,.end=pcb->stack+STACK_SIZE}, func, args);
}