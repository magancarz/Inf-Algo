#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
#define NO_OF_CHARS 256

int getPatternSize(std::string str) {
    int s = 0;
    for(int i = 0; i < str.size(); ) {
        std::bitset<8> c{str[i]};
        int bitCheck = 7;
        while(c[bitCheck] == true) {
            i++;
            bitCheck--;
        }
        i++;
        s++;
    }

    return s;
}

void increaseIndex(int& index, char currChar, int& charsToSkip) {
    //polskie znaki diakrytyczne są zapisane na 2 bajtach, gdzie 2 bajt nie mieści się w poniższym zakresie, więc index zwiększy się tylko raz a nie 2 razy
    index++;
    std::bitset<8> c{currChar};
    if(c[7] == 1) {

        int i = 7;
        while(c[i] == true) {
            charsToSkip++;
            i--;
        }
    }
}

int getNextState(std::string pat, int M, int state, int x) {
    if (state < M && x == pat[state])
        return state + 1;

    int ns, i;

    for (ns = state; ns > 0; ns--) {
        if (pat[ns - 1] == x) {
            for (i = 0; i < ns - 1; i++)
                if (pat[i] != pat[state - ns + 1 + i])
                    break;
            if (i == ns - 1)
                return ns;
        }
    }
 
    return 0;
}

void computeTF(std::string pat, int M, int TF[][NO_OF_CHARS]) {
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = getNextState(pat, M, state, x);
}

void FAMatcher(std::string pat, std::string txt) {
    int M = strlen(pat.c_str());
    int N = txt.size();
 
    int TF[32][NO_OF_CHARS];
 
    computeTF(pat, M, TF);
	
    int i, state = 0;
    for (i = 0; i < N; i++) {
        state = TF[state][txt[i]];
        if (state == M)
            std::cout << "Pattern found at index "<< i - M + 1 <<std::endl;
    }
}

std::vector<int> computePI(std::string& pattern) {
	int m = strlen(pattern.c_str());
	std::vector<int> pi(m, 0);
	int k = 0;

	for(int i = 1; i < m; i++) {
		while(k > 0 && pattern[k] != pattern[i]) {
			k = pi[k - 1];
		}
		if(pattern[k] == pattern[i]) {
			k += 1;
		}
		pi[i] = k;
	}

	return pi;
}

void KMPMatcher(std::string& pattern, std::string& text) {
	int m = pattern.size();
	int n = text.size();
    int rps = getPatternSize(pattern);

	std::vector<int> pi = computePI(pattern);
	int q = 0;

    int charsToSkip = 0;
    int ri = 0;
	for(int i = 0; i < n; i++) {
		while(q > 0 && pattern[q] != text[i]) {
			q = pi[q - 1];
		}

		if(pattern[q] == text[i]) {
			q += 1;
		}
        
		if(q == m) {
			std::cout << "Pattern found at index " << ri - rps + 1 << std::endl;
			q = pi[q - 1];
		}
        
        if(charsToSkip == 0)
            increaseIndex(ri, text[i], charsToSkip);
        else
            charsToSkip--;
	}
}

int main(int argc, char** argv) {
	std::string pattern = argv[2];
    std::string text = argv[3];

	if(strcmp(argv[1], "FA") == 0) {
		FAMatcher(pattern, text);
	}
	else if(strcmp(argv[1], "KMP") == 0) {
		KMPMatcher(pattern, text);
	}

	return 0;
}