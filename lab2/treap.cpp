#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <utility>
#include <chrono>

class TTreap {

private:

    struct TNode {
        TNode *left;
        TNode *right;
        std::string key;
        size_t value;
        size_t priority;

        TNode(const std::string &key, size_t value);
    };

    TNode *root;

    TNode *Merge(TNode *treap1, TNode *treap2);

    void Split(TNode *treap, const std::string &key, TNode *&treap1, TNode *&treap2);

    TNode *Find(const std::string &key);

    TNode *Find(TNode *ptr, const std::string &key);

    void Destroy(TNode *&node);

    void Destroy();

public:

    TTreap();

    ~TTreap();

    void Insert(const std::string &key, size_t value);

    void Erase(const std::string &key);

    std::pair<size_t, bool> Exist(const std::string &key);
};

std::mt19937 random_int(std::chrono::steady_clock::now().time_since_epoch().count());

TTreap::TNode::TNode(const std::string &key, size_t value) {
    left = nullptr;
    right = nullptr;
    this->key = key;
    this->value = value;
    this->priority = random_int();
}

TTreap::TNode *TTreap::Merge(TNode *treap1, TNode *treap2) {
    if (treap1 == nullptr) {
        return treap2;
    }
    if (treap2 == nullptr) {
        return treap1;
    }
    if (treap1->priority > treap2->priority) {
        treap1->right = Merge(treap1->right, treap2);
        return treap1;
    }
    treap2->left = Merge(treap1, treap2->left);
    return treap2;
}

void TTreap::Split(TNode *treap, const std::string &key, TNode *&treap1, TNode *&treap2) {
    if (treap == nullptr) {
        treap1 = nullptr;
        treap2 = nullptr;
        return;
    }
    if (key > treap->key) {
        Split(treap->right, key, treap->right, treap2);
        treap1 = treap;
    } else {
        Split(treap->left, key, treap1, treap->left);
        treap2 = treap;
    }
}

TTreap::TNode *TTreap::Find(const std::string &key) {
    return Find(root, key);
}

TTreap::TNode *TTreap::Find(TNode *ptr, const std::string &key) {
    if (ptr == nullptr) {
        return nullptr;
    }
    if (ptr->key == key) {
        return ptr;
    }
    if (ptr->key > key) {
        return Find(ptr->left, key); 
    }
    return Find(ptr->right, key);
}

void TTreap::Destroy() {
    Destroy(root);
}

void TTreap::Destroy(TNode *&node) {
    if (node != nullptr) {
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }
}

TTreap::TTreap() {
    root = nullptr;
}

TTreap::~TTreap() {
    Destroy();
}

void TTreap::Insert(const std::string &key, size_t value) {
    TNode *ltreap = nullptr;
    TNode *rtreap = nullptr;
    Split(root, key, ltreap, rtreap);
    TTreap::TNode *node = new TNode(key, value);
    root = Merge(Merge(ltreap, node), rtreap);
}

void TTreap::Erase(const std::string &key) {
    TNode *ltreap = nullptr;
    TNode *rtreap = nullptr;
    Split(root, key, ltreap, rtreap);
    TTreap::TNode *rtreapRoot = rtreap;
    if (rtreapRoot->key == key) {
        if (rtreapRoot->right == nullptr) {
            delete rtreapRoot;
            rtreapRoot = nullptr;
        } else {
            rtreapRoot = rtreapRoot->right;
        }
    } else {
        while (rtreap != nullptr) {
            if (rtreap->left != nullptr && rtreap->left->key == key) {
                if (rtreap->left->right == nullptr) {
                    delete rtreap;
                    rtreap->left = nullptr;
                } else {
                    rtreap->left = rtreap->left->right;
                }
            }
            rtreap = rtreap->left;
        }
    }
    root = Merge(ltreap, rtreapRoot);
}

std::pair<size_t, bool> TTreap::Exist(const std::string &key) {
    TTreap::TNode *node = Find(key);
    if (node == nullptr) {
        return std::pair<size_t, bool> (0, false);
    }
    return std::pair<size_t, bool> (node->value, true);
}

void lower(std::string &word) {
    for (int i = 0; i < word.length(); ++i) {
        if (word[i] <= 'Z' && word[i] >= 'A') {
            word[i] -= ('Z' - 'z');
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    TTreap treap;
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            std::string key;
            size_t value;
            std::cin >> key >> value;
            lower(key);
            if (treap.Exist(key).second) {
                std::cout << "Exist\n";
            } else {
                treap.Insert(key, value);
                std::cout << "OK\n";
            }
        }
        else if (command == "-") {
            std::string key;
            std::cin >> key;
            lower(key);
            if (!treap.Exist(key).second) {
                std::cout << "NoSuchWord\n";
            } else {
                treap.Erase(key);
                std::cout << "OK\n";
            }
        } else {
            lower(command);
            std::pair<size_t, bool> node = treap.Exist(command);
            if (node.second) {
                std::cout << "OK: " << node.first << "\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        }
    }

    fclose(stdin);
    fclose(stdout);
}