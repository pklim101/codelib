#!/bin/bash

#将项目路径加入GOPATH（在~/.bash_profile里已经加了export GOPATH=~/src/go/bin）里，这样一会编译main.go的时候才能找到我们自定义的包.
export GOPATH=$GOPATH:~/codelib/go/project_deme

#设置本项目的安装目录，go install main的命令将编译好的文件放到这个目录下面
export GOBIN=~/codelib/go/project_deme/bin

#编译自定义包
go build net.duokr/math

#编译main.go文件
go build main.go

#将编译好的文件安装到指定目录下
go install main
