#include <errno.h>

#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h>

#include <sched.h>

#include <string.h>

 

static int fork_child(void *arg)

{

         int a = (int)arg;

         int i;

         pid_t pid;

         char *cmd  = "ps -el";

         printf("In the container, my pid is: %d\n", getpid());

 /*ps命令是解析procfs的内容得到结果的，而procfs根目录的进程pid目录是基于mount当时的pid namespace的，这个在procfs的get_sb回调中体现的。因此只需要重新mount一下proc, mount -t proc proc /proc*/

         mount("proc", "/proc", "proc", 0, "");
//指定创造子进程数量
         for (i = 0; i <a; i++) {

                   pid = fork();

                   if (pid <0)

                            return pid;

                   else if (pid)

                            printf("pid of my child is %d\n", pid);

                   else if (pid == 0) {

                            sleep(30);

                            exit(0);

                   }

         }

         execl("/bin/bash", "/bin/bash","-c",cmd, NULL);

         return 0;

}

int main(int argc, char *argv[])

{

         int cpid;

         void *childstack, *stack;

         int flags;

         int ret = 0;

         int stacksize = getpagesize() * 4;

         if (argc != 2) {

                   fprintf(stderr, "Wrong usage.\n");

                   return -1;

         }

         stack = malloc(stacksize);

         if(stack == NULL)

         {

                   return -1;

         }

         printf("Out of the container, my pid is: %d\n", getpid());

         childstack = stack + stacksize;

         flags = CLONE_NEWPID | CLONE_NEWNS;

         cpid = clone(fork_child, childstack, flags, (void *)atoi(argv[1]));

         printf("cpid: %d\n", cpid);

         if (cpid <0) {

                   perror("clone");

                   ret = -1;

                  goto out;

         }

         fprintf(stderr, "Parent sleeping 20 seconds\n");

         sleep(20);

         ret = 0;

out:

         free(stack);

         return ret;

}