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
- 아주 아주 benign한 바이너리!!

### Abstract

- ELF를 대상으로 하는 바이러스
- 감염된 바이너리는 원래의 기능을 수행하는 동시에 바이러스로서 동작
- ELF format에 맞게 섹션을 추가함으로서 섹션 사이 여유공간에 코드를 추가하는 기존 방법의 한계 극복
- 시그니처를 통한 중복 감염 방지, 호환성을 위해 라이브러리를 배제하고 C와 어셈블리어 사용, 탐지 회피를 위해 PTRACE 등의 방법 사용
- 화이트햇에 의한 리버싱 방지와 재배포 방지를 위해 PGP 암호화

### Usage

- One execution, One host compromised.
```
./elfluenza
```
As simple as this.

### Licensed Users

- sa****lc
- ox****al
- so****-kim
- se****l-wi
- mi****g
- jc****022
- Da****

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
- Reference : For detailed information about ELF Format, see [ELF_FORMAT.pdf](http://www.skyfree.org/linux/references/ELF_Format.pdf)

### Infection

- Host 상의
- 감염된 바이너리인지 Signature를 통해 판단 : 헤더의 패딩 부분에 'C0DE'로 표시

### Compatibility
- No LIBC, only SYSCALL, using C + ASSEMBLY
- No dependency at all
- Runs on all ELF-compatible machine(little endian)

### Anti Anti-Virus

### Vaccine
- Elfluenza가 ELF 헤더에 표시해놓은 시그니처를 통해 감염된 바이너리인지 판단하는 것을 알아냄
- 'C0DE' 시그니처 삽입을 통해 Elfluenza에 면역

### Reference
- [Programming C without Standard Library](http://weeb.ddns.net/0/programming/c_without_standard_library_linux.txt) : Gives good overview of writing C code without libc
-[bootlin Linux Source Code Referencer](https://elixir.bootlin.com/linux/latest/source) : Very useful for searching necessary macros, structs, types.
- [ELF_FORMAT.pdf](http://www.skyfree.org/linux/references/ELF_Format.pdf) : As it says
- [ELF Virus Writing HOWTO](http://virus.enemy.org/virus-writing-HOWTO/_html/index.html) : Seems like it has a lot of information but difficult to read
- [elfinjector](https://github.com/mfaerevaag/elfinjector) : Good example of writing to an ELF file
- [Online Assembler/Disassembler](https://defuse.ca/online-x86-assembler.htm) : Helps a lot when you need to code a program byte by byte..