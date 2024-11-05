#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);
// 把目录分隔符/也认为是文件名的一部分
/*
约定：
 - 每个文件的大小是固定的
 - 写文件时不允许超过原有文件的大小
 - 文件的数量是固定的, 不能创建新文件
 - 没有目录
*/
typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t open_offset;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
    [FD_STDIN] = {"stdin", 0, 0, invalid_read, invalid_write},
    [FD_STDOUT] = {"stdout", 0, 0, invalid_read, invalid_write},
    [FD_STDERR] = {"stderr", 0, 0, invalid_read, invalid_write},
#include "files.h"
};

extern char *ramdisk_start;
//TODO:flags mode
int fs_open(const char *pathname, int flags, int mode) {
  for (int i = 0; i < sizeof(file_table) / sizeof(Finfo); i++) {
    if (strcmp(file_table[i].name, pathname) == 0) {
      file_table[i].open_offset = 0;
      return i;
    }
  }
  // return NULL;
  assert(0);
}
size_t fs_read(int fd, void *buf, size_t len) {
  for (int i = 0; i < len; i++) {
    if (i == file_table[fd].size)
      return i;
    *((char *)buf + i) = ramdisk_start[file_table[fd].open_offset + i];
  }
  file_table[fd].open_offset += len;
  return len;
}
size_t fs_write(int fd, const void *buf, size_t len) {
  for (int i = 0; i < len; i++) {
    if (i == file_table[fd].size)
      return i;
    ramdisk_start[file_table[fd].open_offset + i] = *((char *)buf + i);
  }
  file_table[fd].open_offset += len;
  return len;
}
size_t fs_lseek(int fd, size_t offset, int whence) {
  switch (whence) {
  case SEEK_SET:
    if (offset > file_table[fd].size)
      return -1;
    file_table[fd].open_offset = offset;
    break;
  case SEEK_CUR:
    if (file_table[fd].open_offset + offset > file_table[fd].size)
      return -1;
    file_table[fd].open_offset += offset;
    break;
  case SEEK_END:
    if (offset > 0)
      return -1;
    file_table[fd].open_offset = file_table[fd].size + offset;
    break;
  default:
    assert(0);
  }
  return 0;
}
int fs_close(int fd) {
  file_table[fd].open_offset = 0;
  return 0;
}

void init_fs() {
  // TODO: initialize the size of /dev/fb
}
