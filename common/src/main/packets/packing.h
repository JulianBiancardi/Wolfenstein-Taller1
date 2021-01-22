#ifndef PACKING_H
#define PACKING_H

#include <stddef.h>

/* Pack a 8-bit char into a char buffer */
void packi8(unsigned char* buf, unsigned char i);

/* Unpack a 8-bit char from a char buffer */
char unpacki8(unsigned char* buf);

/* Unpack a 8-bit unsigned char from a char buffer */
unsigned char unpacku8(unsigned char* buf);

/* Pack a 16-bit int into a char buffer */
void packi16(unsigned char* buf, unsigned int i);

/* Unpack a 16-bit int from a char buffer */
int unpacki16(unsigned char* buf);

/* Unpack a 16-bit unsigned int from a char buffer */
unsigned int unpacku16(unsigned char* buf);

/* Pack a 32-bit int into a char buffer */
void packi32(unsigned char* buf, unsigned long int i);

/* Unpack a 32-bit int from a char buffer */
long int unpacki32(unsigned char* buf);

/* Unpack a 32-bit unsigned int from a char buffer */
unsigned long int unpacku32(unsigned char* buf);

/* Pack a 64-bit int into a char buffer */
void packi64(unsigned char* buf, unsigned long long int i);

/* Unpack a 64-bit int from a char buffer */
long long int unpacki64(unsigned char* buf);

/* Unpack a 64-bit unsigned int from a char buffer */
unsigned long long int unpacku64(unsigned char* buf);

/* Pack data as indicated by the format into the buffer */
size_t pack(unsigned char* buf, const char* format, ...);

/* Unpack data as indicated by the format from a char buffer */
void unpack(unsigned char* buf, const char* format, ...);

#endif
