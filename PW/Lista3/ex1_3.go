package main

import (
    "fmt"
    "math/rand"
    "time"
)

const (
    n = 2
)

type Message struct {
    idx int
    delete int
}

func philosopher(forks* []chan int, i int, messages chan Message) {
    for {
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*forks)[i] <- 1
        (*forks)[(i + 1) % n] <- 1
        messages <- Message{i, 0}
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        <- (*forks)[i]
        <- (*forks)[(i + 1) % n]
        messages <- Message{i, 1}
    }
}

func reverse_philosopher(forks* []chan int, messages chan Message) {
    for {
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*forks)[0] <- 1
        (*forks)[n - 1] <- 1
        messages <- Message{n - 1, 0}
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        <- (*forks)[n - 1]
        <- (*forks)[0]
        messages <- Message{n - 1, 1}
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

    messages := make(chan Message)
    go print(messages)

    for i := 0; i < n - 1; i++ {
        go philosopher(&forks, i, messages)
    }

    go reverse_philosopher(&forks, messages)

    time.Sleep(time.Duration(2 * time.Second))
}