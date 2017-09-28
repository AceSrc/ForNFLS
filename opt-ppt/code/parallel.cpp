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
    } \
  } while (0)
const int inf = 2147483647;
const int size = 500;

void output(rusage start, rusage end) {
  long sec = end.ru_utime.tv_sec - start.ru_utime.tv_sec;
  long usec = end.ru_utime.tv_usec - start.ru_utime.tv_usec;
  if (usec < 0) sec++, usec += 1000000;
  else sec += usec / 1000000, usec %= 1000000;
  printf("%ld.%06ld\n", sec, usec);
}

const int times = 10;
const long long up = 1024 * 1024 * 64;
int a[up];
int main(int argc, char **argv) {
  for (int i = 0; i < up; i++) a[i] = 1;

  rusage start, end;
  getrusage(RUSAGE_SELF, &start);

  for (int inx = 0; inx < times; inx++)
    for (long long i = 0; i < up; i++) {
      a[0]++; a[0]++;
    }

  getrusage(RUSAGE_SELF, &end);
  output(start, end);

  getrusage(RUSAGE_SELF, &start);

  for (int inx = 0; inx < times; inx++) 
    for (long long i = 0; i < up; i++) {
      a[0]++; a[1]++;
    }

  getrusage(RUSAGE_SELF, &end);
  output(start, end);
  return 0;
}
