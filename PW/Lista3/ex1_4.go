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

type Monitor struct {
    forks     [n]int
    ok_to_eat [n]chan int
    lock      chan int

    messages  chan Message
    current_list [n]int
}

func (m *Monitor) takeFork(i int) {
    m.lock <- 1
    if m.forks[i] != 2 {
        <- m.lock
        for {
            <-m.ok_to_eat[i]
            m.lock <- 1
            if m.forks[i] == 2 {
                break
            }
            <- m.lock
        }
    }

    m.forks[(i + 1) % n] -= 1
    m.forks[(i - 1 + n) % n] -= 1
    m.messages <- Message{i, 0}
    <- m.lock
}

func (m *Monitor) releaseFork(i int) {
    m.lock <- 1
    m.forks[(i + 1) % n] += 1
    m.forks[(i - 1 + n) % n] += 1

    if m.forks[(i + 1) % n] == 2 {
        select {
        case m.ok_to_eat[(i + 1) % n] <- 1:
        default:
        }
    }

    if m.forks[(i - 1 + n) % n] == 2 {
        select {
        case m.ok_to_eat[(i - 1 + n) % n] <- 1:
        default:
        }
    }
    m.messages <- Message{i, 1}

    <- m.lock
}

func (m *Monitor) print() {
    for {
        message := <- m.messages
        if message.delete == 1 {
            m.current_list[message.idx] = -1
        } else {
            m.current_list[message.idx] = 1
        }

        fmt.Printf("\n")
        for i := 0; i < n; i++ {
            if m.current_list[i] == 1 {
                fmt.Printf("(w_%d, f_%d, w_%d)\n", i, i, (i + 1) % n)
            }
        }
    }
}

func philosopher(monitor *Monitor, i int) {
    for {
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*monitor).takeFork(i)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*monitor).releaseFork(i)
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())
    
    var monitor Monitor
    for i := 0; i < n; i++ {
        monitor.ok_to_eat[i] = make(chan int, 1)
    }

    for i := 0; i < n; i++ {
        monitor.forks[i] = 2
    }

    monitor.lock = make(chan int, 1)
    monitor.messages = make(chan Message)
    go monitor.print()

    for i := 0; i < n; i++ {
        go philosopher(&monitor, i)
    }

    time.Sleep(time.Duration(2 * time.Second))
}