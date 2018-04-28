package main

/*
- concept:
Channels are the pipes that connect concurrent goroutines. You can send values into channels from one goroutine and receive those values into another goroutine.

- uage:
create a new channel : make(chan val-type)
send: channel <-
receive: <- channel

- block:
By default sends and receives block until both the sender and receiver are ready. This property allowed us to wait at the end of our program for the "ping" message without having to use any other synchronization.

*/


import "fmt"

func main() {
    messages := make(chan string)

    go func() { messages <- "ping" }()

    msg := <-messages
    fmt.Println(msg)

    msg_buffer := make(chan string, 2)
    msg_buffer <- "buffered"
    msg_buffer <- "channel"

    fmt.Println(<-msg_buffer)
    fmt.Println(<-msg_buffer)

}
