#include <common.h>
#include <debug.h>
#include <elf.h>

typedef struct node{
    paddr_t start_addr;
	size_t length;
    char name[64]; // func name
	struct node *next;
} trace_node;

trace_node* nodes;

void add_symbol(paddr_t start_addr,size_t len,char* name){//向链表中添加一项
	trace_node* tail=nodes;
	while(tail->next!=NULL)
		tail=tail->next;
	
	tail->next=malloc(sizeof(trace_node));

	Assert(tail->next,"malloc fail");//检查是否为空

	tail=tail->next;

	tail->start_addr=start_addr;
	tail->length=len;
	strncpy(tail->name,name,64);
	tail->next=NULL;
}

void read_symbol_table(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        Log("Failed to open : %s",filename);
        exit(EXIT_FAILURE);
    }

    Elf64_Ehdr header;
    if(fread(&header, 1, sizeof(header), file)!=sizeof(header))
		assert(0);

    // printf("e_phoff: %ld \n", header.e_phoff);
    // printf("e_shoff: %ld\n", header.e_shoff);//section header table's file offset in bytes.

    // printf("e_shnum: %d\n", header.e_shnum);//number of entries in the section header table.
    // printf("e_shstrndx: %d\n", header.e_shstrndx);//section header table index of the entry associated with the section name string table.

    fseek(file,header.e_shoff,SEEK_SET);
    // 读取节头表
    Elf64_Shdr *shdrs = malloc(header.e_shentsize * header.e_shnum);
    if(fread(shdrs, header.e_shentsize, header.e_shnum, file)!= header.e_shnum)
		assert(0);
	// Log("%lu-----%d",fread(shdrs, header.e_shentsize, header.e_shnum, file),header.e_shnum);
	
    Elf64_Shdr *symtab = NULL;
    Elf64_Shdr *strtab = NULL;
    //遍历，寻找SHT_STRTAB，SHT_SYMTAB
    for(int i=0;i<header.e_shnum;i++){
        if(shdrs[i].sh_type == SHT_STRTAB && i != header.e_shstrndx){//排除sectionHeader的符号表
            // printf("SHT_STRTAB\n");
            strtab = &shdrs[i];
        }

        //sectionHeader的符号表
        // if(shdrs[i].sh_type == SHT_STRTAB && i == header.e_shstrndx){
        //     printf("Section!");
        //         // Read string table
        //     Elf64_Shdr *now=&shdrs[i];
        //     char* strtab_data = malloc(now->sh_size);
        //     fseek(file, now->sh_offset, SEEK_SET);
        //     fread(strtab_data, 1, now->sh_size, file);
        //     int num = now->sh_size ;
        //     for (int i = 0; i < num; i++) {
        //         printf("%c",strtab_data[i]);
        //     }
        // }
        if(shdrs[i].sh_type==SHT_SYMTAB){
            // printf("SHT_SYMTAB\n");
            symtab = &shdrs[i];
        }
    }
    //读取Symbol
    Elf64_Sym *symbols = malloc(symtab->sh_size);
    fseek(file, symtab->sh_offset, SEEK_SET);
    if(fread(symbols, 1, symtab->sh_size, file)!=symtab->sh_size)
		assert(0);

    // 读取符号表
    char *strtab_data = malloc(strtab->sh_size);
    fseek(file, strtab->sh_offset, SEEK_SET);
    if(fread(strtab_data, 1, strtab->sh_size, file)!=strtab->sh_size)
		assert(0);

    //符号表的数量
    int num_symbols = symtab->sh_size / sizeof(Elf64_Sym);

    // printf("\nSymbols:\n");
    // for (int i = 0; i < num_symbols; i++) {
    //     printf("Symbol %d: %s -----%d\n", i, &strtab_data[symbols[i].st_name],symbols[i].st_name);//section的st_name是0！！！RTFM！！！
    //     printf("  Value: %lx\n", symbols[i].st_value);
    //     printf("  Size: %ld\n", symbols[i].st_size);
    //     printf("  Info: %d\n", symbols[i].st_info);
    //     printf("  Other: %d\n", symbols[i].st_other);
    //     printf("  Section Index: %d\n", symbols[i].st_shndx);
    //     }
	for (int i = 0; i < num_symbols; i++) {
		if(symbols[i].st_size!=0){
			add_symbol(symbols[i].st_value,symbols[i].st_size,&strtab_data[symbols[i].st_name]);
		}
	}
    fclose(file);
}

//初始化函数名表，(用链表维护)
void init_ftrace(char *filepath){
	if(filepath==NULL){
		Log("Empty File Path,Won't read Symbol Table!");
		return;
	}
	Log("Reading Symbol Table from %s",filepath);
	//初始化头结点
	nodes=malloc(sizeof(trace_node));
	nodes->length=0;nodes->start_addr=0;nodes->next=NULL;

    read_symbol_table(filepath);
}
