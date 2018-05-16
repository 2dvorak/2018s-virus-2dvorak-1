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

- 감염되지 않은 바이너리는 Elfluenza에 감염된 것처럼 위장하여 바이러스의 확산을 방지
- 이미 감염된 바이너리는 패치하여 악성 행위 중단
- 아주 아주 **benign**한 바이너리!!

### Abstract

- ELF를 대상으로 하는 바이러스
- 감염된 바이너리는 원래의 기능을 수행하는 동시에 바이러스로서 동작
- ELF format에 맞게 섹션을 추가함으로서 섹션 사이 여유공간에 코드를 추가하는 기존 방법의 한계 극복
- 시그니처를 통한 중복 감염 방지, 호환성을 위해 라이브러리를 배제하고 C와 어셈블리어 사용, 탐지 회피를 위한 다양한  방법 사용

### Usage

- One execution, One host compromised.
```
./elfluenza
```
As simple as this.

- To test Elfluenza, Elfpacito
```
$ git clone <repository>
$ ./autoDocker.sh
$ ./test.sh
docker~$ make
docker~$ ./test_script.sh
```

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

![ELF Format](https://upload.wikimedia.org/wikipedia/commons/7/77/Elf-layout--en.svg)

section 사이의 패딩에 원하는 코드를 넣은 다음, program 헤더에서 segment의 크기를 그만큼 늘려주면, 런타임에 추가된 코드도 함께 segment에 로드된다. 하지만 이 방법은 패딩의 크기에 제약을 받는다. 따라서 파일 끝부분에 원하는 코드를 추가한 다음, program 헤더에서 text segment의 크기를 파일 끝까지 늘려준다. 그러면 추가된 코드도 text segment에 함께 로드될 수 있다.

- For detailed information about ELF Format, see [ELF_FORMAT.pdf](http://www.skyfree.org/linux/references/ELF_Format.pdf)

### Infection

- Virus의 폴더 내에 존재하는 DYN 타입 ELF 바이너리를 감염
DYN 타입을 대상으로 한 것은, PIE가 gcc에서 default option이 되었으며, Debian, Ubuntu 등의 운영체제들이 PIE를 지원하며 PIE 옵션으로 빌드되고 있기 때문이다.
- 감염된 바이너리인지 Signature를 통해 판단
중복 감염의 경우 바이너리 크기가 늘어나고, 실행 시간이 오래 걸리는 등 자원을 낭비할 수 있기 때문에 ELF 헤더의 패딩 부분에 'C0DE'로 표시하여 중복 감염 방지
- 파일 끝부분에 바이러스 코드를 추가한 다음, 해당 코드가 실행될 수 있도록 파일 수정
Entry Point에 위치한 코드를 패치해서 바이러스 코드로 jmp하도록 함으로서, Entry Point가 바뀌지 않고도 바이러스 코드가 실행될 수 있다. 이후 바이러스 코드의 실행이 끝나면 다시 원래의 Entry Point 코드로 jmp한다. 따라서 감염된 바이너리 또한 바이러스로서 동작하며, 동시에 원래의 기능도 수행한다.

### Compatibility

- No LIBC, only SYSCALL, using C + ASSEMBLY
- No dependency at all
- Runs on all ELF-compatible machine(little endian)

### Anti Anti-Virus

스캐너에 의해 분석중인지 탐지하여 악성 행위 중단
- Entry Point 보존
Entry Point가 바뀌는 것은 의심스러운 행위인데, Elfluenza는 Entry Point는 그대로 두고 코드 패치를 통해 바이러스 코드가 실행될 수 있도록 함
- 바이러스 코드를 랜덤 값과 xor 인코딩
여러 바이너리에 중복되는 코드가 추가되는 것을 탐지하는 행위 방지
- /proc/self/status : TracerPid
TracerPid가 0이 아니면 스캐너에 의해 분석중인 것으로 판단

### Vaccine - Elfpacito

- Elfluenza는 ELF 헤더에 표시해놓은 시그니처를 통해 감염된 바이너리인지 판단한다.
- Elfluenza는 이미 감염된 바이너리는 감염시키지 않는다.
- 'C0DE' 시그니처 삽입을 통해 Elfluenza에 면역시킨다
- 이미 감염된 바이너리를 찾아, Entry Point를 패치해서 악성 행위를 중단시킨다.

### Reference

- [Programming C without Standard Library](http://weeb.ddns.net/0/programming/c_without_standard_library_linux.txt) : Gives good overview of writing C code without libc
-[bootlin Linux Source Code Referencer](https://elixir.bootlin.com/linux/latest/source) : Very useful for searching necessary macros, structs, types.
- [ELF_FORMAT.pdf](http://www.skyfree.org/linux/references/ELF_Format.pdf) : As it says
- [ELF Virus Writing HOWTO](http://virus.enemy.org/virus-writing-HOWTO/_html/index.html) : Seems like it has a lot of information but difficult to read
- [elfinjector](https://github.com/mfaerevaag/elfinjector) : Good example of writing to an ELF file
- [Online Assembler/Disassembler](https://defuse.ca/online-x86-assembler.htm) : Helps a lot when you need to code a program byte by byte..
- [Learning Linux Binary Analysis](http://index-of.es/Miscellanous/Learning%20Linux%20Binary%20Analysis.pdf) : Introduces ELF Virus Technology
- ELF Format Image from [Wikipedia](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)