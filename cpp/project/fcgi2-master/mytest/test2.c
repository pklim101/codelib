/*************************************************************************
    > File Name: test2.c
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年06月22日 星期一 18时14分47秒
 ************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <alloca.h>
#include <fcgiapp.h>
#define LISTENSOCK_FILENO 0
#define LISTENSOCK_FLAGS 0
int main(int argc, char **argv)
{
  openlog("testfastcgi", LOG_CONS | LOG_NDELAY, LOG_USER);
  int err = FCGX_Init(); /* call before Accept in multithreaded apps */
  if (err)
  {
    syslog(LOG_INFO, "FCGX_Init failed: %d", err);
    return 1;
  }
  FCGX_Request cgi;
  err = FCGX_InitRequest(&cgi, LISTENSOCK_FILENO, LISTENSOCK_FLAGS);
  if (err)
  {
    syslog(LOG_INFO, "FCGX_InitRequest failed: %d", err);
    return 2;
  }
 
  while (1)
  {
    err = FCGX_Accept_r(&cgi);
    if (err)
    {
      syslog(LOG_INFO, "FCGX_Accept_r stopped: %d", err);
      break;
    }
    char **envp;
    int size = 200;
 
    char *result = (char *)alloca(size);
    strcpy(result, "Status: 200 OK\r\nContent-Type: text/html\r\n\r\n");
    strcat(result, "<html><h1>TestCGI!</h1></html>\r\n");
    FCGX_PutStr(result, strlen(result), cgi.out);
  }
 
  return 0;
}
