#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>

static struct task_struct *firstTask, *nextTask;

int my_read_proc(...) { 
	if  (file_ops == 0) {
		//write the header to the buffer
		//find the first valid task (init_task)
		//add the first task information to the buffer
		//go to the second task
	} else {
		if (we are at beginning of list again) {
			*eof = 1;
			*start = page;
			return 0;
		}
		//write task info to the buffer
		//advance the task pointer
	}
	*eof = 1;
	*start = page;
	return numChars;
}
int init_module() {
	//todo
}

void init_module() {
	//todo
}