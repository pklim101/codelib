/**
 * Go 语言中数组可以存储同一类型的数据，但在结构体中我们可以为不同项定义不同的数据类型。
 *
 * 结构体表示一项记录,比如一条个人信息.
 * type 语句设定了结构体的名称.
 * struct 语句定义一个新的数据类型
*/

package main

import "fmt"

type Students struct {
    name string
    age int
    class int
}

func main(){
    var stu1 Students
    var stu2 Students

    stu1.name = "jim"
    stu1.age  = 16

    
    stu2.name = "Amy"
    stu2.age  = 12

    fmt.Printf("stu1 name : %s\n", stu1.name)
    fmt.Printf("stu1 age : %d\n", stu1.age)

    fmt.Printf("stu2 name : %s\n", stu2.name)
    fmt.Printf("stu2 age: %d\n\n", stu2.age)

    printStudent(stu1)
}

# 结构体作为参数传入函数.
func printStudent(stu Students){
    fmt.Printf("stu age: %d\n", stu.age)
}
