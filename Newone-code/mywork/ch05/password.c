#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 8

int main()
{
	struct termios initial_settings,new_settings;
	char password[PASSWORD_LEN+1];

	tcgetattr(fileno(stdin),&initial_settings);
	new_settings=initial_settings;
	new_settings.c_lflag &= ~ECHO;

	printf("Enter password: ");
	/*TCSAFLUSH: 丢弃程序在准备好读取数据之前输入的任何内容
	  TCSANOW：恢复原始的设置
	*/
	if(tcsetattr(fileno(stdin),TCSAFLUSH,&new_settings)!=0)
		fprintf(stderr, "Counld not set attribute\n");
	else{
		fgets(password,PASSWORD_LEN,stdin);
		tcsetattr(fileno(stdin),TCSANOW,&initial_settings);
		fprintf(stdout, "\nYou enter %s\n", password);
	}
	exit(0);
}