package main

import (
    "fmt"
    "math/rand"
    "time"
)

const (
    n = 2
)

func philosopher(forks* []chan int, i int) {
    for {
        fmt.Printf("Philosopher %d thinks.\n", i)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*forks)[i] <- 1
        (*forks)[(i + 1) % n] <- 1
        fmt.Printf("Philosopher %d eats.\n", i)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        <- (*forks)[i]
        <- (*forks)[(i + 1) % n]
    }
}

func reverse_philosopher(forks* []chan int) {
    for {
        fmt.Printf("Philosopher %d thinks.\n", n - 1)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*forks)[0] <- 1
        (*forks)[n - 1] <- 1
        fmt.Printf("Philosopher %d eats.\n", n - 1)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        <- (*forks)[n - 1]
        <- (*forks)[0]
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())
    
    forks := make([]chan int, n)

    for i := 0; i < n; i++ {
        forks[i] = make(chan int, 1)
    }

    for i := 0; i < n - 1; i++ {
        go philosopher(&forks, i)
    }

    go reverse_philosopher(&forks)

    time.Sleep(time.Duration(50 * time.Second))
}