package main

import (
    "fmt"
    "math/rand"
    "sync"
    "time"
)

const (
    m        = 5
    n        = 5
    k        = 5
    maxMoves = 10
)

type traveler struct {
    id   int
    x, y int
}

type move_track struct {
    from_below int
    from_side  int
}

var mutex sync.Mutex

func (t *traveler) move(grid *[][]int, move_grid *[][]move_track) {
    mutex.Lock()
    defer mutex.Unlock()

    directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
    var move [2]int
    var newX, newY int
    num_of_iterations := 0
    for num_of_iterations < 10 {
        move = directions[rand.Intn(4)]
        newX, newY = t.x + move[0], t.y + move[1]
        if newX >= 0 && newX < m && newY >= 0 && newY < n && (*grid)[newX][newY] != 1 {
            break
        }
        num_of_iterations++
    }

    if num_of_iterations >= 10 {
        return
    }

    if newX >= 0 && newX < m && newY >= 0 && newY < n {
        if move[0] != 0 {
            var min int
            if (t.x < newX) {
                min = t.x
            } else {
                min = newX
            }

            (*move_grid)[min][t.y].from_below = 1
        } else {
            var min int
            if (t.y < newY) {
                min = t.y
            } else {
                min = newY
            }

            (*move_grid)[t.x][min].from_side = 1
        }
        (*grid)[t.x][t.y] = -1
        t.x, t.y = newX, newY
        (*grid)[t.x][t.y] = (*t).id
    }
}

func travelerMovement(traveler *traveler, grid *[][]int, move_grid *[][]move_track, moves int, wg *sync.WaitGroup) {
    defer wg.Done()

    for move := 0; move < moves; move++ {
        traveler.move(grid, move_grid)
        time.Sleep(time.Duration(rand.Intn(10)) * 50 * time.Millisecond)
    }
}

func spawnTraveler(travelers *[]traveler, grid *[][]int, next_free_id *int) {
    mutex.Lock()
    defer mutex.Unlock()

    var x, y int
    for {
        x = rand.Intn(m)
        y = rand.Intn(n)
        if (*grid)[x][y] == -1 {
            break
        }
    }
    (*grid)[x][y] = (*next_free_id)
    (*travelers)[(*next_free_id)] = traveler{id: (*next_free_id), x: x, y: y}
    (*next_free_id)++
}

func spawnTravelers(travelers *[]traveler, grid *[][]int, next_free_id *int, wg *sync.WaitGroup) {
    defer wg.Done()

    for i := 0; i < 10; i++ {
        if (*next_free_id) < (m * n - 1) && rand.Intn(100) < 30 {
            spawnTraveler(travelers, grid, next_free_id)
        }
        time.Sleep(time.Duration(100 * time.Millisecond))
    }
}

func snap(move int, travelers *[]traveler, move_grid *[][]move_track, grid *[][]int, moves int, wg *sync.WaitGroup) {
    fmt.Println("Move:", move)

    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            fmt.Print("\x1b[0m")
            if (*grid)[i][j] == -1 {
                fmt.Print("  ")
            } else {
                fmt.Printf("%2d", (*grid)[i][j])
            }
            if (*move_grid)[i][j].from_side == 1 {
                fmt.Print("\x1b[31m")
            } else {
                fmt.Print("\x1b[0m")
            }
            fmt.Print("|")
        }
        fmt.Println()
        for k := 0; k < n; k++ {
            if (*move_grid)[i][k].from_below == 1 {
                fmt.Print("\x1b[31m")
            } else {
                fmt.Print("\x1b[0m")
            }
            fmt.Print("---")
        }
        fmt.Println()
    }
    fmt.Println()
    
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            (*move_grid)[i][j].from_side = -1
            (*move_grid)[i][j].from_below = -1
        }
    }
}

func snapshot(travelers *[]traveler, move_grid *[][]move_track, grid *[][]int, moves int, wg *sync.WaitGroup) {
    defer wg.Done()

    for move := 0; move < moves; move++ {
        snap(move, travelers, move_grid, grid, maxMoves, wg)
        time.Sleep(100 * time.Millisecond)
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())

    grid := make([][]int, m)
    for i := range grid {
        grid[i] = make([]int, n)
    }

    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            grid[i][j] = -1
        }
    }

    move_grid := make([][]move_track, m)
    for i := range move_grid {
        move_grid[i] = make([]move_track, n)
    }

    var next_free_id = 0
    travelers := make([]traveler, (m * n) - 1)
    for i := 0; i < k; i++ {
        spawnTraveler(&travelers, &grid, &next_free_id)
    }

    var wg sync.WaitGroup

    for i := 0; i < k; i++ {
        wg.Add(1)
        go travelerMovement(&travelers[i], &grid, &move_grid, maxMoves, &wg)
    }

    wg.Add(1)
    go snapshot(&travelers, &move_grid, &grid, maxMoves, &wg)

    wg.Add(1)
    go spawnTravelers(&travelers, &grid, &next_free_id, &wg)

    wg.Wait()
}
