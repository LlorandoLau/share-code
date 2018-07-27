#include "header.h"
int main(int argc, char const *argv[])
{
	int running=1;
	int msgid;
	struct msg_st data;
	long int rece=0;

	msgid=msgget((key_t)1234,0666|IPC_CREAT);

	while(running)
	{
		/*rece：接受优先级
		  msgflg：没有对应类型时的应对措施
		  			IPC_NOWAIT：立即返回-1
		  			0：挂起等待
		*/
		msgrcv(msgid,(void*)&data,BUFSIZ,rece,0);
		printf("You wrote %s\n", data.message);
		if(strncmp(data.message,"end",3)==0)
			running=0;
	}

	msgctl(msgid,IPC_RMID,0);
	
	return 0;
}