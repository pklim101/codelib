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

//参考：https://blog.csdn.net/abraham_1/article/details/79824350

using namespace std;

int main(){
  int fp = open("./a.log",O_RDWR);
  if (fp < 0) {
    perror("open test.txt failed.");
    return 0;
  }

  struct aiocb rd;
  bzero(&rd, sizeof(rd));
  rd.aio_buf = malloc(1024);
  rd.aio_fildes = fp;
  rd.aio_nbytes = 1023;
  rd.aio_offset = 0;
  //进行异步读操作
  //在请求进行排队之后会立即返回，成功返回0，失败返回-1
  int ret = aio_read(&rd);
  if (ret < 0) {
    perror("aio_read failed.");
    exit(1);
  }

	//do other things.

  /**
	EINPROGRESS，说明请求尚未完成
	ECANCELLED，说明请求被应用程序取消了
	-1，说明发生了错误，具体错误原因可以查阅 errno
	0 ,说明完成当前请求
  */
	int count = 0;
  while (aio_error(&rd) == EINPROGRESS) {
		printf("the %d time read\n", ++count);
  }
	cout << "请求读的状态:" << aio_error(&rd) << endl;

	//获取异步读的返回值
	ret = aio_return(&rd);
	cout << "return value:" << ret << endl;
	cout << "return buf:" << rd.aio_buf << endl; //%s //为什么这里输出是1
  printf("%s\n",rd.aio_buf);
  //free(rd.aio_buf); //从类型‘volatile void*’到类型‘void*’的转换无效
  free((void *)rd.aio_buf);
  close(fp);
	
  return 0;
}

