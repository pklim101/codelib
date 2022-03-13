/*************************************************************************
    > File Name: test_cgi.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月19日 星期五 18时04分30秒
 ************************************************************************/

//#include <stdlib.h>
#include<stdio.h>

#include "include/fcgi_stdio.h"

int main(void)
{
  int count = 0;
  while(FCGI_Accept() >= 0) {
    printf("Content-type: text/html\r\n"
           "\r\n"

           "<title>FastCGI Hello!</title>"
           "<h1>FastCGI Hello!</h1>"
           "Request number %d running on host <i>%s</i>\n",
           ++count, getenv("SERVER_NAME"));

  }
	return 0;
}
