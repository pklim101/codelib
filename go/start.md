# gostudy
===
`go` study note!

#一、配置环境变量GOPATH 
$ echo 'export GOPATH=$HOME/go' >> $HOME/.profile<br>
$ source $HOME/.profile<br>
$ go env | grep GOPATH<br>
GOPATH="/home/tom/go"<br>

#二、编辑器
Sublime Text<br>
GoSublime<br>
vim<br>

#三、hello
###1.创建github项目且clone到本地
$ mkdir -p $GOPATH/src/github.com/your-username<br>
$ cd $GOPATH/src/github.com/your-username<br>
$ git clone git@github.com:your-username/hello<br>
$ cd hello<br>
###2.vim main.go
```go
package main
func main() {
　　println("hello!")
}
```
###3.编译和执行
$ go build<br>
$ ./hello<br>
hello!<br>


#四、GC问题
1.0版本的GC问题在遇到内存中有大量数据需要回收的时候，会引起服务停顿甚至数秒，相当于服务中断状态，问题很严重，所以需要考虑到不要让内存中有大量数据.<br>
1.5版本解决了GC问题。
