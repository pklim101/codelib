1.修改CGIHTTPServer.py为: cgi_directories = ['/cgi-bin', '/htbin', '/'],增加了"/";
  注意：程序里的含义是：只要在cgi_directories里的目录内的脚本，都属于cgi程序.
2.在thriftdemo目录下执行python CGIHTTPServer.py ，启动CGIHTTPServer服务，默认监听的是8000端口；
3.将server.php更改后缀为server.py，因为CGIHTTPServer.py里会判断是否在['.py','.pyc']里;
4.执行客户端脚本: php client.php --http
