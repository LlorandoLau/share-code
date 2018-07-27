#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void display_time(time_t);
int main()
{
	time_t _time;
	size_t t;
	char buf[256];
	struct tm tm1;

	_time=time((time_t*)0);
	
	strcpy(buf,"Thu 26 July 2007, 17:53 will do fine");
	t=strftime(buf,256,"%Y-%m-%d %I:%M:%S",localtime(&_time));

	// printf("ctime func: %s",ctime(&_time));
	// printf("asctime func: %s",asctime(localtime(&_time)));
	printf("strftime func: %s, and it deal %u char\n",buf,t);

	char* result=strptime(buf,"%Y-%m-%d %I:%M:%S",&tm1);

}

void display_time(time_t time_val)
{
	struct tm *tmStruct=localtime(&time_val);
	printf("%d-%d-%d %d:%d:%d\n",tmStruct->tm_year, tmStruct->tm_mon,tmStruct->tm_mday,
		tmStruct->tm_hour,tmStruct->tm_min,tmStruct->tm_sec);

	printf("Weekday is %d\n", tmStruct->tm_wday);
	printf("Is the No.%d of this year\n", tmStruct->tm_yday);
	printf("Whether is summer time: %d\n",tmStruct->tm_isdst );
}