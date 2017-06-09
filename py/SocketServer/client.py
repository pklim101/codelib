
"""
使用方法: python client.py hello,this is a test demo.


"""

import socket
import sys

HOST, PORT = "localhost", 9999
data = "".join(sys.argv[1:])

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    sock.connect((HOST, PORT))
    sock.sendall(data + "\n")

    received = sock.recv(1024)
finally:
    sock.close()

print "Sent:        {}".format(data)
print "Received     {}".format(received)       
