#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void read_vector(const char *filename, std::vector<std::pair<int, std::string> *> &vec, int &max_element) {
    
    std::fstream file;
    file.open(filename, std::ios::in);

    int key;
    std::string value;

    while (file >> key) {
        file >> value;
        vec.push_back(new std::pair<int, std::string>(key, value));
        max_element = max_element > key ? max_element : key;
    }

    file.close();
}

void write_vector(const char *filename, std::vector<std::pair<int, std::string> *> vec) {
    std::fstream file;
    file.open(filename, std::ios::out);

    for (int i = 0; i < vec.size(); ++i) {
        file << vec[i]->first << "\t" << vec[i]->second << "\n";
        delete vec[i];
    }

    file.close();
}

void sort_vector(std::vector<std::pair<int, std::string> *> &vec, std::vector<std::pair<int, std::string> *> &sorted_vec, int max_element) {
    std::vector<int> temp_vec(max_element + 1);

    for (int i = 0; i < vec.size(); ++i) {
        temp_vec[vec[i]->first]++;
    }

    for (int i = 1; i < temp_vec.size(); ++i) {
        temp_vec[i] += temp_vec[i - 1];
    }

    for (int i = vec.size() - 1; i >= 0; --i) {
        sorted_vec[--temp_vec[vec[i]->first]] = vec[i];
    }
}

void count_sort(const char *input, const char *output) {
    std::vector<std::pair<int, std::string> *> init_vec;
    int max_element;

    read_vector(input, init_vec, max_element);
    
    std::vector<std::pair<int, std::string> *> sorted_vec(init_vec.size());
    sort_vector(init_vec, sorted_vec, max_element);

    write_vector(output, sorted_vec);
}

int main() {
    count_sort("input.txt", "output.txt");
    
    return 0;
}