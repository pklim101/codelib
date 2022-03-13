/*************************************************************************
    > File Name: aio.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2020年04月28日 星期二 17时17分40秒
 ************************************************************************/

#include<iostream>
#include<errno.h>
#include<aio.h>
#include<fcntl.h>
#include<string.h> //bzero()
#include<unistd.h> //close(fd)

using namespace std;

int main(){
  int fp = open("/opt/logs/access.log",O_RDONLY);
  if (fp < 0) {
    perror("open test.txt failed.");
    return 0;
  }

  struct aiocb rd;
  bzero(&rd, sizeof(rd));
  rd.aio_buf = malloc(1024000);
  rd.aio_fildes = fp;
  rd.aio_nbytes = 1023;
  rd.aio_offset = 0;

  //cblist链表：监听的
  struct aiocb *aiocb_list[2];
  //将fp的时间注册
  aiocb_list[0] = &rd;

  //进行异步读操作
  //在请求进行排队之后会立即返回，成功返回0，失败返回-1
  int ret = aio_read(&rd);
  if (ret < 0) {
    perror("aio_read failed.");
    exit(1);
  }

  //开始等待异步读事件完成
  ret = aio_suspend(aiocb_list, 2, NULL);

	//获取异步读的返回值
	ret = aio_return(&rd);
	cout << "return value:" << ret << endl;
	//cout << "return buf:" << rd.aio_buf << endl; //%s //为什么这里输出是1
  printf("%s\n",rd.aio_buf);
  cout << sizeof(rd.aio_buf) << endl;
  //free(rd.aio_buf); //从类型‘volatile void*’到类型‘void*’的转换无效
  free((void *)rd.aio_buf);
  close(fp);
	
  return 0;
}

