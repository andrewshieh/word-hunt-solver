#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

const int N = 4;
const vector<pair<int, int>> DIRS = {
    make_pair(-1,-1), make_pair(-1, 0), make_pair(-1, 1),
    make_pair( 0,-1), make_pair( 0, 0), make_pair( 0, 1),
    make_pair( 1,-1), make_pair( 1, 0), make_pair( 1, 1)
};

struct TrieNode {
    bool is_word = false;
    struct TrieNode *children[26] = {0};
};

TrieNode *root = new TrieNode;
vector<string> answer;

void insert(string word) {
    TrieNode *curr = root;
    for (int i = 0; i < word.length(); i++) {
        int j = word[i] - 'A';
        if (!curr->children[j]) {
            curr->children[j] = new TrieNode;
        }
        curr = curr->children[j];
    }
    curr->is_word = true;
}

bool prefix(string word) {
    TrieNode *curr = root;
    for (int i = 0; i < word.length(); i++) {
        int j = word[i] - 'A';
        if (!curr->children[j]) {
            return false;
        }
        curr = curr->children[j];
    }
    return true;
}

bool check(string word) {
    TrieNode *curr = root;
    for (int i = 0; i < word.length(); i++) {
        int j = word[i] - 'A';
        if (!curr->children[j]) {
            return false;
        }
        curr = curr->children[j];
    }
    return (curr && curr->is_word);
}

void dfs(string board, string word, int i, int j) {
    if (i < 0 || j < 0 || i >= N || j >= N || board[i*N+j] == '*' || !prefix(word)) {
        return;
    }
    if (check(word)) {
        answer.push_back(word);
    }
    board[i*N+j] = '*';
    for (pair<int, int> p: DIRS) {
        int x = p.first;
        int y = p.second;
        dfs(board, word+board[(i+x)*N+j+y], i+x, j+y);
    }
}

void free_all(TrieNode* curr) {
    for (int i = 0; i < 27; i++) {
        if (curr->children[i] != 0) {
            free_all(curr->children[i]);
        }
    }
    delete curr;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Error: expected 1 argument, got " << argc-1 << "\n";
        return 1;
    }
    string board = argv[1];
    if (board.length() != 16) {
        cout << "Error: input must be a 16 letter string" << "\n";
        return 1;
    }

    for (char &c: board) {
        if (!isalpha(c)) {
            cout << "Error: input must only contain letters" << "\n";
            return 1;
        }
        c = toupper(c);
    }

    ifstream dict("dictionary.txt");
    string word;
    while (dict >> word) {
        insert(word);
    }
    dict.close();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dfs(board, string(1,board[i*N+j]), i, j);
        }
    }

    sort(answer.begin(), answer.end(),
     [](string &one, string &two) { return one.length() == two.length() ? one < two : one.length() > two.length(); });
    answer.erase(unique(answer.begin(), answer.end()), answer.end());
    for (string s: answer) {
        if (s.length() >= 3) {
            cout << s << "\n";
        }
    }

    free_all(root);
    return 0;
}