//============================================================================
// Name        : ZS-LRM100.cpp
// Author      : mh.najafi
// Version     :
// Copyright   : ZarrinSamaneh
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.h"



using namespace std;

void exec(const char* cmd,char *resultt,uint32_t time) {
    uint16_t cnt=0;
    clock_t clk,t=0;
    char buffer[1000],count;

	FILE* pipe = popen(cmd, "r");
	if (!pipe) printf("popen() failed!\n");
	try
	{
		memset(buffer,0,1000);
		memset(resultt,0,sizeof(resultt));
		t=time*1000;
		clk=clock();

		while(clock()-clk<t)
		{
			if (fgets(buffer, sizeof(buffer), pipe) != NULL)
			{

				memcpy(resultt+cnt,buffer,strlen(buffer));
				cnt+=strlen(buffer);
				//memcpy(resultt,buffer,sizeof(buffer));
				count=0;
				//printf("---------------------eeeee=%s\r\n",buffer);
			}
			else
			{
				count++;
				usleep(100);
				//if(count>20 && cnt>0) break;
			}

		}

	}
	catch (...)
	{
		pclose(pipe);
		//throw;
	}
	pclose(pipe);


}

int main()
{
	char str[2048];
	string ss;


	while(1)
	{
		memset(str,0,sizeof(str));
		exec("ps |grep ZS-CMU\0", str, 10);
		ss=str;
		int result1=ss.find("/usr/bin/ZS-CMU");


		memset(str,0,sizeof(str));
		exec("ps |grep ZS-MDM\0", str, 10);
		ss=str;
		int result2=ss.find("/usr/bin/ZS-MDM");


		if(result1<0) system("nice -19 /usr/bin/ZS-CMU &");

		if(result2<0) system("nice -15 /usr/bin/ZS-MDM &");


		sleep(10);

	}

	return 0;
}
