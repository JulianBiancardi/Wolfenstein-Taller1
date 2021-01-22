#include "packing.h"

#include <cstdarg>
#include <cstring>

void packi8(unsigned char* buf, unsigned char i) { *buf++ = i; }

char unpacki8(unsigned char* buf) {
  unsigned char u = unpacku8(buf);
  char i;

  // Change sign if necessary using two's complement
  if (u < 0x7fu) {
    i = u;
  } else {
    i = -1 - (unsigned int)(0xffu - u);
  }

  return i;
}

unsigned char unpacku8(unsigned char* buf) { return buf[0]; }

void packi16(unsigned char* buf, unsigned int i) {
  *buf++ = i >> 8;
  *buf++ = i;
}

int unpacki16(unsigned char* buf) {
  unsigned int u = unpacku16(buf);
  int i;

  // Change sign if necessary using two's complement
  if (u < 0x7fffu) {
    i = u;
  } else {
    i = -1 - (unsigned int)(0xffffu - u);
  }

  return i;
}

unsigned int unpacku16(unsigned char* buf) {
  return ((unsigned int)buf[0] << 8) | buf[1];
}

void packi32(unsigned char* buf, unsigned long int i) {
  *buf++ = i >> 24;
  *buf++ = i >> 16;
  *buf++ = i >> 8;
  *buf++ = i;
}

long int unpacki32(unsigned char* buf) {
  unsigned long int u = unpacku32(buf);
  long int i;

  // Change sign if necessary using two's complement
  if (u <= 0x7fffffffu) {
    i = u;
  } else {
    i = -1 - (long int)(0xffffffffu - u);
  }

  return i;
}

unsigned long int unpacku32(unsigned char* buf) {
  return ((unsigned long int)buf[0] << 24) | ((unsigned long int)buf[1] << 16) |
         ((unsigned long int)buf[2] << 8) | buf[3];
}

void packi64(unsigned char* buf, unsigned long long int i) {
  *buf++ = i >> 56;
  *buf++ = i >> 48;
  *buf++ = i >> 40;
  *buf++ = i >> 32;
  *buf++ = i >> 24;
  *buf++ = i >> 16;
  *buf++ = i >> 8;
  *buf++ = i;
}

long long int unpacki64(unsigned char* buf) {
  unsigned long long int u = unpacku64(buf);
  long long int i;

  // Change sign if necessary using two's complement
  if (u <= 0x7fffffffffffffffu) {
    i = u;
  } else {
    i = -1 - (long long int)(0xffffffffffffffffu - u);
  }

  return i;
}

unsigned long long int unpacku64(unsigned char* buf) {
  return ((unsigned long long int)buf[0] << 56) |
         ((unsigned long long int)buf[1] << 48) |
         ((unsigned long long int)buf[2] << 40) |
         ((unsigned long long int)buf[3] << 32) |
         ((unsigned long long int)buf[4] << 24) |
         ((unsigned long long int)buf[5] << 16) |
         ((unsigned long long int)buf[6] << 8) | buf[7];
}

size_t pack(unsigned char* buf, const char* format, ...) {
  // 8-bit
  signed char c;
  unsigned char C;

  // 16-bit
  int i;
  unsigned int I;

  // 32-bit
  long int l;
  unsigned long int L;

  // 64-bit
  long long int h;
  unsigned long long int H;

  // strings
  char* s;
  size_t len;

  size_t size = 0;

  va_list args;
  va_start(args, format);

  for (; *format != '\0'; format++) {
    switch (*format) {
      case 'c':
        c = (signed char)va_arg(args, int);
        packi8(buf, c);
        buf += 1;
        size += 1;
        break;
      case 'C':
        C = (unsigned char)va_arg(args, unsigned int);
        packi8(buf, c);
        buf += 1;
        size += 1;
        break;
      case 'i':
        i = va_arg(args, int);
        packi16(buf, i);
        buf += 2;
        size += 2;
        break;
      case 'I':
        I = va_arg(args, unsigned int);
        packi16(buf, I);
        buf += 2;
        size += 2;
        break;
      case 'l':
        l = va_arg(args, long int);
        packi32(buf, l);
        buf += 4;
        size += 4;
        break;
      case 'L':
        L = va_arg(args, unsigned long int);
        packi32(buf, L);
        buf += 4;
        size += 4;
        break;
      case 'h':
        h = va_arg(args, long long int);
        packi64(buf, h);
        buf += 8;
        size += 8;
        break;
      case 'H':
        H = va_arg(args, unsigned long long int);
        packi64(buf, H);
        buf += 8;
        size += 8;
        break;
      case 's':
        s = va_arg(args, char*);
        len = strlen(s);
        packi16(buf, len);
        buf += 2;
        memcpy(buf, s, len);
        buf += len;
        size += len + 2;
        break;
      default:
        break;
    }
  }

  va_end(args);

  return size;
}

void unpack(unsigned char* buf, const char* format, ...) {
  // 8-bit
  signed char* c;
  unsigned char* C;

  // 16-bit
  int* i;
  unsigned int* I;

  // 32-bit
  long int* l;
  unsigned long int* L;

  // 64-bit
  long long int* h;
  unsigned long long int* H;

  // strings
  char* s;
  size_t len;

  va_list args;
  va_start(args, format);

  for (; *format != '\0'; format++) {
    switch (*format) {
      case 'c':
        c = va_arg(args, signed char*);
        *c = unpacki8(buf);
        buf += 1;
        break;
      case 'C':
        C = va_arg(args, unsigned char*);
        *C = unpacku8(buf);
        buf += 1;
        break;
      case 'i':
        i = va_arg(args, int*);
        *i = unpacki16(buf);
        buf += 2;
        break;
      case 'I':
        I = va_arg(args, unsigned int*);
        *I = unpacku16(buf);
        buf += 2;
        break;
      case 'l':
        l = va_arg(args, long int*);
        *l = unpacki32(buf);
        buf += 4;
        break;
      case 'L':
        L = va_arg(args, unsigned long int*);
        *L = unpacku32(buf);
        buf += 4;
        break;
      case 'h':
        h = va_arg(args, long long int*);
        *h = unpacki64(buf);
        buf += 8;
        break;
      case 'H':
        H = va_arg(args, unsigned long long int*);
        *H = unpacku64(buf);
        buf += 8;
        break;
      case 's':
        s = va_arg(args, char*);
        len = unpacku16(buf);
        buf += 2;
        memcpy(s, buf, len);
        s[len] = '\0';
        buf += len;
      default:
        break;
    }
  }

  va_end(args);
}