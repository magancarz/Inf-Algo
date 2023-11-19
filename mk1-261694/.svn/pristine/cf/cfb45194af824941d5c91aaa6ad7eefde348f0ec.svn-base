package main

import (
    "fmt"
    "math/rand"
    "time"
)

const (
    m        = 8
    n        = 8
    k        = 5
    maxMoves = 10
)

type traveler struct {
    id   int
    x, y int
}

type Request struct {
    t *traveler
    move [2]int
    leave bool
}

type Response struct {
    allowed bool
}

type node struct {
    traveler *traveler
    occupied bool
    x, y int
    from_below int
    from_side  int
    requests chan Request
    responses chan Response
}

func (t *traveler) move(grid *[][]node) {
    directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
    for {
        var move = directions[rand.Intn(4)]
        var newX, newY = t.x + move[0], t.y + move[1]
        var oldX, oldY = t.x, t.y
        if newX >= 0 && newX < m && newY >= 0 && newY < n {
            (*grid)[newY][newX].requests <- Request{t, move, false}
            var response = <- (*grid)[newY][newX].responses
            if response.allowed {
                (*grid)[oldY][oldX].requests <- Request{t, move, true}
                <- (*grid)[oldY][oldX].responses
                return
            }
        }
    }
}

func server(node *node) {
    for {
        var request = <- (*node).requests
        if request.leave {
            (*node).occupied = false
            (*node).responses <- Response{allowed: true}

            if request.move[0] != 0 {
                if (node.x < request.t.x) {
                    (*node).from_side = 1
                }
            } else {
                if (node.y < request.t.y) {
                    (*node).from_below = 1
                }
            }
        } else {
            if node.occupied {
                (*node).responses <- Response{allowed: false}
            } else {
                (*node).occupied = true
                (*node).traveler = request.t

                var oldX, oldY = (*node).traveler.x, (*node).traveler.y
                (*node).traveler.x = node.x
                (*node).traveler.y = node.y

                if request.move[0] != 0 {
                    if (node.x < oldX) {
                        (*node).from_side = 1
                    }
                } else {
                    if (node.y < oldY) {
                        (*node).from_below = 1
                    }
                }
                (*node).responses <- Response{allowed: true}
            }
        }
    }
}

func travelerMovement(traveler *traveler, grid *[][]node, moves int) {
    for move := 0; move < moves; move++ {
        traveler.move(grid)
        time.Sleep(time.Duration(rand.Intn(10)) * 50 * time.Millisecond)
    }
}

func spawnTraveler(travelers *[]traveler, grid *[][]node, next_free_id *int) {
    var x, y int
    (*travelers)[(*next_free_id)] = traveler{id: (*next_free_id), x: x, y: y}
    var t  = &(*travelers)[(*next_free_id)]
    for {
        (*t).x = rand.Intn(m)
        (*t).y = rand.Intn(n)
        (*grid)[t.y][t.x].requests <- Request{t, [2]int{0, 0}, false}
        var response = <- (*grid)[t.y][t.x].responses
        if response.allowed {
            break
        }
    }
    (*next_free_id)++

    go travelerMovement(t, grid, maxMoves)
}

func spawnTravelers(travelers *[]traveler, grid *[][]node, next_free_id *int) {
    for {
        if (*next_free_id) < (m * n - 1) && rand.Intn(100) < 30 {
            spawnTraveler(travelers, grid, next_free_id)
        }
        time.Sleep(time.Duration(100 * time.Millisecond))
    }
}

func snap(move int, grid *[][]node) {
    fmt.Println("Move:", move)

    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            fmt.Print("\x1b[0m")
            if (*grid)[i][j].occupied {
                fmt.Printf("%2d", (*grid)[i][j].traveler.id)
            } else {
                fmt.Print("  ")
            }
            if (*grid)[i][j].from_side == 1 {
                fmt.Print("\x1b[31m")
            } else {
                fmt.Print("\x1b[0m")
            }
            fmt.Print("|")
        }
        fmt.Println()
        for k := 0; k < n; k++ {
            if (*grid)[i][k].from_below == 1 {
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
            (*grid)[i][j].from_side = -1
            (*grid)[i][j].from_below = -1
        }
    }
}

func snapshot(grid *[][]node, moves int) {
    for move := 0; move < moves; move++ {
        time.Sleep(100 * time.Millisecond)
        snap(move, grid)
    }
}

func main() {
    rand.Seed(time.Now().UnixNano())

    grid := make([][]node, n)
    for i := range grid {
        grid[i] = make([]node, m)
    }

    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            var requests = make(chan Request)
            var responses = make(chan Response)
            grid[i][j].requests = requests
            grid[i][j].responses = responses
            grid[i][j].occupied = false
            grid[i][j].x = j
            grid[i][j].y = i
            go server(&grid[i][j])
        }
    }

    var next_free_id = 0
    travelers := make([]traveler, (m * n) - 1)
    for i := 0; i < k; i++ {
        spawnTraveler(&travelers, &grid, &next_free_id)
    }

    for i := 0; i < k; i++ {
        go travelerMovement(&travelers[i], &grid, maxMoves)
    }

    go snapshot(&grid, maxMoves)

    go spawnTravelers(&travelers, &grid, &next_free_id)

    time.Sleep(5 * time.Second)
}
