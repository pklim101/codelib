#!/usr/bin/env python

import os
import sys
import BaseHTTPServer
import CGIHTTPServer

os.chdir(os.path.dirname(os.path.realpath(sys.argv[0])))

class Handler(CGIHTTPServer.CGIHTTPRequestHandler):
    cgi_directories = ['']

BaseHTTPServer.HTTPServer(('', 8080), Handler).serve_forever()
