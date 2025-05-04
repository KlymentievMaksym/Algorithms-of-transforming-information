#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode()
    {
        isEndOfWord = false;
    }
};

class Trie
{
private:
    TrieNode* root;

public:
    Trie()
    {
        root = new TrieNode();
    }
    Trie(vector<string> patterns)
    {
        root = new TrieNode();
        for (string pattern : patterns)
            insert(pattern);
    }
    Trie(string pattern)
    {
        root = new TrieNode();
        insert(pattern);
    }


    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch))
                node->children[ch] = new TrieNode();
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    // Search a full word
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch))
                return false;
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    // Check if any word in the trie starts with the given prefix
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (!node->children.count(ch))
                return false;
            node = node->children[ch];
        }
        return true;
    }

    ~Trie() {
        clear(root);
    }

private:
    void clear(TrieNode* node) {
        for (auto& pair : node->children) {
            clear(pair.second);
        }
        delete node;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");

    cout << boolalpha;
    cout << "Search 'apple': " << trie.search("apple") << endl;     // true
    cout << "Search 'app': " << trie.search("app") << endl;         // true
    cout << "Prefix 'ap': " << trie.startsWith("ap") << endl;       // true
    cout << "Search 'appl': " << trie.search("appl") << endl;       // false
}
