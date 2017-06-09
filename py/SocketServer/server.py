#!~/anaconda2/bin/python

import SocketServer


class MyTCPHandler(SocketServer.BaseRequestHandler):

    """
        1.self.request是在调用server.serve_forever()的时候，通过_handle_request_noblock里的get_request()方法获得的；
          而get_request()是通过创建的socket获得。
        2.MyTCPHandler类在server.serve_forever()阶段，通过finish_request()对它进行实例化时的构造函数中handler()触发调用request处理逻辑.

    """
    def handle(self):
        self.data = self.request.recv(1024).strip()
        print "{} wrote:".format(self.client_address[0])
        print self.data
        self.request.sendall(self.data.upper())


if __name__ == "__main__":
    HOST, PORT = "localhost", 9999
    server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
    server.serve_forever()


