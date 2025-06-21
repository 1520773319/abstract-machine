#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

int itoa(int n, char buffer[], int base) {
  const char digits[] = "0123456789abcdef";
  char temp[32];
  int i = 0;
  int is_negative = 0;

  if (n == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return 1;
  }

  if (n < 0 && base == 10) {
    is_negative = 1;
    n = -n;
  }

  while (n > 0) {
    temp[i++] = digits[n % base];
    n /= base;
  }

  if (is_negative) {
    temp[i++] = '-';
  }

  int j = 0;
  while (i > 0) {
    buffer[j++] = temp[--i];
  }
  buffer[j] = '\0';

  return j;
}

void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  panic("Not implemented");
#endif
  return NULL;
}

void free(void *ptr) {
}

#endif
