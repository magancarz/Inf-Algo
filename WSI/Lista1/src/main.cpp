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

using namespace std;

constexpr int N = 4;

struct State {
    std::array<std::array<int, N>, N> board;
    int g;
    int h;
    int f;
    int zero_row;
    int zero_col;
    vector<int> path;

    bool operator<(const State& rhs) const {
	    return f > rhs.f;
    }

    bool operator==(const State& other) const {
		if (zero_row != other.zero_row || zero_col != other.zero_col)
			return false;

        for (int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                if (board[y][x] != other.board[y][x]) {
                    return false;
                }
            }
        }

        return true;
    }
};

uint32_t MurmurHash32(const void *key, int len, uint32_t seed)
{
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

struct StateHash {
    size_t operator()(const State& s) const {

        constexpr uint32_t seed = 0;
        const auto board = s.board;
        const uint32_t hash_code = MurmurHash32(&board, sizeof(board), seed);

        return hash_code;
    }
};

int h1(const State& s) {
    int result = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s.board[i][j] != 0) {
                const int row = (s.board[i][j] - 1) / N;
                const int col = (s.board[i][j] - 1) % N;
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

void printBoard(int board[N][N]) {
    cout << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 0) {
                cout << " ";
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isGoalState(const State& s) {
	if (s.board[N - 1][N - 1] != 0)
		return false;

    int count = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
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
    const int r = s.zero_row;
    const int c = s.zero_col;

    // up
    if (r > 0) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r-1][c]);
        temp.zero_row = r-1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r][c]);
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
        temp.path.push_back(temp.board[r][c]);
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
        temp.path.push_back(temp.board[r][c]);
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
        temp.path.push_back(temp.board[r][c]);
        successors.push_back(temp);
    }
    return successors;
}

void solvePuzzle() {
	const auto start = std::chrono::steady_clock::now();

    int board[N][N] = {
            {13, 2, 10, 3},
            {1, 12, 8, 4},
            {5, 9, 6, 7},
            {15, 14, 11, 0}
    };
    cout << "Initial state: " << endl;
    printBoard(board);

    State initial_state;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            initial_state.board[i][j] = board[i][j];
            if (board[i][j] == 0) {
                initial_state.zero_row = i;
                initial_state.zero_col = j;
            }
        }
    }
    initial_state.g = 0;
    initial_state.h = h1(initial_state);
    initial_state.f = initial_state.g + initial_state.h;

    priority_queue<State> pq;
    pq.push(initial_state);

    unordered_set<State, StateHash> visited_states;

    int visited_count = 0;

    while (!pq.empty()) {
        State current_state = pq.top();
        pq.pop();
        visited_states.insert(current_state);
        ++visited_count;
        
        if (isGoalState(current_state)) {
            cout << "Number of visited states: " << visited_count << endl;
            cout << "Solution: ";
            for (const auto& step : current_state.path) {
                cout << step << " ";
            }
            cout << endl;
			const auto end = std::chrono::steady_clock::now();

            std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
            return;
        }

        vector<State> successors = getSuccessors(current_state);
        for (const auto& successor : successors) {
            if (visited_states.find(successor) == visited_states.end()) {
                pq.push(successor);
            }
        }
    }
}

int main() {
    solvePuzzle();
    return 0;
}