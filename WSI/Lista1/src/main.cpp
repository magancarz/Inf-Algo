#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <chrono>

using namespace std;

const int N = 4; //rozmiar planszy

//Struktura reprezentuj�ca stan planszy
struct State {
    int board[N][N];
    int g; //koszt dotychczasowy
    int h; //heurystyka
    int f; //funkcja celu f = g + h
    int zero_row; //numer wiersza z zerem
    int zero_col; //numer kolumny z zerem
    vector<int> path; //�cie�ka od stanu pocz�tkowego
    bool operator<(const State& rhs) const { return f > rhs.f; } //operator por�wnania dla kolejki priorytetowej
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

struct StateHash {
	size_t operator()(const State& s) const {
		size_t hash_code = 0;
        const auto board = s.board;
	    for (int i = 0; i < N; i++) {
	        for (int j = 0; j < N; j++) {
	            hash_code = hash_code * 31 + board[i][j];
	        }
	    }
	    return hash_code;
	}
};

//Funkcja heurystyczna nr 1: liczba element�w nie na swoim miejscu
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

//Funkcja heurystyczna nr 2: suma odleg�o�ci ka�dego elementu od jego pozycji w stanie docelowym
int h1(const State& s) {
    int result = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s.board[i][j] != 0) {
                int row = (s.board[i][j] - 1) / N;
                int col = (s.board[i][j] - 1) % N;
                result += abs(i - row) + abs(j - col);
            }
        }
    }
    return result;
}

//Funkcja pomocnicza do generowania losowej permutacji planszy
//void shuffleBoard(int board[N][N]) {
//    vector<int> v;
//    for (int i = 0; i < N*N; ++i) {
//        v.push_back(i);
//    }
//    shuffle(v.begin(), v.end(), );
//    int index = 0;
//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N; ++j) {
//            board[i][j] = v[index++];
//        }
//    }
//}

//Funkcja pomocnicza do drukowania planszy
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

//Funkcja sprawdzaj�ca, czy dany stan jest stanem docelowym
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

//Funkcja zwracaj�ca list� nast�pnik�w danego stanu
vector<State> getSuccessors(const State& s) {
    vector<State> successors;
    int r = s.zero_row;
    int c = s.zero_col;
//przesuni�cie pustego pola w g�r�
    if (r > 0) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r-1][c]);
        temp.zero_row = r-1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r][c]);
        successors.push_back(temp);
    }
//przesuni�cie pustego pola w d�
    if (r < N-1) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r+1][c]);
        temp.zero_row = r+1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r][c]);
        successors.push_back(temp);
    }
//przesuni�cie pustego pola w lewo
    if (c > 0) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r][c-1]);
        temp.zero_col = c-1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r][c]);
        successors.push_back(temp);
    }
//przesuni�cie pustego pola w prawo
    if (c < N-1) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r][c+1]);
        temp.zero_col = c+1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r][c]);
        successors.push_back(temp);
    }
    return successors;
}

//G��wna funkcja rozwi�zuj�ca 15 puzzle algorytmem A*
void solvePuzzle() {
//Generowanie losowej permutacji planszy
	auto start = std::chrono::steady_clock::now();

    int board[N][N] = {
            {13, 2, 10, 3},
            {1, 12, 8, 4},
            {5, 9, 6, 7},
            {15, 14, 11, 0}
    };
    cout << "Stan pocz�tkowy:" << endl;
    printBoard(board);
//Inicjalizacja stanu pocz�tkowego
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
    initial_state.h = h1(initial_state); //zmiana funkcji heurystycznej
    initial_state.f = initial_state.g + initial_state.h;

//Inicjalizacja kolejki priorytetowej i dodanie stanu pocz�tkowego do kolejki
    priority_queue<State> pq;
    pq.push(initial_state);

//Inicjalizacja zbioru odwiedzonych stan�w
    unordered_set<State, StateHash> visited_states;

//Licznik odwiedzonych stan�w
    int visited_count = 0;

//G��wna p�tla algorytmu A*
    while (!pq.empty()) {
        //Pobranie stanu o najni�szym f-warto�ci z kolejki
        State current_state = pq.top();
        pq.pop();
        visited_states.insert(current_state);
        ++visited_count;

        //Sprawdzenie, czy to stan docelowy
        if (isGoalState(current_state)) {
            cout << "Liczba odwiedzonych stan�w: " << visited_count << endl;
            cout << "Rozwi�zanie: ";
            for (int i = 0; i < current_state.path.size(); ++i) {
                cout << current_state.path[i] << " ";
            }
            cout << endl;
			auto end = std::chrono::steady_clock::now();

            std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
            return;
        }
        //Generowanie nast�pnik�w i dodawanie ich do kolejki, je�li nie by�y odwiedzone wcze�niej
        vector<State> successors = getSuccessors(current_state);
        for (int i = 0; i < successors.size(); ++i) {
            if (visited_states.find(successors[i]) == visited_states.end()) {
                pq.push(successors[i]);
            }
        }
    }
}

int main() {
    srand(time(NULL));
    solvePuzzle();
    return 0;
}