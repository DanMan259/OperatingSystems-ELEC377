/*+
 * Module:  lab2.c
 *
 * Purpose: Skeleton solution to ELEC 377 Lab2.
 *
-*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>

#define NR_THREADS 0Xc038b3a8

static struct task_struct * firstTask, *lastTask;

int cnt;

int my_read_proc(char * page, char **start, off_t fpos, int blen, int * eof, void * data){
    int numChars = 0;
    if (fpos == 0){
	     numChars += sprintf(page, "Number of running processes: %d\n", nr_running);
	     numChars += sprintf(page + numChars, "Number of running threads: %d\n", (int*)NR_THREADS);
	     numChars += sprintf(page + numChars, "PID\tUID\tNICE\n");
	     // First Task
	     theTask = &init_task;
	     lastTask = theTask;
	     if (theTask -> pid != 0){
	         numChars += sprintf(page + numChars, "%d\t%d\t%d\n", theTask->pid, theTask->uid, theTask->nice);
	     }
	     lastTask = lastTask->next_task;
    } else {
        if (lastTask == theTask){
            *eof = 0;
            *start = page;
            return 0;
        }
        if (theTask -> pid != 0){
            numChars += sprintf(page + numChars, "%d\t%d\t%d\n", theTask->pid, theTask->uid, theTask->nice);
        }
        lastTask = lastTask->next_task;
    }
    *eof = 1;
    *start = page;
    return numChars;
}

int init_module(){
   struct proc_dir_entry * proc_entry;
   char [] procName = "lab2"
   proc_entry = create_proc_entry("lab2", 0444, NULL);
   if (proc_entry == NULL) {
        remove_proc_entry("lab2", &proc_root);
        printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
                procfs_name);
        return -ENOMEM;
   }
   proc_entry->read_proc = my_read_proc;
   return 0
}

void cleanup_module(){
    remove_proc_entry("lab2", &proc_root);
}
