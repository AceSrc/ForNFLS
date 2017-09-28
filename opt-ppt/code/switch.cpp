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
  if (usec < 0) sec++, usec += 1000000;
  else sec += usec / 1000000, usec %= 1000000;
  printf("%ld.%06ld\n", sec, usec);
}

const int times = 100;
const long long maxn = 1024 * 1024 * 1024LL;

void switch_func() {
  int rt = 0, x = 4;
  for (int i = 0; i < maxn; i++) {
    switch(x) {
      case 0: rt += 15; break;
      case 1: rt += 107; break;
      case 2: rt += 3; break;
      case 3: rt += 5; break;
      case 4: rt += 13; break;
    }
  }
}

void if_func() {
  int rt = 0, x = 4;
  for (int i = 0; i < maxn; i++) {
    if (x == 0) rt += 15;
    else if (x == 1) rt += 107;
    else if (x == 2) rt += 3;
    else if (x == 3) rt += 5;
    else if (x == 4) rt += 13;
  }
}

int main(int argc, char **argv) {
  Test(switch_func, "switch_func");
  Test(if_func, "if_func");
  return 0;
}
