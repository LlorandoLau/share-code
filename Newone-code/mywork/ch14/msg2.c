#include "header.h"

int main()
{
	int running=1;
	struct msg_st data;
	int msgid;
	char buffer[BUFSIZ];

	msgid=msgget((key_t)1234,0666|IPC_CREAT);

	while(running)
	{
		printf("Enter your text: ");
		fgets(buffer,BUFSIZ,stdin);
		data.msg_type=1;
		strcpy(data.message,buffer);

		msgsnd(msgid,(void*)&data,MAX_TEXT,0);

		if(strncmp(buffer,"end",3)==0)
			running=0;
	}
}