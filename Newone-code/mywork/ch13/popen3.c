#include "header.h"
void read_chars(char* ,char* ,char* ,int );
int main()
{
	char buf[BUFSIZ + 1];
	memset(buf, '\0', sizeof(buf));
	read_chars("ps ax","r",buf,BUFSIZ);
}

void read_chars(char* path,char* mode,char* buf,int size)
{
	FILE* read_fp=popen(path,mode);
	int char_read;
	if(read_fp!=NULL)
	{
		char_read=fread(buf,sizeof(char),size,read_fp);
		while(char_read>0)
		{
			buf[char_read-1]='\0';
			printf("%s\n", buf);
			char_read=fread(buf,sizeof(char),size,read_fp);
		}
		pclose(read_fp);
		exit(0);
	}
	exit(1);
}