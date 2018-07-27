#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*

SIGABRT	由调用abort函数产生，进程非正常退出
SIGALRM	用alarm函数设置的timer超时或setitimer函数设置的interval timer超时
SIGBUS	某种特定的硬件异常，通常由内存访问引起
SIGCANCEL	由Solaris Thread Library内部使用，通常不会使用
SIGCHLD	进程Terminate或Stop的时候，SIGCHLD会发送给它的父进程。缺省情况下该Signal会被忽略
SIGCONT	当被stop的进程恢复运行的时候，自动发送
SIGEMT	和实现相关的硬件异常
SIGFPE	数学相关的异常，如被0除，浮点溢出，等等
SIGFREEZE	Solaris专用，Hiberate或者Suspended时候发送
SIGHUP	发送给具有Terminal的Controlling Process，当terminal被disconnect时候发送
SIGILL	非法指令异常
SIGINFO	BSD signal。由Status Key产生，通常是CTRL+T。发送给所有Foreground Group的进程
SIGINT	由Interrupt Key产生，通常是CTRL+C或者DELETE。发送给所有ForeGround Group的进程
SIGIO	异步IO事件
SIGIOT	实现相关的硬件异常，一般对应SIGABRT
SIGKILL	无法处理和忽略。中止某个进程
SIGLWP	由Solaris Thread Libray内部使用
SIGPIPE	在reader中止之后写Pipe的时候发送
SIGPOLL	当某个事件发送给Pollable Device的时候发送
SIGPROF	Setitimer指定的Profiling Interval Timer所产生
SIGPWR	和系统相关。和UPS相关。
SIGQUIT	输入Quit Key的时候（CTRL+\）发送给所有Foreground Group的进程
SIGSEGV	非法内存访问
SIGSTKFLT	Linux专用，数学协处理器的栈异常
SIGSTOP	中止进程。无法处理和忽略。
SIGSYS	非法系统调用
SIGTERM	请求中止进程，kill命令缺省发送
SIGTHAW	Solaris专用，从Suspend恢复时候发送
SIGTRAP	实现相关的硬件异常。一般是调试异常
SIGTSTP	Suspend Key，一般是Ctrl+Z。发送给所有Foreground Group的进程
SIGTTIN	当Background Group的进程尝试读取Terminal的时候发送
SIGTTOU	当Background Group的进程尝试写Terminal的时候发送
SIGURG	当out-of-band data接收的时候可能发送
SIGUSR1	用户自定义signal 1
SIGUSR2	用户自定义signal 2
SIGVTALRM	setitimer函数设置的Virtual Interval Timer超时的时候
SIGWAITING	Solaris Thread Library内部实现专用
SIGWINCH	当Terminal的窗口大小改变的时候，发送给Foreground Group的所有进程
SIGXCPU	当CPU时间限制超时的时候
SIGXFSZ	进程超过文件大小限制
SIGXRES	Solaris专用，进程超过资源限制的时候发送
*/
int main()
{
	system("./madplay 1.mp3 &");
	printf("madplay 1.mp3\n");
	sleep(8);
	//暂停
	system("killall -19 madplay &");
	printf("-19\n");
	sleep(4);
	//恢复运行
	system("killall -18 madplay &");
	printf("-18\n");
	sleep(5);

	system("killall -9 madplay &");
	printf("-9\n");
	return 0;
}