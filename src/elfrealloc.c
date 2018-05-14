#include <linux/elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int resolve_header(Elf64_Ehdr* header, Elf64_Phdr** pHeader, Elf64_Shdr** sHeader, char** programs, char** sections, Elf64_Half shstrndx) {
	header->e_ehsize = (Elf64_Half)sizeof(*header);
	header->e_phentsize = (Elf64_Half)sizeof(**pHeader);
	header->e_shentsize = (Elf64_Half)sizeof(**sHeader);
	header->e_phoff = (Elf64_Off)(header->e_ehsize);
	header->e_shoff = (Elf64_Off)(header->e_ehsize + header->e_phnum * header->e_phentsize);
	header->e_shstrndx = shstrndx;
	return 0;
}

int assemble(Elf64_Ehdr* header, Elf64_Phdr** pHeader, Elf64_Shdr** sHeader, char** programs, char** sections) {
	Elf64_Off e_phoff, e_shoff;
	Elf64_Addr e_entry;
	FILE* file = fopen("new_victim","w");
	if(!file) {
		printf("cannot open file new_elf\n");
		return -1;
	}
	if(sizeof(*header) != header->e_ehsize) {
		printf("something wrong with e_ehsize\n");
		return -1;
	}
	if(sizeof(**pHeader) != header->e_phentsize) {
		printf("something wrong with e_phentsize\n");
		return -1;
	}
	if(sizeof(**sHeader) != header->e_shentsize) {
		printf("something wrong with e_shentsize\n");
		return -1;
	}
	fwrite(header, 1, sizeof(*header), file);
	printf("header written\n");

	for(int i = 0 ; i < header->e_phnum ; i++) {
		fwrite((void *)&(*pHeader)[i], 1, sizeof(**pHeader), file);
	}

	printf("pheaders written\n");
	for(int i = 0 ; i < header->e_shnum ; i++) {
		fwrite((void *)&(*sHeader)[i], 1, sizeof(**sHeader), file);
	}

	printf("sheaders written\n");
	fclose(file);
	return 0;
}

int main(int argc, char** argv) {
	Elf64_Ehdr header;
	// Elf64_Phdr, Elf64_Shdr
	FILE* file = fopen(argv[1],"rw");
	if(!file) {
		printf("cannot open file\n");
		return -1;
	}
	fread(&header, 1, sizeof(header), file);

	if(header.e_ident[0] != 0x7f ||
		header.e_ident[1] != 'E' ||
		header.e_ident[2] != 'L' ||
		header.e_ident[3] != 'F') {
		printf("ELF header missmatch\n");
		return -1;
	}

	if(header.e_ident[EI_CLASS] != ELFCLASS64) {
		printf("ELF version missmatch\n");
		return -1;
	}

	//printf("ELF header parsed\n");

	Elf64_Phdr pHeader[header.e_phnum];
	Elf64_Shdr sHeader[header.e_shnum];
	char* programs[header.e_phnum];
	char* sections[header.e_shnum];
	char* sNames[header.e_shnum];
	Elf64_Half textseg = 0;
	Elf64_Half textsec = 0;

	fseek(file, header.e_phoff, SEEK_SET);
	for(int i = 0 ; i < header.e_phnum ; i++) {
		fread(&pHeader[i], 1, header.e_phentsize, file);
		if(pHeader[i].p_type == PT_LOAD && pHeader[i].p_flags & (PF_R | PF_X)) {
			textseg = (Elf64_Half)(i - 1);
			//printf("textseg : seg[%d]\n", textseg);
		}
	}

	//printf("ELF segment headers parsed\n");

	fseek(file, header.e_shoff, SEEK_SET);
	for(int i = 0 ; i < header.e_shnum ; i++) {
		fread(&sHeader[i], 1, header.e_shentsize, file);
	}

	//printf("ELF section headers parsed\n");

	for(int i = 0 ; i < header.e_phnum ; i++) {
		fseek(file, pHeader[i].p_offset, SEEK_SET);
		programs[i] = (char *)malloc(pHeader[i].p_filesz);
		fread(programs[i], 1, pHeader[i].p_filesz, file);
	}

	//printf("ELF segments parsed\n");

	for(int i = 0 ; i < header.e_shnum ; i++) {
		fseek(file, sHeader[i].sh_offset, SEEK_SET);
		sections[i] = (char *)malloc(sHeader[i].sh_size);
		fread(sections[i], 1, sHeader[i].sh_size, file);
	}

	//printf("ELF sections parsed\n");


	Elf64_Half shstrndx = header.e_shstrndx;

	//printf("shstrndx : section[%d] %llx\n", shstrndx, &sections[shstrndx]);
	if(shstrndx != SHN_UNDEF) {
		for(int i = 0 ; i < header.e_shnum ; i++) {
			//printf("shstrndx section : %s\n", (char *)(&(sections[shstrndx][0]) + pos));
			sNames[i] = (char *)malloc(strlen(sections[shstrndx] + sHeader[i].sh_name) + 1);
			strncpy(sNames[i], sections[shstrndx] + sHeader[i].sh_name, strlen(sections[shstrndx] + sHeader[i].sh_name));
			if(strncmp(sNames[i], ".text", 5) == 0) {
				textsec = (Elf64_Half)i;
				//printf("text section found\n");
			}
		}
	} else {
		printf("[error?] shstrndx == SH_UNDEF\n");
	}

	// for(int i = 0 ; i < header.e_shnum ; i++) {
	// 	printf("Section [%d] : ", i);
	// 	printf("%s, offset : %llx\n", sNames[i], sHeader[i].sh_offset);
	// }
	fclose(file);

	int victim_fd = open(argv[1], O_RDWR | O_APPEND);
	int add_size = header.e_phentsize * (header.e_phnum);

	struct stat victim_info;
	fstat(victim_fd, &victim_info);

	int origin_size = victim_info.st_size;

	char nullbyte = '\0';
	for(int i = 0 ; i < 0x3000 ; i++) {
		if(write(victim_fd, &nullbyte, 1) != 1) {
			printf("write failed\n");
		}
	}

	
	fstat(victim_fd, &victim_info);

	void* victim = (void *)mmap(0, victim_info.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, victim_fd, 0);

	Elf64_Ehdr* victim_header = (Elf64_Ehdr*)victim;

	Elf64_Phdr* p_pHeader[victim_header->e_phnum];
	Elf64_Shdr* p_sHeader[victim_header->e_shnum];
	//Elf64_Half textseg = 0;

	char* pos = victim + victim_header->e_phoff;
	for(int i = 0 ; i < victim_header->e_phnum ; i++) {
		p_pHeader[i] = (Elf64_Phdr*)pos;
		// if(pHeader[i]->p_type == PT_LOAD && pHeader[i]->p_flags & (PF_R | PF_X)) {
		// 	textseg = (Elf64_Half)i;
		// }
		pos += victim_header->e_phentsize;
	}

	pos = victim + victim_header->e_shoff;
	for(int i = 0 ; i < victim_header->e_shnum ; i++) {
		p_sHeader[i] = (Elf64_Shdr*)pos;
		// if(pHeader[i]->p_type == PT_LOAD && pHeader[i]->p_flags & (PF_R | PF_X)) {
		// 	textseg = (Elf64_Half)i;
		// }
		pos += victim_header->e_shentsize;
	}

	///////////////////////////////////
	//// add section header at the end
	///////////////////////////////////

	Elf64_Addr base = header.e_entry;
	Elf64_Shdr new_sHeader;
	new_sHeader.sh_name = sHeader[textsec].sh_name + 2;
	new_sHeader.sh_type = sHeader[textsec].sh_type;
	new_sHeader.sh_flags = sHeader[textsec].sh_flags;
	//new_sHeader.sh_addr = sHeader[textsec].sh_addr + 0x1000;
	//new_sHeader.sh_addr = 0x1000;
	new_sHeader.sh_addr = p_pHeader[textseg]->p_memsz + 0x1000 - (p_pHeader[textseg]->p_memsz % 0x1000);
	new_sHeader.sh_offset = header.e_shoff + header.e_shentsize * (header.e_shnum + 1);
	new_sHeader.sh_size = 50;
	new_sHeader.sh_link = SHN_UNDEF;
	new_sHeader.sh_info = 0;
	new_sHeader.sh_addralign = 0;
	new_sHeader.sh_entsize = 0;

	memcpy(victim + origin_size, &new_sHeader, sizeof(new_sHeader));

	char tmp_entry[5];
	memcpy(tmp_entry, victim + base, 5);

	char jump_code[5] = "\xe9\x00\x00\x00\x00";

	int offset = new_sHeader.sh_addr - base - 5;
	printf("offset : %x\n", offset);

	for(int i = 0 ; i < 3 ; i++) {
		jump_code[1+i] = (char)(offset & 0x000000ff);
		offset = offset >> 8;
	}
	jump_code[4] = '\x00';

	#define LEN 	40
	//int len = 40;
	int lea_pos = 9;

	char tmp_code[LEN] = "\x41\x52\x4C\x8D\x15\xF9\x0F\x00\x00\x41\xC6\x02\x31\x41\xC6\x42\x01\xED\x41\xC6\x42\x02\x49\x41\xC6\x42\x03\x89\x41\xC6\x42\x04\xD1\x41\x5A\xE9\x00\x00\x00\x00";

	offset = new_sHeader.sh_addr + lea_pos - base;
	offset = 0x0fffffff - offset + 1;
	for(int i = 0 ; i < 3 ; i++) {
		tmp_code[(lea_pos-4)+i] = (char)(offset & 0x000000ff);
		offset = offset >> 8;
	}
	tmp_code[lea_pos - 1] = '\xff';

	offset = new_sHeader.sh_addr + LEN - base;
	offset = 0x0fffffff - offset + 1;
	for(int i = 0 ; i < 3 ; i++) {
		tmp_code[(LEN - 4)+i] = (char)(offset & 0x000000ff);
		offset = offset >> 8;
	}
	tmp_code[LEN - 1] = '\xff';

	tmp_code[0xc] = tmp_entry[0];
	tmp_code[0x11] = tmp_entry[1];
	tmp_code[0x16] = tmp_entry[2];
	tmp_code[0x1b] = tmp_entry[3];
	tmp_code[0x20] = tmp_entry[4];

	memcpy(victim + new_sHeader.sh_addr, tmp_code, LEN);
	memcpy(victim + header.e_entry, jump_code, 5);

	victim_header->e_shnum += 1;
	p_pHeader[textseg]->p_flags = PF_R | PF_W | PF_X;
	p_pHeader[textseg]->p_memsz += 0x1000;
	p_pHeader[textseg]->p_filesz += 0x1000;

	///////////////////////////////////
	//// program header add
	///////////////////////////////////

	//Elf64_Addr base = header.e_phoff + header.e_phnum * header.e_phentsize;


	///////////////////////////////////
	//// text section resize
	//// sections are totally broken
	///////////////////////////////////

	// Elf64_Addr base = sHeader[textsec].sh_offset;
	// Elf64_Addr next_base = sHeader[textsec + 1].sh_offset;
	// Elf64_Addr gap = 0x3000 - p_sHeader[textsec + 1]->sh_offset;

	// printf("%s section size : %llx\n", sNames[textsec], p_sHeader[textsec]->sh_size);
	// p_sHeader[textsec]->sh_size = 0x3000;

	// if(header.e_phoff > base) {
	// 	printf("program headers locates(%llx) behind base(%llx)???\n", header.e_phoff,base);
	// 	victim_header->e_phoff += gap;
	// }

	// if(header.e_shoff > base) {
	// 	printf("section headers locates(%llx) behind base(%llx)???\n", header.e_shoff,base);
	// 	victim_header->e_shoff += gap;
	// }

	// for(int i = 0 ; i < header.e_phnum ; i++) {
	// 	if(pHeader[i].p_offset > base) {
	// 		p_pHeader[i]->p_offset += gap;
	// 		//p_pHeader[i]->p_vaddr += 0x1000;
	// 		//p_pHeader[i]->p_paddr += 0x1000;
	// 		printf("program[%d] at %llx realloced to %llx\n", i, p_pHeader[i]->p_offset - gap, p_pHeader[i]->p_offset);
	// 	}
	// }

	// for(int i = 0 ; i < header.e_shnum ; i++) {
	// 	if(sHeader[i].sh_offset > base) {
	// 		p_sHeader[i]->sh_offset += gap;
	// 		printf("section[%d](%s) at %llx realloced to %llx\n", i, sNames[i], p_sHeader[i]->sh_offset - gap, p_sHeader[i]->sh_offset);
	// 	}
	// 	// if(p_sHeader[i]->sh_addr >= p_pHeader[textseg]->p_vaddr) {
	// 	// 	p_sHeader[i]->sh_addr += 0x1000;
	// 	// }
	// }

	// memmove(victim + base + 0x3000, victim + next_base, gap);

	///////////////////////////////////
	//// text segment shift
	//// won't work, elf cannot resolve plt, got
	//// thus cannot call main (keeps jumping to 0x00000000 looks like elf loader
	//// or libc fills that address, but )
	///////////////////////////////////

	//Elf64_Addr base = pHeader[textseg].p_offset;

	// Elf64_Addr base = victim_header->e_entry;

	// if(header.e_phoff > base) {
	// //if(1) {
	// 	printf("GG program headers locates(%llx) behind programs(%llx)???\n", header.e_phoff,base);
	// 	//victim_header->e_phoff += 0x1000;
	// }

	// if(header.e_shoff > base) {
	// //if(1) {
	// 	printf("GG section headers locates(%llx) behind programs(%llx)???\n", header.e_shoff,base);
	// 	//victim_header->e_shoff += 0x1000;
	// }

	// for(int i = 0 ; i < header.e_phnum ; i++) {
	// 	//if(pHeader[i].p_offset > base) {
	// 	if(1) {
	// 		p_pHeader[i]->p_offset += 0x1000;
	// 		p_pHeader[i]->p_vaddr += 0x1000;
	// 		p_pHeader[i]->p_paddr += 0x1000;
	// 		//printf("program[%d] at %llx realloced to %llx\n", i, p_pHeader[i]->p_offset - 0x1000, p_pHeader[i]->p_offset);
	// 	}
	// }

	// for(int i = 0 ; i < header.e_shnum ; i++) {
	// 	//if(sHeader[i].sh_offset > base) {
	// 	if(1) {
	// 		p_sHeader[i]->sh_offset += 0x1000;
	// 		//printf("section[%d](%s) at %llx realloced to %llx\n", i, sNames[i], p_sHeader[i]->sh_offset - 0x1000, p_sHeader[i]->sh_offset);
	// 		p_sHeader[i]->sh_addr += 0x1000;
	// 	}
	// 	// if(p_sHeader[i]->sh_addr >= p_pHeader[textseg]->p_vaddr) {
	// 	// 	p_sHeader[i]->sh_addr += 0x1000;
	// 	// }
	// }

	// p_pHeader[textseg]->p_offset = pHeader[textseg].p_offset;
	// p_pHeader[textseg]->p_vaddr = pHeader[textseg].p_vaddr;
	// p_pHeader[textseg]->p_paddr = pHeader[textseg].p_paddr;
	// p_pHeader[textseg]->p_filesz += 0x1000;
	// p_pHeader[textseg]->p_memsz += 0x1000;
	// victim_header->e_entry += 0x1000;
	// victim_header->e_phoff += 0x1000;
	// victim_header->e_shoff += 0x1000;

	// memmove(victim + 0x1000, victim, origin_size);
	//memset(victim + base, 'A', 0x1000);

	/////////////////////
	//// shift program header
	/////////////////////

	// // if(header.e_type == ET_EXEC) {
	// // 	close(victim_fd);
	// // 	return -1;
	// // }

	// // this works for dyn
	// Elf64_Addr base = header.e_phoff;
	// printf("base : %llx\n", base);

	// // this works for dyn
	// //Elf64_Addr base = pHeader[0].p_offset;

	// //victim_header->e_ehsize += 0x1000;
	// victim_header->e_phoff += 0x1000;
	// victim_header->e_shoff += 0x1000;
	// //victim_header->e_entry += 0x1000;

	// for(int i = 0 ; i < header.e_phnum ; i++) {
	// 	p_pHeader[i]->p_offset += 0x1000;
	// }

	// for(int i = 0 ; i < header.e_shnum ; i++) {
	// 	p_sHeader[i]->sh_offset += 0x1000;
	// }

	// // this works for dyn
	// //p_pHeader[0]->p_offset = base;
	// if(header.e_type == ET_EXEC) {
	// 	//p_pHeader[0]->p_offset = 0x1000;
	// 	//p_pHeader[0]->p_vaddr += 0x1000;
	// 	//victim_header->e_entry += 0x1000;
	// } else if(header.e_type == ET_DYN) {
	// 	p_pHeader[0]->p_offset = base;
	// }
	// p_pHeader[textseg]->p_flags = PF_R | PF_W | PF_X;

	// // danger zone
	
	// p_pHeader[textseg]->p_offset = 0;
	
	// p_pHeader[textseg]->p_memsz += 0x1000;
	// //
	
	// p_pHeader[0]->p_filesz += 0x1000;
	// p_pHeader[0]->p_memsz += 0x1000;

	// memmove(victim + base + 0x1000, victim + base , origin_size - base);
	// memset(victim + base, '\x90', 0x1000);

	// close(victim_fd);
	// return 0;

	// char tmp_entry[5];
	// memcpy(tmp_entry, victim + base + 0x1000, 5);

	// char jump_code[5] = "\xe9\xff\xff\xff\xff";

	// int offset = header.e_entry + 0x1000 + 5 - base;
	// printf("offset : %x\n", offset);
	// offset = 0x0fffffff - offset + 1;
	// for(int i = 0 ; i < 3 ; i++) {
	// 	jump_code[1+i] = (char)(offset & 0x000000ff);
	// 	offset = offset >> 8;
	// }
	// jump_code[4] = '\xff';


	// // char to_find_0[4] = "\x00\x00";
	// // char to_find_f[4] = "\xff\xff";
	// // void* delimiter = (void*)memmem(tmp_entry, 512, to_find_0, 4);
	// // if(delimiter == NULL) {
	// // 	delimiter = (void*)memmem(tmp_entry, 512, to_find_f, 4);
	// // 	if(delimiter == NULL) {
	// // 		printf("nooooooooooooo\n");
	// // 	}
	// // }

	// //char tmp_code[35] = "\x41\x57\
	// 	\x4c\x8d\x3d\xf9\x0f\x00\x00\
	// 	\x41\xc6\
	// 	\x41\xc6\x07\x31\
	// 	\x41\xc6\x47\x01\xed\
	// 	\x41\xc6\x47\x02\x49\
	// 	\x41\xc6\x47\x03\x89\
	// 	\x41\xc6\x47\x04\xd1\
	// 	\x41\x5f";
	// char tmp_code[35] = "\x41\x57\x4C\x8D\x3D\xF5\x0F\x00\x00\x41\xC6\x07\x31\x41\xC6\x47\x01\xED\x41\xC6\x47\x02\x49\x41\xC6\x47\x03\x89\x41\xC6\x47\x04\xD1\x41\x5F";

	// memcpy(victim + base, tmp_code, 35);
	// memcpy(victim + header.e_entry + 0x1000, jump_code, 5);



	/////////////////////
	//// program header copy
	/////////////////////


	//p_pHeader[textseg]->p_align = 1;

	// memmove(victim + origin_size, victim + header.e_phoff, add_size);

	// Elf64_Phdr text_program;

	// text_program.p_type = PT_LOAD;
	// //text_program.p_offset = origin_size + add_size + header.e_phentsize;
	// text_program.p_offset = 0x3000;
	// //text_program.p_vaddr = pHeader[textseg].p_vaddr + pHeader[textseg].p_memsz;
	// //text_program.p_paddr = pHeader[textseg].p_paddr + pHeader[textseg].p_memsz;
	// //text_program.p_vaddr = origin_size + add_size + header.e_phentsize;
	// //text_program.p_paddr = origin_size + add_size + header.e_phentsize;
	// text_program.p_vaddr = 0x3000;
	// text_program.p_paddr = 0x3000;
	// text_program.p_filesz = 9;
	// text_program.p_memsz = 9;
	// text_program.p_flags = pHeader[textseg].p_flags;
	// text_program.p_align = 1;

	// memmove(victim + origin_size + add_size, &text_program, sizeof(Elf64_Phdr));

	// char nop[9];
	// nop[0] = '\x90';
	// nop[1] = '\x90';
	// nop[2] = '\x90';
	// nop[3] = '\x90';
	// nop[4] = '\xe9';
	// nop[5] = '\xbf';
	// nop[6] = '\xff';
	// nop[7] = '\xff';
	// nop[8] = '\xff';

	// int offset = text_program.p_offset + 9 - header.e_entry;
	// offset = 0x0fffffff - offset + 1;
	// for(int i = 0 ; i < 3 ; i++) {
	// 	nop[5+i] = (char)(offset & 0x000000ff);
	// 	offset = offset >> 8;
	// }
	// nop[8] = '\xff';

	// //victim_header->e_entry = text_program.p_offset;
	// victim_header->e_phoff = origin_size;
	// victim_header->e_phnum += 1;


	// memmove(victim + text_program.p_offset, nop, 9);

	// Elf64_Phdr data_program;

	// data_program.p_type = PT_LOAD;
	// data_program.p_offset = origin_size + add_size + header.e_phentsize * 2;
	// data_program.p_vaddr = pHeader[textseg]->p_vaddr;
	// data_program.p_paddr = pHeader[textseg]->p_paddr;
	// data_program.p_filesz = pHeader[textseg]->p_filesz;
	// data_program.p_memsz = pHeader[textseg]->p_memsz;
	// data_program.p_flags = pHeader[textseg]->p_flags;
	// data_program.p_align = pHeader[textseg]->p_align;

	close(victim_fd);

	//assemble(&header, (Elf64_Phdr**)&pHeader, (Elf64_Shdr**)&sHeader, programs, sections);

	
	return 0;
}