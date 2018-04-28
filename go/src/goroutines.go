package main

/*
- usage:
use 'go' declare.
go f(s)


- output:
goroutine : 18
goroutine : 19
goroutine : 20
goroutine : 21
goroutine : 22
goroutine : 23
goroutine : 24
going
goroutine : 25
goroutine : 26
goroutine : 27
goroutine : 28
goroutine : 29
*/

import "fmt"

func f(from string) {
    for i:=0; i<30; i++ {
        fmt.Println(from, ":", i)
    }
}


func main() {
    f("direct")
    
    go f("goroutine")

    go func(msg string) {
        fmt.Println(msg)
    }("going")

    fmt.Scanln()
    fmt.Println("doing")

}

