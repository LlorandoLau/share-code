#include "header.h"

int isCFile(char*,const char*);
char *name[100]={0};

int main(int argc,char* argv[]){
	int i;
	int index=0;
	DIR* dir=opendir(".");
	const char* tail=argv[1];
	struct dirent* list;

	if(tail==NULL){
		printf("Failed\n");
		return 0;
	}
	while((list=readdir(dir))!=NULL)
	{
		if(list->d_type==4)
			continue;
		if(!isCFile(list->d_name,tail))
			continue;
		name[index++]=list->d_name;
	}
	for(i=0;name[i]!='\0';i++)
		printf("%s\n", name[i]);
	return 0;
}

int isCFile(char* s1,const char* s2)
{
	if(strstr(s1,s2)!=NULL)
		return 1;
	return 0;
}