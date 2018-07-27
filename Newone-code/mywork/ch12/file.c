#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
	int fd=open("/dev/fb0",O_RDWR);
	
	char buf[800*480];
	int i,j;
	for(i=0;i<800;i++)
	{
		for(j=0;j<480;j++)
			buf=0x000000ff;
	}

	write(fd,buf,sizeof(buf));

	// ssize_t num=read(fd,buf,256);
	// if(num<0){
	// 	strcpy(buf,"Look me");
	// }else{
	// 	printf("%s\n",buf );
	// }
	// lseek(fd,2,SEEK_SET);
	// num=write(fd,buf,sizeof(buf));
	// printf("%ld\n",num );
	// printf("%ld\n",write(fd,buf,strlen(buf)-1) );
}