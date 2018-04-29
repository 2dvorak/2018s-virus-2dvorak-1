#include "types.h"

#define NULL    0
#define SEEK_SET   0
#define SEEK_CUR   1
#define SEEK_END   2

#define FILENAME_MAX   256
#define EOF            (-1)
#define BUFSIZ         512

/*typedef int handle_t;

struct _iobuf {
  char *ptr;
  int cnt;
  char *base;
  int flag;
  handle_t file;
  int charbuf;
  int bufsiz;
  int phndl;
};

typedef struct _iobuf FILE;*/

int my_memcmp(const unsigned char *str1, const unsigned char *str2, size_t count);
