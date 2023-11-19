package main

import (
    "fmt"
    "math/rand"
    "time"
)

const (
    m        = 4
    n        = 4
    k        = 5
    maxMoves = 40
    snap_sleep = 25
)

type traveler struct {
    id   int
    x, y int
    is_alive bool
}

type wild_locator struct {
    d    time.Duration
    x, y int
    is_alive bool
}

type bomb struct {
    d    time.Duration
    x, y int
    is_alive bool
}

type Request struct {
    response chan Response
    t *traveler
    wl *wild_locator
    b *bomb
    move [2]int
    leave bool
}

type Response struct {
    allowed bool
}

type node struct {
    traveler *traveler
    wild_locator *wild_locator
    bomb *bomb
    occupied bool
    mark rune
    x, y int
    from_below int
    from_side  int
    requests chan Request
}

func (t *traveler) move(grid *[][]node) {
    directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
    for {
        var move = directions[rand.Intn(4)]
        var newX, newY = t.x + move[0], t.y + move[1]
        var oldX, oldY = t.x, t.y
        if newX >= 0 && newX < m && newY >= 0 && newY < n {
            response_channel := make(chan Response)
            var request = Request{response_channel, t, nil, nil, move, false}
            (*grid)[newY][newX].requests <- request
            var response = <- response_channel
            if response.allowed {
                (*grid)[oldY][oldX].requests <- Request{response_channel, t, nil, nil, move, true}
                <- response_channel
                return
            }
        }
    }
}

func server(node *node, grid *[][]node) {
    for {
        var request = <- (*node).requests
        if request.leave {
            (*node).occupied = false
            (*node).traveler = nil
            (*node).wild_locator = nil
            (*node).bomb = nil

            if (request.move[0] == 1) {
                (*node).from_side = 1
            } else if (request.move[1] == 1) {
                (*node).from_below = 1
            }

            request.response <- Response{allowed: true}
        } else {
            if node.occupied {
                if request.t != nil {
                    if node.wild_locator != nil {
                        directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
                        var wild_locator_moved = false
                        for _, direction := range directions {
                            var newX, newY = node.x + direction[0], node.y + direction[1]
                            if (newX < 0 || newX >= m || newY < 0 || newY >= n) {
                                continue
                            }

                            response_channel := make(chan Response)
                            (*grid)[newY][newX].requests <- Request{response_channel, nil, node.wild_locator, nil, direction, false}
                            var response = <- response_channel
                            if response.allowed {
                                fmt.Printf("Wild locator was moved!\n")
                                (*node).occupied = false
                                (*node).traveler = nil
                                (*node).wild_locator = nil
                                (*node).bomb = nil

                                if (request.move[0] == -1) {
                                    (*node).from_side = 1
                                } else if (request.move[1] == -1) {
                                    (*node).from_below = 1
                                }

                                wild_locator_moved = true
                                break
                            }
                        }

                        if wild_locator_moved {
                            moveTravelerIntoNode(node, request)
                            continue
                        }
                    } else if node.bomb != nil {
                        fmt.Printf("%d was bombed!\n", request.t.id)
                        request.t.is_alive = false
                        (*node).bomb.is_alive = false
                        (*node).occupied = false
                        (*node).traveler = nil
                        (*node).wild_locator = nil
                        (*node).bomb = nil

                        if (request.move[0] == -1) {
                            (*node).from_side = 1
                        } else if (request.move[1] == -1) {
                            (*node).from_below = 1
                        }

                        request.response <- Response{allowed: true}
                        continue
                    }
                }

                request.response <- Response{allowed: false}
            } else {
                moveTravelerIntoNode(node, request)
            }
        }
    }
}

func moveTravelerIntoNode(node *node, request Request) {
    if request.wl != nil {
        (*node).wild_locator = request.wl
        (*node).mark = '*'

        (*node).wild_locator.x = node.x
        (*node).wild_locator.y = node.y
    } else if request.t != nil {
        (*node).traveler = request.t
        (*node).mark = rune(request.t.id + 48)

        (*node).traveler.x = node.x
        (*node).traveler.y = node.y
    } else if request.b != nil {
        (*node).bomb = request.b
        (*node).mark = rune('#')

        (*node).bomb.x = node.x
        (*node).bomb.y = node.y
    }

    if request.move[0] != 0 {
        if (request.move[0] == -1) {
            (*node).from_side = 1
        }
    } else if request.move[1] != 0 {
        if (request.move[1] == -1) {
            (*node).from_below = 1
        }
    }
    (*node).occupied = true
    request.response <- Response{allowed: true}
}

func travelerMovement(traveler *traveler, grid *[][]node, moves int) {
    for move := 0; move < moves; move++ {
        if traveler.is_alive {
            traveler.move(grid)
            time.Sleep(time.Duration(rand.Intn(10)) * 50 * time.Millisecond)
        } else {
            return
        }
    }
}

func spawnTraveler(travelers *[]traveler, grid *[][]node, next_free_id *int) {
    var x, y int
    (*travelers)[(*next_free_id)] = traveler{id: (*next_free_id), x: x, y: y, is_alive: true}
    var t = &(*travelers)[(*next_free_id)]
    response_channel := make(chan Response)
    for {
        (*t).x = rand.Intn(m)
        (*t).y = rand.Intn(n)
        (*grid)[t.y][t.x].requests <- Request{response_channel, t, nil, nil, [2]int{0, 0}, false}
        var response = <- response_channel
        if response.allowed {
            break
        }
    }

    fmt.Printf("%d was spawned!\n", (*next_free_id))

    (*next_free_id)++

    go travelerMovement(t, grid, maxMoves)
}

func spawnTravelers(travelers *[]traveler, grid *[][]node, next_free_id *int) {
    for {
        if (*next_free_id) < (m * n - 1) && rand.Intn(100) < 30 {
            spawnTraveler(travelers, grid, next_free_id)
        }
        time.Sleep(time.Duration(rand.Intn(10)) * 100 * time.Millisecond)
    }
}

func spawnWildLocators(wild_locators *[]wild_locator, grid *[][]node) {
    for {
        if rand.Intn(100) < 50 {
            index := -1
            for i := 0; i < len((*wild_locators)); i++ {
                if !(*wild_locators)[i].is_alive {
                    index = i
                    break
                }
            }
            if index == -1 {
                continue
            }
            spawnWildLocator(wild_locators, index, grid)
        }
        time.Sleep(time.Duration(rand.Intn(5)) * 100 * time.Millisecond)
    }
}

func spawnWildLocator(wild_locators *[]wild_locator, index int, grid *[][]node) {
    (*wild_locators)[index] = wild_locator{d: time.Duration(rand.Intn(10)) * 100 * time.Millisecond, x: 0, y: 0, is_alive: true}
    var wl = &(*wild_locators)[index]
    response_channel := make(chan Response)
    for {
        (*wl).x = rand.Intn(m)
        (*wl).y = rand.Intn(n)
        (*grid)[wl.y][wl.x].requests <- Request{response_channel, nil, wl, nil, [2]int{0, 0}, false}
        var response = <- response_channel
        if response.allowed {
            break
        }
    }

    fmt.Printf("Wild locator has spawned!\n")

    go wildLocatorLifetime(wl, wild_locators, index, grid)
}

func wildLocatorLifetime(wild_locator *wild_locator, wild_locators *[]wild_locator, index int, grid *[][]node) {
    time.Sleep(wild_locator.d)
    response_channel := make(chan Response)
    (*grid)[wild_locator.y][wild_locator.x].requests <- Request{response_channel, nil, wild_locator, nil, [2]int{0, 0}, true}
    <- response_channel
    (*wild_locators)[index].is_alive = false
    fmt.Printf("Wild locator is gone!\n")
}

func spawnBombs(bombs *[]bomb, grid *[][]node) {
    for {
        if rand.Intn(100) < 75 {
            index := -1
            for i := 0; i < len((*bombs)); i++ {
                if !(*bombs)[i].is_alive {
                    index = i
                    break
                }
            }
            if index == -1 {
                continue
            }
            spawnBomb(bombs, index, grid)
        }
        time.Sleep(time.Duration(rand.Intn(5)) * 100 * time.Millisecond)
    }
}

func spawnBomb(bombs *[]bomb, index int, grid *[][]node) {
    (*bombs)[index] = bomb{d: time.Duration(10) * 100 * time.Millisecond, x: 0, y: 0, is_alive: true}
    var b = &(*bombs)[index]
    response_channel := make(chan Response)
    for {
        (*b).x = rand.Intn(m)
        (*b).y = rand.Intn(n)
        (*grid)[b.y][b.x].requests <- Request{response_channel, nil, nil, b, [2]int{0, 0}, false}
        var response = <- response_channel
        if response.allowed {
            break
        }
    }

    fmt.Printf("Bomb has spawned!\n")

    go bombLifetime(b, bombs, index, grid)
}

func bombLifetime(bomb *bomb, bombs *[]bomb, index int, grid *[][]node) {
    time.Sleep(bomb.d)
    response_channel := make(chan Response)
    (*grid)[bomb.y][bomb.x].requests <- Request{response_channel, nil, nil, bomb, [2]int{0, 0}, true}
    <- response_channel
    (*bombs)[index].is_alive = false
    fmt.Printf("Bomb was destroyed!\n")
}

func snap(move int, grid [][]node) {
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            fmt.Print("\x1b[0m")
            if grid[i][j].occupied {
                fmt.Printf("%2c", rune(grid[i][j].mark))
            } else {
                fmt.Print("  ")
            }
            if grid[i][j].from_side == 1 {
                fmt.Print("\x1b[31m")
            } else {
                fmt.Print("\x1b[0m")
            }
            fmt.Print("|")
        }
        fmt.Println()
        for k := 0; k < n; k++ {
            if grid[i][k].from_below == 1 {
                fmt.Print("\x1b[31m")
            } else {
                fmt.Print("\x1b[0m")
            }
            fmt.Print("---")
        }
        fmt.Println()
    }
    fmt.Println()
}

func snapshot(grid *[][]node, moves int) {
    for move := 0; move < moves; move++ {
        time.Sleep(snap_sleep * time.Millisecond)
        snap(move, *grid)
        for i := 0; i < m; i++ {
            for j := 0; j < n; j++ {
                (*grid)[i][j].from_side = -1
                (*grid)[i][j].from_below = -1
            }
        }
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
            grid[i][j].requests = requests
            grid[i][j].occupied = false
            grid[i][j].x = j
            grid[i][j].y = i
            go server(&grid[i][j], &grid)
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

    wild_locators := make([]wild_locator, (m * n) - 1)
    bombs := make([]bomb, (m * n) - 1)

    go snapshot(&grid, maxMoves)

    go spawnTravelers(&travelers, &grid, &next_free_id)
    go spawnWildLocators(&wild_locators, &grid)
    go spawnBombs(&bombs, &grid)

    time.Sleep(1 * time.Second)
}
