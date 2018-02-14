#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main(void){
  FILE *fpJiff1;
  FILE *fpJiff2;
  FILE *fpUpTime;

  fpJiff1 = popen("cat /proc/jiffies", "r");
  sleep(2);
  fpJiff2 = popen("cat /proc/jiffies", "r");
  fpUpTime = popen("cat /proc/uptime", "r");

  char bufJiff1[4096];
  char bufJiff2[4096];
  char bufUpTime[4096];

  char *p;

  printf("Hz == sysconf(_SC_CLK_TCK) == %lu\n", sysconf(_SC_CLK_TCK));

  if(fpJiff1 == NULL || fpJiff2 == NULL || fpUpTime == NULL){
    perror("popen");
    exit(2);
  }

  fgets(bufJiff1, sizeof(bufJiff1), fpJiff1);
  fgets(bufJiff2, sizeof(bufJiff2), fpJiff2);
  fgets(bufUpTime, sizeof(bufUpTime), fpUpTime);

  unsigned long lJiff1 = strtoul(bufJiff1, &p, 10);
  unsigned long lJiff2 = strtoul(bufJiff2, &p, 10);
  unsigned long lUpTime = strtoul(bufUpTime, &p, 10);

  printf("Start: %lu\n", lJiff1);
  printf("Start: %lu\n", lJiff2);
  unsigned long dif = lJiff2 - lJiff1;

  printf("Difference: %lu\n", dif/10);

  printf("Seconds per 100 jiffies: %lu\n", dif/(10 * (unsigned long) sysconf(_SC_CLK_TCK)));

  printf("Total uptime in jiffies from /proc/jiffies: %lu\n", lJiff2);
  printf(":Total uptime in seconds from /proc/jiffies%lu\n", dif/(10 * (unsigned long) sysconf(_SC_CLK_TCK)));
  printf("Total uptime in seconds from /proc/uptime: %lu\n", lUpTime);

  return 0;
}

