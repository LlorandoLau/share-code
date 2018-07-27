#include "header.h"
/*getrlimit(int resource, struct rlimit *r_limit);
	return 0: Success
	return -1: Failed
  getrusage(int who, struct rusage *r_usage);
*/
void display_limit(int,struct rlimit*);
int main()
{
	struct rlimit r_limit;
	int pri=getpriority(PRIO_PROCESS,getpid());
	printf("%d\n",pri );

	display_limit(RLIMIT_CORE,&r_limit);
}

void display_limit(int rer,struct rlimit *r_limit)
{
	getrlimit(rer,r_limit);
	printf("Min is %ld, Max is %ld\n",r_limit->rlim_cur,r_limit->rlim_max );
}

