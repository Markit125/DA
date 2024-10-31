#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> zString(std::string &text, std::string &pattern) {
    std::string str = pattern + "$" + text;
    std::vector<int> z_func;
    z_func.push_back(-1);
    
    int begin = -1;
    int end = -1;

    for (int i = pattern.length() + 1; i < text.length(); ++i) {
        if (begin != -1 && end < ) {
            
        } else {

        }
    }

    return z_func; 
}

int main() {
    std::ios::sync_with_stdio(false);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    std::string text;
    std::string pattern;

    std::cin >> text >> pattern;

    std::vector<int> zStr = zString(text, pattern);

    for (int i = 0; i < zStr.size(); ++i) {
        if (zStr[i] == pattern.length()) {
            std::cout << i << "\n";
        }
    }

    fclose(stdin);
    fclose(stdout);
}