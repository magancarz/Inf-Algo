package main

import (
    "fmt"
    "math/rand"
    "time"
)

const (
    n = 5
    m = 2
)

type Monitor struct {
    ok_to_read  chan int
    ok_to_write chan int
    readers     int
    writing     bool
    lock        chan int
}

func (m *Monitor) startRead(i int) {
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
    <- m.lock
}

func (m *Monitor) stopRead(i int) {
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

    <- m.lock
}

func (m *Monitor) startWrite(i int) {
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
    <- m.lock
}

func (m *Monitor) stopWrite(i int) {
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

    <- m.lock
}

func philosopher(monitor *Monitor, i int) {
    for {
        fmt.Printf("Philosopher %d thinks.\n", i)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*monitor).takeFork(i)
        fmt.Printf("Philosopher %d eats.\n", i)
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

    for i := 0; i < n; i++ {
        go philosopher(&monitor, i)
    }

    time.Sleep(time.Duration(50 * time.Second))
}