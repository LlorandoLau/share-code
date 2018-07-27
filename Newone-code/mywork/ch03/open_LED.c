#include <unistd.h>
int main()
{
	ioctl(tty_fd,KDSETLED,LED_NUM|LED_CAP|LED_SCR);
}