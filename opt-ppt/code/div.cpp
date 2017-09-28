#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <sys/resource.h>
using namespace std;
#ifndef __DEBUG__
  #define debug NULL
#else
  #define debug printf("%s %d\n", __FUNCTION__, __LINE__);
#endif
#define Assert(cond, ...) \
  do { \
    if (!cond) { \
      printf("\33[4;31mLINE NUMBER:\33[0m %d \n", __LINE__); \
      printf(__VA_ARGS__); \
      assert(cond); \
    } \ } while (0)

#define Test(code_block, desc) { \
  printf("Testing \33[4;32m%s\33[0m...\n", desc); \
  rusage start, end; \
  getrusage(RUSAGE_SELF, &start); \
  code_block(); \
  getrusage(RUSAGE_SELF, &end); \
  output(start, end); \
} 

const int inf = 2147483647;

void output(rusage start, rusage end) {
  long sec = end.ru_utime.tv_sec - start.ru_utime.tv_sec;
  long usec = end.ru_utime.tv_usec - start.ru_utime.tv_usec;
  if (usec < 0) sec--, usec += 1000000;
  else sec += usec / 1000000, usec %= 1000000;
  printf("%ld.%06ld\n", sec, usec);
}

const int times = 100;
const long long maxn = 1024 * 1024;

int a[maxn], b[maxn], c[maxn];
void div_then_mod() {
  for (int inx = 0; inx < times; inx++) {
    for (int i = 0; i < maxn; i++) {
      a[i] = i / c[i];
    }
    for (long long i = 0; i < maxn; i++) {
      b[i] = i % c[i];
    }
  }
}

void div_and_mod() {
  for (int inx = 0; inx < times; inx++)
    for (int i = 0; i < maxn; i++) {
      a[i] = i / c[i] + i % c[i];
      //a[i] = i % c[i];
      //b[i] = i % c[i];
    }
}

int main(int argc, char **argv) {
  for (int i = 0; i < maxn; i++) c[i] = rand();
  Test(div_then_mod, "div_then_mod");
  Test(div_and_mod, "div_and_mod");
  return 0;
}
