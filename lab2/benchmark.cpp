#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map>

#include "treap.cpp"

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

std::pair<std::vector<std::pair<std::string, size_t> *>, std::vector<std::pair<std::string, size_t> *> > generate_test(int count_elems) {
    srand(time(0));

    std::vector<std::pair<std::string, size_t> *> elements_insert(count_elems);
    std::vector<std::pair<std::string, size_t> *> elements_remove(count_elems);

    for (int i = 0; i < count_elems; ++i) {
        std::string key = random_string(25);
        size_t value = random_uint(1 << 30);

        elements_insert[i] = new std::pair<std::string, size_t>(key, value);
        elements_remove[i] = new std::pair<std::string, size_t>(key, value);
    }

    std::random_shuffle(elements_insert.begin(), elements_insert.end());
    std::random_shuffle(elements_remove.begin(), elements_remove.end());

    return std::pair<std::vector<std::pair<std::string, size_t> *>, std::vector<std::pair<std::string, size_t> *> > (
        elements_insert,
        elements_remove
    );
}

void run_test_treap(std::vector<std::pair<std::string, size_t> *> vec_insert,
              std::vector<std::pair<std::string, size_t> *> vec_remove) {
    TTreap treap;
    
    for (int i = 0; i < vec_insert.size(); ++i) {
        treap.Insert(vec_insert[i]->first, vec_insert[i]->second);
    }
    for (int i = 0; i < vec_insert.size(); ++i) {
        treap.Erase(vec_remove[i]->first);
    }
}

void run_test_rb(std::vector<std::pair<std::string, size_t> *> vec_insert,
              std::vector<std::pair<std::string, size_t> *> vec_remove) {
    std::map<std::string, size_t> rb;
    
    for (int i = 0; i < vec_insert.size(); ++i) {
        rb[vec_insert[i]->first] = vec_insert[i]->second;
    }
    for (int i = 0; i < vec_insert.size(); ++i) {
        rb.erase(vec_remove[i]->first);
    }
}

// int main() {

//     for (int i = 10; i < 1e8; i *= 10) {

//         auto vecs = generate_test(i);
//         auto vecs_rb = vecs;

//         auto begin = std::chrono::high_resolution_clock::now();
//         run_test_treap(std::move(vecs.first), vecs.second);
//         auto end = std::chrono::high_resolution_clock::now();
//         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

//         std::cout << "treap    \tn: " << i << "\t" << "time: " << time << "ms\n";

//         begin = std::chrono::high_resolution_clock::now();
//         run_test_rb(std::move(vecs_rb.first), vecs_rb.second);
//         end = std::chrono::high_resolution_clock::now();
//         time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

//         std::cout << "std::map\tn: " << i << "\t" << "time: " << time << "ms\n";

//     }

//     return 0;
// }
