#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#define ALPHABET_SIZE 128 //you can instead reduce the alphabet size and createyour own mapping of character to index in array
int CHAR_TO_INDEX(char c) {
//custom mapping if alphabet size reduced
    return (int)c;
}
// trie node
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
    // void* data; //instead of checking for the presence or absence of a string, if we wish to assign some value with the key as a pair, then this could be uncommented
    int childCount;
};
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void) {
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (pNode) {
        int i;
        pNode->isEndOfWord = false;
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
        pNode->childCount = 0;
    }
    return pNode;
}
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key) {
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++) {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = getNode();
            pCrawl->childCount++;
        }
        pCrawl = pCrawl->children[index];
    }
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}
// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key) {
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++) {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl->isEndOfWord);
}

bool delete(struct TrieNode *root, const char* key) {
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for(level = 0; level<length; level++) {
        index = CHAR_TO_INDEX(key[level]);
        if(!pCrawl->children[index]) {
            return false;
        } 
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = false;
    return true;
}

bool delete2(struct TrieNode *pCrawl, const char* key, int level) {
    if(level==strlen(key)) {
        if(pCrawl->childCount) {
            pCrawl->isEndOfWord = false;
            return false;
        }
        else {
            for(int i = 0; i<ALPHABET_SIZE; i++) 
                pCrawl->children[i] = NULL;
            free(pCrawl);
            return true;
        }
    }
    if(!delete2(pCrawl->children[CHAR_TO_INDEX(key[level])], key, level+1)) return false;
    else {
        pCrawl->childCount--;
        if(pCrawl->childCount) {
            pCrawl->isEndOfWord = false;
            return false;
        }
        else {
            for(int i = 0; i<ALPHABET_SIZE; i++) 
                pCrawl->children[i] = NULL;
            free(pCrawl);
            return true;
        }
    }
}

// Driver
int main() {
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    char output[][32] = {"Not present in trie", "Present in trie"};
    struct TrieNode *root = getNode();
    // Construct trie
    int i;
    for (i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
        insert(root, keys[i]);
    // Search for different keys
    printf("%s---%s\n", "the", output[search(root, "the")] );
    printf("%s---%s\n", "these", output[search(root, "these")] );
    printf("%s---%s\n", "their", output[search(root, "their")] );
    printf("%s---%s\n", "thaw", output[search(root, "thaw")] );

    delete2(root, "the", 0);
    printf("%s---%s\n", "the", output[search(root, "the")] );
    
    delete2(root, "their", 0);
    printf("%s---%s\n", "their", output[search(root, "their")] );
    return 0;
}

