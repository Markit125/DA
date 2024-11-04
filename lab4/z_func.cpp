#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> zString(std::string &text, std::string &pattern) {
    std::string str = pattern + "$" + text;
    std::vector<int> z_func(str.length());

    int l = -1, r = -1;
    z_func[0] = str.size();

    for (int i = 1; i < str.size(); i++) {
        if (i <= r) {
            z_func[i] = std::min(z_func[i - l], r - i);
        }

        while (l + z_func[i] < str.size() && str[z_func[i]] == str[i + z_func[i]]){
            ++z_func[i];
        }

        if (i + z_func[i] > r) {
            r = i + z_func[i];
            l = i;
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

    for (int i = pattern.length() + 1; i < zStr.size(); ++i) {
        if (zStr[i] == pattern.length()) {
            std::cout << i - pattern.length() - 1 << "\n";
        }
    }

    fclose(stdin);
    fclose(stdout);
}
