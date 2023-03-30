#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <chrono>
#include <array>
#include <cstdint>
#include <random>

using namespace std;

constexpr int N = 4;

struct Test {
	uint32_t test1;
    uint8_t test2;
};

std::vector<Test> test_vec;

struct State {
    std::array<std::array<uint8_t, N>, N> board;
    struct alignas(1) {
        uint8_t zero_row;
        uint8_t zero_col;
        uint8_t g : 8;
        uint8_t h : 8;
        uint8_t f : 8;
    };
    uint32_t test;

    bool operator<(const State& rhs) const {
	    return f > rhs.f;
    }

    bool operator==(const State& other) const {
        return board == other.board && zero_row == other.zero_row && zero_col == other.zero_col;
    }

    /*std::vector<int> getPath() const {
        std::vector<int> path;
        path.emplace_back(path_element->current_move);

        auto current = path_element->parent;
        while (current != nullptr) {
            path.push_back(current->current_move);
            current = current->parent;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }*/
};

uint32_t MurmurHash32(const void *key, int len, uint32_t seed) {
    const uint8_t *data = (const uint8_t *)key;
    const int nblocks = len >> 2;

    uint32_t hash = seed;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    // Process the data in 4-byte blocks
    const uint32_t *blocks = (const uint32_t *)(data + nblocks * 4);
    for (int i = -nblocks; i; i++) {
        uint32_t k = blocks[i];

        k *= c1;
        k = (k << 15) | (k >> 17);  // Rotates the bits to the left
        k *= c2;

        hash ^= k;
        hash = (hash << 13) | (hash >> 19);  // Rotates the bits to the left
        hash = hash * 5 + 0xe6546b64;
    }

    // Process any remaining bytes
    const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);
    uint32_t k1 = 0;
    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << 15) | (k1 >> 17);
            k1 *= c2;
            hash ^= k1;
    }

    // Finalize the hash
    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

uint8_t h1(const State& s) {
    uint8_t result = 0;
    for (uint8_t i = 0; i < N; ++i) {
        for (uint8_t j = 0; j < N; ++j) {
            if (s.board[i][j] != 0) {
                const uint8_t row = (s.board[i][j] - 1) >> 2; // N = 4
                const uint8_t col = (s.board[i][j] - 1) % N;
                result += abs(i - row) + abs(j - col);
            }
        }
    }
    return result;
}

int h2(const State& s) {
    int result = 0;
    int count = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s.board[i][j] != count && s.board[i][j] != 0) {
                ++result;
            }
            ++count;
        }
    }
    return result;
}

void printBoard(std::array<std::array<uint8_t, N>, N> board) {
    cout << endl;
    for (uint8_t i = 0; i < N; ++i) {
        for (uint8_t j = 0; j < N; ++j) {
            if (board[i][j] == 0) {
                cout << "x ";
            } else {
                cout << static_cast<int>(board[i][j]) << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isGoalState(const State& s) {
	if (s.board[N - 1][N - 1] != 0)
		return false;

    uint8_t count = 1;
    for (uint8_t i = 0; i < N; ++i) {
        for (uint8_t j = 0; j < N; ++j) {
            if (s.board[i][j] != count && s.board[i][j] != 0) {
                return false;
            }
            ++count;
        }
    }
    return true;
}

vector<State> getSuccessors(const State& s) {
    vector<State> successors;
    const uint8_t r = s.zero_row;
    const uint8_t c = s.zero_col;

    // up
    if (r > 0) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r-1][c]);
        temp.zero_row = r-1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        temp.f = temp.g + temp.h;

        /*const auto path_element = new PathElement{
			s.path_element,
            temp.board[r][c]
        };
        temp.path_element = path_element;*/
        test_vec.push_back({1024, 5});
        successors.push_back(temp);
    }

	// down
    if (r < N-1) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r+1][c]);
        temp.zero_row = r+1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        temp.f = temp.g + temp.h;

        /*const auto path_element = new PathElement{
			s.path_element,
            temp.board[r][c]
        };
        temp.path_element = path_element;*/
        test_vec.push_back({1024, 5});
        successors.push_back(temp);
    }

    // left
    if (c > 0) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r][c-1]);
        temp.zero_col = c-1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        temp.f = temp.g + temp.h;

        /*const auto path_element = new PathElement{
			s.path_element,
            temp.board[r][c]
        };
        temp.path_element = path_element;*/
        test_vec.push_back({1024, 5});
        successors.push_back(temp);
    }

    // right
    if (c < N-1) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r][c+1]);
        temp.zero_col = c+1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        temp.f = temp.g + temp.h;

        /*const auto path_element = new PathElement{
			s.path_element,
            temp.board[r][c]
        };
        temp.path_element = path_element;*/
        test_vec.push_back({1024, 5});
        successors.push_back(temp);
    }
    return successors;
}

bool isSolvable(std::array<std::array<uint8_t, N>, N> board) {
    int inversions = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = i + 1; j < 16; j++) {
            if (board[i/4][i%4] && board[j/4][j%4] && board[i/4][i%4] > board[j/4][j%4]) {
                inversions++;
            }
        }
    }
    return (inversions % 2 == 0);
}

std::array<std::array<uint8_t, N>, N> generateRandomBoard() {
    auto board = std::array<std::array<uint8_t, N>, N>();
	do {
		// Initialize a random number generator engine
	    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	    std::default_random_engine randEngine(seed);
	    // Define a uniform distribution to generate random numbers between 0 and 15
	    uniform_int_distribution<int> randDist(0, 15);

	    // Initialize the board with values from 0 to 15 in random order
	    board = std::array<std::array<uint8_t, N>, N>();
	    int boardArr[16];
	    for (int i = 0; i < 16; i++) {
	        boardArr[i] = i;
	    }
	    shuffle(boardArr, boardArr + 16, randEngine);
	    for (int i = 0; i < 16; i++) {
	        board[i/4][i%4] = boardArr[i];
	    }

	    // Move 0 to the bottom right corner
	    int zeroRow, zeroCol;
	    for (int i = 0; i < 16; i++) {
	        if (board[i/4][i%4] == 0) {
	            zeroRow = i/4;
	            zeroCol = i%4;
	            break;
	        }
	    }
	    int lastRow = 3, lastCol = 3;
	    swap(board[zeroRow][zeroCol], board[lastRow][lastCol]);
	} while (!isSolvable(board));

    return board;
}

//void destroyPath(const PathElement* path_element) {
//    while (path_element != nullptr) {
//        destroyPath(path_element->parent);
//        delete path_element;
//    }
//}

void solvePuzzle() {
	const auto start = std::chrono::steady_clock::now();

    /*int board[N][N] = {
            {1, 8, 2},
            {0, 4, 3},
            {7, 6, 5}
    };*/
    /*int board[N][N] = {
            {13, 2, 10, 3},
            {1, 12, 8, 4},
            {5, 9, 6, 7},
            {15, 14, 11, 0}
    };*/
    /*int board[N][N] = {
            {6, 13, 7, 10},
            {8, 9, 11, 5},
            {15, 2, 12, 4},
            {14, 3, 1, 0}
    };*/

    const auto board = generateRandomBoard();

    cout << "Initial state: " << endl;
    printBoard(board);

    State initial_state{};
    for (uint8_t i = 0; i < N; ++i) {
        for (uint8_t j = 0; j < N; ++j) {
            initial_state.board[i][j] = static_cast<uint8_t>(board[i][j]);
            if (board[i][j] == 0) {
                initial_state.zero_row = i;
                initial_state.zero_col = j;
            }
        }
    }
    //initial_state.path_element = new PathElement{nullptr, 0};
    initial_state.g = 0;
    initial_state.h = h1(initial_state);
    initial_state.f = initial_state.g + initial_state.h;

    priority_queue<State> pq;
    pq.push(initial_state);

    unordered_set<uint32_t> visited_states;

    uint32_t visited_count = 0;

    while (!pq.empty()) {
        State current_state = pq.top();
        pq.pop();
        visited_states.insert(MurmurHash32(&current_state.board, sizeof(current_state.board), 0));
        ++visited_count;
        
        if (isGoalState(current_state)) {
            cout << "Number of visited states: " << visited_count << endl;
            cout << "Solution: ";
            /*for (const auto& step : current_state.getPath()) {
                cout << step << " ";
            }*/
            cout << endl;
			const auto end = std::chrono::steady_clock::now();

            std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms." << std::endl;

            return;
        }

        vector<State> successors = getSuccessors(current_state);
        for (const auto& successor : successors) {
            if (visited_states.find(MurmurHash32(&successor.board, sizeof(successor.board), 0)) == visited_states.end()) {
                pq.push(successor);
            }
        }
    }
}

void performanceTest() {
	for (int i = 0; i < 10; ++i) {
		
	}
}

int main() {
    solvePuzzle();
    return 0;
}