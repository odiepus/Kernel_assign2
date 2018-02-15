/*Assignment 2 by Hector R Herrera kec296 
 * 02/14/2018
 *
 * Program will access system jiffies. The function will 
 * output the jiffies through a function that is implemented into
 * a kernel module
 */


#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/jiffies.h>
#include<linux/timer.h>
#include<linux/delay.h>

//name the module 
static char modname[] = "jiffies";

//define the function that will return the jiffies count
static int my_proc_read(char *buf, char **start, off_t off, int count, int *eof, void *data){
  return sprintf(buf, "%lu\n", jiffies);
}


//create and initiialize the module
int init_module(void){
  create_proc_read_entry(modname, 0, NULL, my_proc_read, NULL);
  return 0;
}

//clean up after it returns
void cleanup_module(void){
  remove_proc_entry(modname, NULL);
}

MODULE_LICENSE("GPL")
