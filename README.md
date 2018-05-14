# Elfluenza

This is a proof-of-concept virus written in class
[IS-521](https://github.com/KAIST-IS521/) at KAIST.

### Author

Seungyeop Lee (2dvorak)

### Elfluenza

A pandemic ELF virus that will destroy the world.

- 알파고와 스카이넷도 무력화시킬 강력한 ELF 바이러스
- 감염된 ELF 파일 또한 바이러스의 숙주로 동작
- 안티바이러스의 탐지 회피를 위한 방어 기재

### Elfpacito

A vaccine for Elfluenza

- 바이너리를 Elfluenza에 감염된 것처럼 위장하여 바이러스의 확산을 방지
- 

### Abstract

- ELF를 대상으로 하는 바이러스
- 감염된 바이너리는 원래의 기능을 수행하는 동시에 바이러스로서 동작
- 시그니처를 통한 중복 감염 방지
- 호환성을 위해 라이브러리를 배제하고 C와 어셈블리어 사용
- 탐지 회피를 위해 PTRACE 등의 방법 사용
- 화이트햇에 의한 디버깅 방지를 위해 PGP 암호화

### Usage

### Licensed Users
- sangkilc
- oxsignal
- soomin-kim
- seongil-wi
- mikkang
- jchoi2022
- DaramG

### ELF Format

ELF는 다음과 같은 구조로 이루어져 있다.
- ELF Header
```
typedef struct elf64_hdr {
  unsigned char	e_ident[EI_NIDENT];	/* ELF "magic number" */
  Elf64_Half e_type;
  Elf64_Half e_machine;
  Elf64_Word e_version;
  Elf64_Addr e_entry;		/* Entry point virtual address */
  Elf64_Off e_phoff;		/* Program header table file offset */
  Elf64_Off e_shoff;		/* Section header table file offset */
  Elf64_Word e_flags;
  Elf64_Half e_ehsize;
  Elf64_Half e_phentsize;
  Elf64_Half e_phnum;
  Elf64_Half e_shentsize;
  Elf64_Half e_shnum;
  Elf64_Half e_shstrndx;
} Elf64_Ehdr;
```
- Program Headers
```
typedef struct elf64_phdr {
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Off p_offset;		/* Segment file offset */
  Elf64_Addr p_vaddr;		/* Segment virtual address */
  Elf64_Addr p_paddr;		/* Segment physical address */
  Elf64_Xword p_filesz;		/* Segment size in file */
  Elf64_Xword p_memsz;		/* Segment size in memory */
  Elf64_Xword p_align;		/* Segment alignment, file & memory */
} Elf64_Phdr;
```
- Section Headers
```
typedef struct elf64_shdr {
  Elf64_Word sh_name;		/* Section name, index in string tbl */
  Elf64_Word sh_type;		/* Type of section */
  Elf64_Xword sh_flags;		/* Miscellaneous section attributes */
  Elf64_Addr sh_addr;		/* Section virtual addr at execution */
  Elf64_Off sh_offset;		/* Section file offset */
  Elf64_Xword sh_size;		/* Size of section in bytes */
  Elf64_Word sh_link;		/* Index of another section */
  Elf64_Word sh_info;		/* Additional section information */
  Elf64_Xword sh_addralign;	/* Section alignment */
  Elf64_Xword sh_entsize;	/* Entry size if section holds table */
} Elf64_Shdr;
```
- Programs
- Sections
- Reference : For detailed information about ELF Format, [ELF_FORMAT.pdf](http://www.skyfree.org/linux/references/ELF_Format.pdf)

### Infection

- Host 상의

#### Signature
- Header : AC3D C0DE + [1 random byte]
- Entry Point : nop; nop; nop; nop; xor esp, ebp; xor esp, ebp; nop; nop; nop; nop;

### Compatibility

### Anti Anti-Virus

### Reference
