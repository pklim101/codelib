#!/bin/env python
#!encoding:utf-8

#################################
# flask quick start.
#################################
# Usage:
#   export FLASK_APP=flask_start.py 
#   flask run
#   curl "http://127.0.0.1:5000"

from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello, World!'
