#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

bool isFirstByteInUtf8(const uint8_t& bits) { return (bits <= 127 || bits >= 192); }

void increaseIndexIfNecessary(uint64_t& index, const uint8_t currChar)
{
    if (isFirstByteInUtf8(currChar))
        index++;
}

uint32_t getSizeInUtf8(const std::string& pattern)
{
    int size = 0;

    for (uint8_t currChar : pattern)
    {
        if (isFirstByteInUtf8(currChar))
            size++;
    }

    return size;
}

class State
{
public:
    State()
    {
        this->map = std::map<uint8_t, int>();
    }

    int returnNewStateIndex(uint8_t currChar) { return this->map[currChar]; }
    void setStateIndex(uint8_t currChar, int stateIndex) { this->map[currChar] = stateIndex; }

private:
    std::map<uint8_t, int> map;
};

void setState(std::vector<State>& states, std::string& pattern, int patternSize, int i, char currChar)
{
    int currState = std::min(patternSize, i + 1);
    std::string patternSuffix(pattern.substr(i == patternSize ? 1 : 0, i) + currChar);

    while(currState > 0 && pattern.compare(0, currState, patternSuffix) != 0)
    {
        patternSuffix.erase(0, 1);
        currState--;
    }

    states[i].setStateIndex(currChar, currState);
}

std::vector<State> computeTF(std::string& pattern)
{
    int patternSize = pattern.size();
    std::vector<State> states(patternSize + 1, State{});
    for (int i = 0; i <= patternSize; ++i)
    {
        for (const char& currChar : pattern)
        {
            setState(states, pattern, patternSize, i, currChar);
        }
    }

    return states;
}

void FAMatcher(std::string& pattern, std::string& text)
{
    std::vector<State> states = computeTF(pattern);
    const uint32_t lastState = pattern.size();
    const uint32_t patternSize = getSizeInUtf8(pattern);

    uint32_t current_state = 0;
    uint64_t index = 0;

    for(char current_char : text)
    {
        current_state = states[current_state].returnNewStateIndex(current_char);
        increaseIndexIfNecessary(index, current_char);
        if (current_state == lastState)
            printf("%lu\n", index - patternSize);
    }
}

int main(int argc, char** argv) {
    std::string pattern = "abc";
    std::string text = "ababcabba";

    std::cout << "FA Matcher\n";
    FAMatcher(pattern, text);

    return 0;
}