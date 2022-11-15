#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

bool isFirstByteInUtf8(const uint8_t& bits) { return (bits <= 127 || bits >= 192); }

void increaseIndexIfNecessary(uint64_t& index, const uint8_t currChar) {
	if (isFirstByteInUtf8(currChar))
	    index++;
}

uint32_t getSizeInUtf8(const std::string& pattern) {
	int size = 0;

	for (uint8_t currChar : pattern) {
	    if (isFirstByteInUtf8(currChar))
		size++;
	}

	return size;
}

std::vector<int> computePI(std::string& pattern) {
    int pointer = -1;
    int patternSize = pattern.size();
    std::vector<int> pi = std::vector<int>(patternSize, -1);

    for (int i = 1; i < patternSize; i++) {
        while (pointer >= 0 && pattern[pointer + 1] != pattern[i])
            pointer = pi[pointer];
        if (pattern[pointer + 1] == pattern[i])
            pointer++;
        pi[i] = pointer;
    }

    return pi;
}

class State {
public:
    State() {this->map = std::map<uint8_t, int>(); }

    int returnNewStateIndex(uint8_t currChar) { return this->map[currChar]; }
    void setStateIndex(uint8_t currChar, int stateIndex) { this->map[currChar] = stateIndex; }

private:
    std::map<uint8_t, int> map;
};

void setState(std::vector<State>& states, std::string& pattern, int patternSize, int i, char currChar) {
    int currState = std::min(patternSize, i + 1);
    std::string patternSuffix(pattern.substr(i == patternSize ? 1 : 0, i) + currChar);

    while(currState > 0 && pattern.compare(0, currState, patternSuffix) != 0) {
        patternSuffix.erase(0, 1);
        currState--;
    }

    states[i].setStateIndex(currChar, currState);
}

std::vector<State> computeTF(std::string& pattern) {
    int patternSize = pattern.size();
    std::vector<State> states = std::vector<State>(patternSize + 1, State());
    for (int i = 0; i <= patternSize; i++) {
        for (const char& currChar : pattern) {
            setState(states, pattern, patternSize, i, currChar);
        }
    }
    
    return states;
}

void FAMatcher(std::string& pattern, std::string& txt) {
    std::vector<State> states = computeTF(pattern);
    const uint32_t lastState = pattern.size();
    const uint32_t patternSize = getSizeInUtf8(pattern);

    uint8_t currChar = 0;
    uint32_t currState = 0;
    uint64_t index = 0;

    for(int i = 0; i < txt.size(); i++) {
    	currChar = txt[i];
        currState = states[currState].returnNewStateIndex(currChar);
        increaseIndexIfNecessary(index, currChar);
        if (currState == lastState)
            printf("%lu\n", index - patternSize);
    }
}

void KMPMatcher(std::string& pattern, std::string& text) {
	const std::vector<int> f = computePI(pattern);
    const uint32_t m = pattern.size() - 1;
    const uint32_t patternSize = getSizeInUtf8(pattern);

    uint8_t currChar = 0;
    uint64_t index = 0;
    int pointer = -1;

    for (int i = 0; i < text.size(); i++) {
    	currChar = text[i];
        increaseIndexIfNecessary(index, currChar);
        while (pointer >= 0 && currChar && uint8_t(pattern[pointer + 1]) != currChar)
            pointer = f[pointer];
        if (uint8_t(pattern[pointer + 1]) == currChar)
            pointer++;
        if (pointer == m) {
            printf("%lu\n", index - patternSize);
            pointer = f[pointer];
        }
    }
}

int main(int argc, char** argv) {
	//std::string pattern = argv[2];
    //std::string text = argv[3];
    
    std::string pattern = "号号";
    std::string text = "号号号号号号abba";

    std::cout << "FA Matcher\n";
    FAMatcher(pattern, text);

    std::cout << "KMP Matcher\n";
    KMPMatcher(pattern, text);

    /*
	if(strcmp(argv[1], "FA") == 0) {
		FAMatcher(pattern, text);
	}
	else if(strcmp(argv[1], "KMP") == 0) {
		KMPMatcher(pattern, text);
	}
    */

	return 0;
}