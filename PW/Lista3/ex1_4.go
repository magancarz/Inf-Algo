package main

import (
    "fmt"
    "math/rand"
    "time"
    "sync"
)

const (
    n = 5
)

type Monitor struct {
    forks     [n]int
    ok_to_eat [n]chan int
    mu        sync.Mutex
}

func (m *Monitor) takeFork(i int) {
    m.mu.Lock()
    // Monitor.enter
    if m.forks[i] != 2 {
        // Monitor.leave
        m.mu.Unlock()
        select {
        case <-m.ok_to_eat[i]:
        default:
        }
        <-m.ok_to_eat[i]
        m.mu.Lock()
    }

    m.forks[(i + 1) % n] -= 1
    m.forks[(i - 1 + n) % n] -= 1
    m.mu.Unlock()
    // Monitor.leave
}

func (m *Monitor) releaseFork(i int) {
    m.mu.Lock()
    // Monitor.enter
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
    m.mu.Unlock()
    // Monitor.leave
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

    for i := 0; i < n; i++ {
        go philosopher(&monitor, i)
    }

    time.Sleep(time.Duration(50 * time.Second))
}