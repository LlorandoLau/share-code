#include "head.h"
void printfdir(char*,int);
int main(int argc,char* argv[])
{
	char *topdir=".";
	if(argc>2)
		topdir=argv[1];

	printf("Directory scan of %s\n",topdir );
	printfdir(topdir,0);
	printf("done.\n");
	exit(0);
}

void printfdir(char *dir,int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if((dp=opendir(dir))==NULL){
		fprintf(stderr, "Failed to open %s\n",dir);
		return;
	}
	chdir(dir);
	while((entry=readdir(dp))!=NULL)
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(".",entry->d_name)==0 ||
				strcmp("..",entry->d_name)==0)
				continue;
			printf("%*s%s/\n",depth,"",entry->d_name );
			printfdir(entry->d_name,depth+4);
		}else		printf("%*s%s\n",depth,"",entry->d_name );
	}
	chdir("..");
	closedir(dp);
}