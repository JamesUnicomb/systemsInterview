#include <iostream>
#include <fstream>

#define ALPHABET_SIZE 26

using namespace std;

struct Node
{
    struct Node *children[ALPHABET_SIZE];
    char letter;
    bool isEndOfWord;
};

Node *newNode(void)
{
    Node *pNode = new Node;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

void insert(Node *root, string key)
{
    Node *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = newNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = true;
}

Node *search(Node *root, string key)
{
    Node *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return nullptr;

        pCrawl = pCrawl->children[index];
    }

    return pCrawl;
}

int numChildren(Node *root)
{
    Node *pCrawl = root;

    int count = 0;

    if (pCrawl->isEndOfWord)
    {
        count += 1;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (pCrawl->children[i])
        {
            count += numChildren(pCrawl->children[i]);
        }
    }

    return count;
}

void display(Node *root, const char prefix[], char str[], int level)
{
    if (root->isEndOfWord)
    {
        str[level] = '\0';
        cout << prefix << str << endl;
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            display(root->children[i], prefix, str, level + 1);
        }
    }
}

int main()
{
    Node *root = newNode();

    std::fstream file("words.txt");
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            insert(root, line);
        }
    }

    int level = 0;
    char str[26];

    int count = 0;
    string query;

    cout << "enter query string: ";

    cin >> query;
    cout << numChildren(search(root, query)) << endl;
    display(search(root, query), query.c_str(), str, level);
}