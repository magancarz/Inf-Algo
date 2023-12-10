package main

import (
    "fmt"
    "math/rand"
    "time"
)

const (
    n = 2
)

func philosopher(forks* []chan int, diner* chan int, i int) {
    for {
        fmt.Printf("Philosopher %d thinks.\n", i)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        (*diner) <- 1
        (*forks)[i] <- 1
        (*forks)[(i + 1) % n] <- 1
        fmt.Printf("Philosopher %d eats.\n", i)
        time.Sleep(time.Duration(rand.Intn(5)) * 50 * time.Millisecond)
        <- (*forks)[i]
        <- (*forks)[(i + 1) % n]
        <- (*diner)
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())
    
    forks := make([]chan int, n)

    for i := 0; i < n; i++ {
        forks[i] = make(chan int, 1)
    }

    diner := make(chan int, n - 1)

    for i := 0; i < n; i++ {
        go philosopher(&forks, &diner, i)
    }

    time.Sleep(time.Duration(50 * time.Second))
}