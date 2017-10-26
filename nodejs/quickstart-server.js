var http = require("http")

//创建服务器:参数为匿名函数
http.createServer(function (request, response){
    //发送HTTP头
    response.writeHead(200, {'Content-Type':'text/plain'});
    //发送相应数据
    response.end('Hello World\n')

}).listen(8888);

//终端启动server的时候打印启动信息
console.log('Server running at http://127.0.0.1:8888/');
