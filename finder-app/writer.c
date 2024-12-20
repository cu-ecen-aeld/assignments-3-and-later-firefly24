#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char* argv[])
{
	
	openlog ("writer", LOG_PID | LOG_CONS, LOG_USER);
	if (argc != 3)
	{
		syslog(LOG_ERR,"Invalid arguments");
		closelog();
		return 1;
	}
	else
	{
		FILE *fp;
		fp= fopen(argv[1],"w");
		
		if (fp == NULL)
		{
			syslog(LOG_ERR,"File could not be created");
			closelog();
			return 1;
		}
		
		fprintf(fp,"%s",argv[2]);
		syslog(LOG_DEBUG,"Writing %s to %s",argv[2],argv[1]);
		
		fclose(fp);
	}
	closelog();
	return 0;
}

