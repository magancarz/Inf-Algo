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
#include <bitset>

constexpr int puzzle_size = 4;

struct PathElement {
	uint32_t parent;
    uint8_t value;
};

uint32_t current_path_element_index = 0;
std::vector<PathElement> path_elements;

struct State {
    uint64_t board;
    uint32_t path_element_ptr;
    uint8_t zero_row : 4;
    uint8_t zero_col : 4;
    uint8_t g : 8;
    uint8_t h : 8;

    bool operator<(const State& rhs) const {
	    return (g + h) > (rhs.g + rhs.h);
    }

    std::vector<int> getPath() const {
        std::vector<int> path;
        path.emplace_back(path_elements[path_element_ptr].value);

        auto current = path_elements[path_elements[path_element_ptr].parent];
        while (current.value != 0) {
            path.push_back(current.value);
            current = path_elements[current.parent];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    static uint64_t arrayToUint64(const std::array<std::array<uint8_t, puzzle_size>, puzzle_size>& arr) {

        std::bitset<64> result;

        for (int i = 0; i < puzzle_size; i++) {
            for (int j = 0; j < puzzle_size; j++) {
                std::bitset<64> temp{ arr[i][j] };
                temp <<= i * 16 + j * 4;
                result |= temp;
            }
        }

        return result.to_ullong();
    }

    static std::array<std::array<uint8_t, puzzle_size>, puzzle_size> uint64ToArray(const uint64_t value) {

        std::bitset<64> from_value{value};
        std::array<std::array<uint8_t, puzzle_size>, puzzle_size> result{};

        for (int i = 0; i < puzzle_size; i++) {
            for (int j = 0; j < puzzle_size; j++) {
                result[i][j] = (value >> i * 16 + j * 4) & 0xF;
            }
        }

        return result;
    }
};

uint8_t h1(const State& s) {

    const auto board = State::uint64ToArray(s.board);

    uint8_t result = 0;
    for (uint8_t i = 0; i < puzzle_size; ++i) {
        for (uint8_t j = 0; j < puzzle_size; ++j) {
            if (board[i][j] != 0) {
                const uint8_t row = (board[i][j] - 1) >> 2; // puzzle_size = 4
                const uint8_t col = (board[i][j] - 1) % puzzle_size;
                result += abs(i - row) + abs(j - col);
            }
        }
    }
    return result;
}

int h2(const State& s) {

	const auto board = State::uint64ToArray(s.board);

    int result = 0;
    int count = 1;
    for (int i = 0; i < puzzle_size; ++i) {
        for (int j = 0; j < puzzle_size; ++j) {
            if (board[i][j] != count && board[i][j] != 0) {
                ++result;
            }
            ++count;
        }
    }
    return result;
}

void printBoard(const std::array<std::array<uint8_t, puzzle_size>, puzzle_size>& board) {

    for (uint8_t i = 0; i < puzzle_size; ++i) {
        for (uint8_t j = 0; j < puzzle_size; ++j) {
            if (board[i][j] == 0) {
                std::cout << "x ";
            } else {
                std::cout << static_cast<int>(board[i][j]) << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isGoalState(const State& s) {

    const auto board = State::uint64ToArray(s.board);

	if (board[puzzle_size - 1][puzzle_size - 1] != 0)
		return false;

    uint8_t count = 1;
    for (uint8_t i = 0; i < puzzle_size; ++i) {
        for (uint8_t j = 0; j < puzzle_size; ++j) {
            if (board[i][j] != count && board[i][j] != 0) {
                return false;
            }
            ++count;
        }
    }
    return true;
}

std::vector<State> getSuccessors(const State& s) {

    std::vector<State> successors;
    const uint8_t r = s.zero_row;
    const uint8_t c = s.zero_col;

    const auto template_board = State::uint64ToArray(s.board);

    // up
    if (r > 0) {
		auto board = template_board;
        State temp = s;
        std::swap(board[r][c], board[r-1][c]);
        temp.board = State::arrayToUint64(board);
        temp.path_element_ptr = current_path_element_index++;
        temp.zero_row = r-1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        path_elements.push_back({s.path_element_ptr, board[r][c]});
        successors.push_back(temp);
    }

	// down
    if (r < puzzle_size-1) {
        auto board = template_board;
        State temp = s;
        std::swap(board[r][c], board[r+1][c]);
        temp.board = State::arrayToUint64(board);
        temp.path_element_ptr = current_path_element_index++;
        temp.zero_row = r+1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        path_elements.push_back({s.path_element_ptr, board[r][c]});
        successors.push_back(temp);
    }

    // left
    if (c > 0) {
        auto board = template_board;
        State temp = s;
        std::swap(board[r][c], board[r][c-1]);
        temp.board = State::arrayToUint64(board);
        temp.path_element_ptr = current_path_element_index++;
        temp.zero_col = c-1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        path_elements.push_back({s.path_element_ptr, board[r][c]});
        successors.push_back(temp);
    }

    // right
    if (c < puzzle_size-1) {
        auto board = template_board;
        State temp = s;
        std::swap(board[r][c], board[r][c+1]);
        temp.board = State::arrayToUint64(board);
        temp.path_element_ptr = current_path_element_index++;
        temp.zero_col = c+1;
        temp.g = s.g + 1;
        temp.h = h1(temp);
        path_elements.push_back({s.path_element_ptr, board[r][c]});
        successors.push_back(temp);
    }
    return successors;
}

bool isSolvable(const std::array<std::array<uint8_t, puzzle_size>, puzzle_size>& board) {

    int inversions = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = i + 1; j < 16; j++) {
            if (board[i / 4][i % 4] && board[j / 4][j % 4] && board[i / 4][i % 4] > board[j / 4][j % 4]) {
                ++inversions;
            }
        }
    }
    return (inversions % 2 == 0);
}

std::array<std::array<uint8_t, puzzle_size>, puzzle_size> generateRandomBoard() {

    auto board = std::array<std::array<uint8_t, puzzle_size>, puzzle_size>();
	do {
	    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	    std::default_random_engine default_random_engine{static_cast<unsigned int>(seed)};

	    std::uniform_int_distribution<int> rand_dist(0, 15);
        
	    board = std::array<std::array<uint8_t, puzzle_size>, puzzle_size>();
	    uint8_t board_arr[puzzle_size * puzzle_size];
	    for (uint8_t i = 0; i < puzzle_size * puzzle_size; i++) {
	        board_arr[i] = i;
	    }
	    shuffle(board_arr, board_arr + puzzle_size * puzzle_size, default_random_engine);
	    for (uint8_t i = 0; i < puzzle_size * puzzle_size; i++) {
	        board[i/4][i%4] = board_arr[i];
	    }
        
	    uint8_t zero_row, zero_col;
	    for (uint8_t i = 0; i < puzzle_size * puzzle_size; i++) {
	        if (board[i / 4][i % 4] == 0) {
	            zero_row = i / 4;
	            zero_col = i % 4;
	            break;
	        }
	    }
	    constexpr uint8_t last_row = 3, last_col = 3;
	    std::swap(board[zero_row][zero_col], board[last_row][last_col]);
	} while (!isSolvable(board));

    return board;
}

void solvePuzzle() {

	const auto start = std::chrono::steady_clock::now();

    // test cases
    /*const std::array<std::array<uint8_t, 4>, 4> board {{
            {13, 2, 10, 3},
            {1, 12, 8, 4},
            {5, 9, 6, 7},
            {15, 14, 11, 0}
    }};*/
    /*const std::array<std::array<uint8_t, 4>, 4> board {{
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 0, 14, 15}
    }};*/
    /*const std::array<std::array<uint8_t, 4>, 4> board {{
            {6, 13, 7, 10},
            {8, 9, 11, 5},
            {15, 2, 12, 4},
            {14, 3, 1, 0}
    }};*/

    const auto board = generateRandomBoard();

    std::cout << "Initial state: " << std::endl;
    printBoard(board);

    State initial_state{};
    initial_state.board = State::arrayToUint64(board);
    initial_state.zero_row = puzzle_size - 1;
    initial_state.zero_col = puzzle_size - 1;
    initial_state.g = 0;
    initial_state.h = h1(initial_state);
    initial_state.path_element_ptr = 0;
    path_elements.push_back({initial_state.path_element_ptr, 0});
    ++current_path_element_index;

    std::priority_queue<State> pq;
    pq.push(initial_state);

    std::unordered_set<uint64_t> visited_states;

    uint32_t visited_count = 0;

    while (!pq.empty()) {
        State current_state = pq.top();
        pq.pop();
        visited_states.insert(current_state.board);
        ++visited_count;
        
        if (isGoalState(current_state)) {
            std::cout << "Number of visited states: " << visited_count << std::endl;
            std::cout << "Solution: ";
            for (const auto& step : current_state.getPath()) {
                std::cout << step << " ";
            }
            std::cout << std::endl;
			const auto end = std::chrono::steady_clock::now();

            std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms." << std::endl;

            return;
        }

        std::vector<State> successors = getSuccessors(current_state);
        for (const auto& successor : successors) {
            if (visited_states.find(successor.board) == visited_states.end()) {
                pq.push(successor);
            }
        }
    }
}

void performanceTest() {
	for (int i = 0; i < 10; ++i) {
        {
			solvePuzzle();

		    path_elements.clear();
		    current_path_element_index = 0;
        }
		std::cout << "------------------------------\n";
	}
}

int main() {
	std::cout << "Size of State: " << sizeof(State) << "B" << std::endl;
	std::cout << "Size of PathElement: " << sizeof(PathElement) << "B" << std::endl;
    std::cout << std::endl;

    performanceTest();
    return 0;
}