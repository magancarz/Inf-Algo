package main

import (
    "fmt"
    "math/rand"
    "time"
)

const (
    n = 5
)

type Message struct {
    idx int
    delete int
}

func philosopher(forks* []chan int, messages chan Message, diner* chan int, i int) {
    for {
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*diner) <- 1
        (*forks)[i] <- 1
        (*forks)[(i + 1) % n] <- 1
        messages <- Message{i, 0}
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        <- (*forks)[i]
        <- (*forks)[(i + 1) % n]
        <- (*diner)
        messages <- Message{i, 1}
    }
}

func print(messages chan Message) {
    var current_list [n]int

    for {
        message := <- messages
        if message.delete == 1 {
            current_list[message.idx] = -1
        } else {
            current_list[message.idx] = 1
        }

        fmt.Printf("\n")
        for i := 0; i < n; i++ {
            if current_list[i] == 1 {
                fmt.Printf("(w_%d, f_%d, w_%d)\n", i, i, (i + 1) % n)
            }
        }
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())
    
    forks := make([]chan int, n)

    for i := 0; i < n; i++ {
        forks[i] = make(chan int, 1)
    }

    diner := make(chan int, n - 1)

    messages := make(chan Message)
    go print(messages)

    for i := 0; i < n; i++ {
        go philosopher(&forks, messages, &diner, i)
    }

    time.Sleep(time.Duration(50 * time.Second))
}