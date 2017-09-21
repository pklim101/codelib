#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/*
void (*signal(int sig, void (*func)(int)))(int) : 设置一个函数来处理信号。
参数：
    sig: 信号码；
    func：指向函数的指针.
*/

void sighandler(int);

int main(){

    //void (*signal(int sig, void (*func)(int)))(int);
    signal(SIGINT, sighandler);

    while(1){
        printf("sleep 1 second...\n");
        sleep(1);
    }
    return 0;

}

void sighandler(int signo){
    printf("捕获信号 %d ，跳出...\n", signo);
    exit(1);
}
