#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "count_sort.cpp"

const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

int random_uint(int max) {
    return rand() % (int)(max + 1);
}

std::string random_string(int length) {
    std::string random_string = "";

    for (int i = 0; i < length; i++) {
        int random_index = rand() % characters.length();
        random_string += characters[random_index];
    }

    return std::move(random_string);
}

void generate_test(const char *filename, int count_elems) {
    srand(time(0));
    std::fstream file;
    file.open(filename, std::ios::out);

    for (int i = 0; i < count_elems; ++i) {
        file << random_uint(count_elems) << " " << random_string(20) << "\n";
    }

    file.close();
}

int main() {
    const char *test_input = "test_input.txt";
    const char *test_output = "test_output.txt";

    for (int i = 10; i < 1e8; i *= 10) {

        generate_test(test_input, i);

        auto begin = std::chrono::high_resolution_clock::now();
        count_sort(test_input, test_output);
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        std::cout << "n: " << i << "\t" << "time: " << time << "ms\n";
    }

    return 0;
}
