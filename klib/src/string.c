#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t  len = 0;
  while(*s != '\0')
  {
    len++;
    s++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  char *d = dst;
  const char *s = src;

  while(*s != '\0')
  {
    *d = *s;
    d++;
    s++;
  }
  *d = '\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t lens = strlen(src);
  size_t i = 0;

  while(i < n)
  {
      if(i < lens)
          dst[i] = src[i];
      else
          dst[i] = '\0';
      i++;
  }

  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t i = 0;
  while(dst[i] != '\0')
  {
    i++;
  }

  strcpy(dst+i, src);

  return dst;
}

int strcmp(const char *s1, const char *s2) {
  const char *p1 = s1;
  const char *p2 = s2;
  size_t len1 = strlen(s1);
  size_t len2 = strlen(s2);
  int ret = 0;

  while(((p1 - s1 <= len1) || (p2 - s2 <= len2)) && ret==0)
  {
    ret = *p1 - *p2;
    p1++;
    p2++;
  }

  return ret;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t i = 0;
  size_t len1 = strlen(s1);
  size_t len2 = strlen(s2);
  int ret = 0;
  
  size_t min1 = len1 < len2 ? len1+1 : len2+1;
  size_t min2 = min1 < n ? min1 : n;

  while(i < min2 && ret == 0)
  {
    ret = s1[i] - s2[i];
    i++;
  }

  return ret;
}

void *memset(void *s, int c, size_t n) {
  if (s == NULL || n == 0)
  return s;

  unsigned char *p = (unsigned char *)s;
  size_t i = 0;

  while (i < n) {
    p[i] = (unsigned char)c;
    i++;
  }

  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  unsigned char *p1 = (unsigned char *)src;
  unsigned char *p2 = (unsigned char *)dst;
  int i = 0;

  /*
    但当源内存和目标内存存在重叠时，memcpy可能会出现错误
    当源内存的首地址等于目标内存的首地址时，不进行任何拷贝
    当源内存的首地址大于目标内存的首地址时，实行正向拷贝
    当源内存的首地址小于目标内存的首地址时，实行反向拷贝
  */
  if(src > dst)
  {
      i = 0;
      while(i < n)
      {
          p2[i] = p1[i];
          i++;
      }
  }
  else if(src < dst)
  {
      i = n - 1;
      while(i >= 0)
      {
          p2[i] = p1[i];
          i--;
      }
  }

  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  unsigned char *p1 = (unsigned char *)in;
  unsigned char *p2 = (unsigned char *)out;
  int i = 0;

  if(in > out)
  {
      i = 0;
      while(i < n)
      {
          p2[i] = p1[i];
          i++;
      }
  }
  else if(in < out)
  {
      i = n - 1;
      while(i >= 0)
      {
          p2[i] = p1[i];
          i--;
      }
  }

  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = s1;
  const unsigned char *p2 = s2;
  size_t i = 0;
  int ret = 0;

  while(i < n && ret == 0)
  {
    ret = p1[i] - p2[i];
    i++;
  }

  return ret;
}

#endif
