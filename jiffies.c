#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/jiffies.h>
#include<linux/timer.h>
#include<linux/delay.h>

static char modname[] = "jiffies";

static int my_proc_read(char *buf, char **start, off_t off, int count, int *eof, void *data){
  return sprintf(buf, "%lu\n", jiffies);
}

int init_module(void){
  create_proc_read_entry(modname, 0, NULL, my_proc_read, NULL);
  return 0;
}

void cleanup_module(void){
  remove_proc_entry(modname, NULL);
}

MODULE_LICENSE("GPL")
