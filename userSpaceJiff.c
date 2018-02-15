/* Assingment 2 by Hector Herrera kec296
 * 02/14/2018
 * Add a proc module that outputs jiffies
 * Use a userspace program to confirm jiffies 
 *  and time in secs correlate.
 */


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main(void){
  //create file pointers for /proc/jiffies and /proc/uptime
  FILE *fpJiff1;
  FILE *fpJiff2;
  //uptime will be used to measure accuracy of jiffies
  FILE *fpUpTime;

  fpJiff1 = popen("cat /proc/jiffies", "r");
  sleep(2);
  fpJiff2 = popen("cat /proc/jiffies", "r");
  fpUpTime = popen("cat /proc/uptime", "r");

  //buffers to hold the output from proc files
  char bufJiff1[4096];
  char bufJiff2[4096];
  char bufUpTime[4096];

  //pointer used to point to discarded input
  char *p;
  
  //print out the system definition of Hz which should be 1000 but is 100 on my system
  printf("Hz == sysconf(_SC_CLK_TCK) == %lu\n", sysconf(_SC_CLK_TCK));

  if(fpJiff1 == NULL || fpJiff2 == NULL || fpUpTime == NULL){
    perror("popen");
    exit(2);
  }

  //place proc outputs to buffers
  fgets(bufJiff1, sizeof(bufJiff1), fpJiff1);
  fgets(bufJiff2, sizeof(bufJiff2), fpJiff2);
  fgets(bufUpTime, sizeof(bufUpTime), fpUpTime);

  //extract the value of proc files in specified data type
  unsigned long lJiff1 = strtoul(bufJiff1, &p, 10);
  unsigned long lJiff2 = strtoul(bufJiff2, &p, 10);
  unsigned long lUpTime = strtoul(bufUpTime, &p, 10);

  //print out the initial jiffy capture delay for secs then print out the subsequent capture
  printf("Start jiffies: %lu\n", lJiff1);
  printf("Sleep for 2 seconds...\n");
  printf("Stop jiffies: %lu\n", lJiff2);

  //calculate the difference
  unsigned long dif = lJiff2 - lJiff1;

  printf("Difference: %lu\n", dif);

  printf("Man pages state jiffies for this linux version is 1000. But, sysconf returns 100. I will use manpage specifications. Time elapsed in %lu jiffies is:  %lu secs\n", dif, dif/1000);

  printf("Total uptime in jiffies from /proc/jiffies: %lu\n", lJiff2);
  printf(":Total uptime in seconds from /proc/jiffies%lu\n", dif/1000);

  //there is always a 300 sec difference between uptime and jiffies. this works out to a 5 min
  //difference. this may have to do with the 5 min overflow that is designed into jiffies.
  printf("Total uptime in seconds from /proc/uptime: %lu\n", lUpTime);

  return 0;
}

