#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <random>

using namespace std;

const int N = 4; //rozmiar planszy

//Struktura reprezentująca stan planszy
struct State {
    int board[N][N];
    int g; //koszt dotychczasowy
    int h; //heurystyka
    int f; //funkcja celu f = g + h
    int zero_row; //numer wiersza z zerem
    int zero_col; //numer kolumny z zerem
    vector<int> path; //ścieżka od stanu początkowego
    bool operator<(const State& rhs) const { return f > rhs.f; } //operator porównania dla kolejki priorytetowej
};

//Funkcja heurystyczna nr 1: liczba elementów nie na swoim miejscu
int h1(State& s) {
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

//Funkcja heurystyczna nr 2: suma odległości każdego elementu od jego pozycji w stanie docelowym
int h2(State& s) {
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
void shuffleBoard(int board[N][N]) {
    vector<int> v;
    for (int i = 0; i < N*N; ++i) {
        v.push_back(i);
    }
    random_shuffle(v.begin(), v.end());
    int index = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = v[index++];
        }
    }
}

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

//Funkcja sprawdzająca, czy dany stan jest stanem docelowym
bool isGoalState(State& s) {
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

//Funkcja zwracająca listę następników danego stanu
vector<State> getSuccessors(State& s) {
    vector<State> successors;
    int r = s.zero_row;
    int c = s.zero_col;
//przesunięcie pustego pola w górę
    if (r > 0) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r-1][c]);
        temp.zero_row = r-1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r-1][c]);
        successors.push_back(temp);
    }
//przesunięcie pustego pola w dół
    if (r < N-1) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r+1][c]);
        temp.zero_row = r+1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r+1][c]);
        successors.push_back(temp);
    }
//przesunięcie pustego pola w lewo
    if (c > 0) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r][c-1]);
        temp.zero_col = c-1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r][c-1]);
        successors.push_back(temp);
    }
//przesunięcie pustego pola w prawo
    if (c < N-1) {
        State temp = s;
        swap(temp.board[r][c], temp.board[r][c+1]);
        temp.zero_col = c+1;
        temp.g = s.g + 1;
        temp.h = h1(temp); //zmiana funkcji heurystycznej
        temp.f = temp.g + temp.h;
        temp.path.push_back(temp.board[r][c+1]);
        successors.push_back(temp);
    }
    return successors;
}

//Główna funkcja rozwiązująca 15 puzzle algorytmem A*
void solvePuzzle() {
//Generowanie losowej permutacji planszy
    int board[N][N];
    shuffleBoard(board);
    cout << "Stan początkowy:" << endl;
    printBoard(board);
//Inicjalizacja stanu początkowego
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

//Inicjalizacja kolejki priorytetowej i dodanie stanu początkowego do kolejki
    priority_queue<State> pq;
    pq.push(initial_state);

//Inicjalizacja zbioru odwiedzonych stanów
    set<int[N][N]> visited_states;
    visited_states.insert(initial_state.board);

//Licznik odwiedzonych stanów
    int visited_count = 1;

//Główna pętla algorytmu A*
    while (!pq.empty()) {
        //Pobranie stanu o najniższym f-wartości z kolejki
        State current_state = pq.top();
        pq.pop();
        //Sprawdzenie, czy to stan docelowy
        if (isGoalState(current_state)) {
            cout << "Liczba odwiedzonych stanów: " << visited_count << endl;
            cout << "Rozwiązanie: ";
            for (int i = 0; i < current_state.path.size(); ++i) {
                cout << current_state.path[i] << " ";
            }
            cout << endl;
            return;
        }
        //Generowanie następników i dodawanie ich do kolejki, jeśli nie były odwiedzone wcześniej
        vector<State> successors = getSuccessors(current_state);
        for (int i = 0; i < successors.size(); ++i) {
            if (visited_states.count(successors[i].board) == 0) {
                pq.push(successors[i]);
                visited_states.insert(successors[i].board);
                ++visited_count;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    solvePuzzle();
    return 0;
}