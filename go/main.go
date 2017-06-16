package main

import "net/http" //导入net/http包

func main(){
    http.HandleFunc("/hello",hello) //在网络服务器的跟路径下安装一个处理函数，每次和根路径相匹配的一个新的请求到达HTTP服务器时，服务器将生成一个新的goroutine执行hello函数。

    http.HandleFunc("/hello1",hello1)
    //通过http.ListenAndServe用默认的ServeMux启动HTTP服务器的8080端口。这是阻塞调用.
    http.ListenAndServe(":8080",nil)
}

//hello函数使用http.ResponseWriter写一个响应给客户端
func hello(w http.ResponseWriter,r *http.Request){
    w.Write([]byte("hello!"))    
}



func hello1(w http.ResponseWriter,r *http.Request){
    w.Write([]byte("hello1!"))    
}
