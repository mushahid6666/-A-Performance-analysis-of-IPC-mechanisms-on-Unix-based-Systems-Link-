#include <time.h>
#include <stdint.h>

#define FREQ 3192844000
#define NANO_SECONDS_IN_SEC  1000000000
//rdtscp wrapper
static inline uint64_t RDTSCP()
{
  unsigned int hi,lo;
  __asm__ volatile("rdtscp" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi<<32) | lo;
}

//Function to set processor no.                                              
void SetAffinity(unsigned long cpuMask)
{
  sched_setaffinity(0, sizeof(cpuMask), &cpuMask);
}

/* returns a static buffer of struct timespec with the time difference of ts1 and ts2
   ts1 is assumed to be greater than ts2 */
struct timespec TimeSpecDiff(struct timespec *ts1, struct timespec *ts2)
{
  struct timespec ts;
  ts.tv_sec = ts1->tv_sec - ts2->tv_sec;
  ts.tv_nsec = ts1->tv_nsec - ts2->tv_nsec;
  if (ts.tv_nsec < 0) {
    ts.tv_sec--;
    ts.tv_nsec += NANO_SECONDS_IN_SEC;
  }
  return ts;
}
