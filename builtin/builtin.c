#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _Array {
  char *data;
  int32_t size;
};

void print(char *s) {
  printf("%s", s);
}

void println(char *s) {
  printf("%s\n", s);
}

char *getString() {
  char buffer[8096];
  scanf("%s", buffer);
  char *s = malloc(strlen(buffer));
  strcpy(s, buffer);
  return s;
}

int32_t getInt() {
  int32_t n;
  scanf("%d", &n);
  return n;
}

char *toString(int32_t n) {
  char *s = malloc(24);
  sprintf(s, "%d", n);
  return s;
}

int32_t _string_length(char *s) {
  return strlen(s);
}

char *_string_substring(char *s, int32_t l, int32_t r) {
  int32_t len = r - l + 1;
  char *sub = malloc(len + 1);
  for (int32_t i = 0; i < len; ++i) {
    sub[i] = s[l + i];
  }
  sub[len] = '\0';
  return sub;
}

int32_t _string_parseInt(char *s) {
  int32_t n = 0;
  int32_t neg = 0;
  if (*s == '-') {
    neg = 1;
    s++;
  }
  while ('0' <= *s && *s <= '9') {
    n = n * 10 + (*s - '0');
    s++;
  }
  return neg ? -n : n;
}

int32_t _string_ord(char *s, int32_t i) {
  return s[i];
}

char* __string_add(char* s1, char* s2) {
  int32_t l1 = strlen(s1);
  int32_t l2 = strlen(s2);
  char* s = malloc(l1 + l2 + 1);
  for (int32_t i = 0; i < l1; ++i)
    s[i] = s1[i];
  for (int32_t i = 0; i < l2; ++i)
    s[l1 + i] = s2[i];
  s[l1 + l2] = '\0';
  return s;
}

int8_t _string_eq(char* s1, char* s2) {
  return strcmp(s1, s2) ? 0 : 1;
}

int8_t _string_neq(char* s1, char* s2) {
  return strcmp(s1, s2) ? 1 : 0;
}

int8_t _string_lt(char* s1, char* s2) {
  return strcmp(s1, s2) < 0;
}

int8_t _string_gt(char* s1, char* s2) {
  return strcmp(s1, s2) > 0;
}

int8_t _string_le(char* s1, char* s2) {
  return strcmp(s1, s2) <= 0;
}

int8_t _string_ge(char* s1, char* s2) {
  return strcmp(s1, s2) >= 0;
}

int32_t _array_size(struct _Array *a) {
  return a->size;
}