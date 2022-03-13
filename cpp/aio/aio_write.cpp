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
  //因为write中可以设置O_APPEND,所以可以不用设置aio_offset
  int fp = open("./a2.log",O_RDWR|O_APPEND);
  if (fp < 0) {
    perror("open test.txt failed.");
    return 0;
  }

  char str[] = {"hello,world!"}; //长度13，内容+"\0"

  struct aiocb rd;
  bzero(&rd, sizeof(rd));
  //rd.aio_buf = malloc(1024);
  rd.aio_buf = str;
  rd.aio_fildes = fp;
  rd.aio_nbytes = sizeof(str)-1; //-1是不用写入\0
  rd.aio_offset = 0; //写入文件的偏移量。如果设置了O_APPEND，则该项被忽略.
  //进行异步写操作
  //在请求进行排队之后会立即返回，成功返回0，失败返回-1
  int ret = aio_write(&rd);
  if (ret < 0) {
    perror("aio_write failed.");
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
		printf("the %d time write\n", ++count);
  }
	cout << "请求读的状态:" << aio_error(&rd) << endl;

	//获取异步读的返回值
	ret = aio_return(&rd);
	cout << "return value:" << ret << endl;
	cout << "return buf:" << rd.aio_buf << endl; //%s //为什么这里输出是1
  printf("%s\n",rd.aio_buf);
  //free((void *)rd.aio_buf); //难道不用释放吗？释放就段错误
  close(fp);
	
  return 0;
}

