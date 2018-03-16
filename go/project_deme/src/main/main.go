package main

import ( 
    "fmt"
    math "net.duokr/math" //引用的方法是从main包平行的文件夹net.duokr开始，后面跟上包名math. 给这个长长的包名起了一个别名就叫math.
)

func main() {
    var a = 100
    var b = 200


    fmt.Println("Add demo:", math.Add(a, b))
    fmt.Println("Subtract demo:", math.Subtract(a, b))
    fmt.Println("Divide demo:", math.Divide(a, b))
}
