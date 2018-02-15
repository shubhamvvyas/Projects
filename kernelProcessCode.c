#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/tty.h>


#define MAX_BUF_SIZE 1024

int inp_pid = 0;
struct tty_struct *my_tty = NULL;
struct task_struct *iter = NULL;
struct task_struct* piter = NULL;
struct list_head* listc = NULL;
static char buf[MAX_BUF_SIZE];


module_param(inp_pid, int, S_IRUSR| S_IWUSR | S_IRGRP | S_IROTH);

MODULE_PARM_DESC(ins_pid, "Parameter to take as input.");

static void print_string(char* msg){
	if (my_tty != NULL){
		my_tty->driver->ops->write (my_tty, msg, strlen(msg));
		my_tty->driver->ops->write (my_tty, "\015\012", 2); 
	}
}

static int __init init_func(void){
	my_tty = get_current_tty();
	for_each_process(iter){
		if (iter->pid > inp_pid){
			snprintf(buf, MAX_BUF_SIZE, "PROCESS\t\t\tPID\t\t\tSTATE\t\t\tPRIO\t\t\tST_PRIO\t\t\tNORM_PRIO\n");
			print_string(buf);
			snprintf(buf, MAX_BUF_SIZE,"%s\t\t\t%d\t\t\t%ld\t\t\t%d\t\t\t%d\t\t\t%d",iter->comm, iter->pid, iter->state, iter->prio, iter->static_prio, iter->normal_prio);
			print_string(buf);
			piter = iter->parent;
			snprintf(buf, MAX_BUF_SIZE, "PARENT\n");
			print_string(buf);
			snprintf(buf, MAX_BUF_SIZE,"%s\t\t\t%d\t\t\t%ld\t\t\t%d\t\t\t%d\t\t\t%d",piter->comm, piter->pid, piter->state, piter->prio, piter->static_prio, piter->normal_prio);
			print_string(buf);
			snprintf(buf, MAX_BUF_SIZE, "CHILDREN\n");
                        print_string(buf);
			list_for_each(listc, &iter->children){
				struct task_struct* temp;
				temp = list_entry(listc, struct task_struct, sibling);
				snprintf(buf, MAX_BUF_SIZE,"%s\t\t\t%d\t\t\t%ld\t\t\t%d\t\t\t%d\t\t\t%d",temp->comm, temp->pid, temp->state, temp->prio, temp->static_prio, temp->normal_prio);
                       		print_string(buf);
			}
			snprintf(buf, MAX_BUF_SIZE, "\n\n");
			print_string(buf);
		}
	}
	return 0;
}

static void __exit exit_func(void){
	print_string("Module removed!");
}

module_init(init_func);
module_exit(exit_func);

MODULE_LICENSE("GPL");
