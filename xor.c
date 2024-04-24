#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#define ALPHABET_SIZE 2//you can instead reduce the alphabet size and createyour own mapping of character to index in array
int CHAR_TO_INDEX(char c) {
//custom mapping if alphabet size reduced
    return (int)c;
}
// trie node
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
};
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void) {
    struct TrieNode *pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode* root, int num) {
    struct TrieNode* node = root;
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (node->children[bit] == NULL) {
            node->children[bit] = createNode();
        }
        node = node->children[bit];
    }
}
// Returns true if key presents in trie, else false
int search(struct TrieNode* root, int num) {
    struct TrieNode* node = root;
    int result = 0;
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (node->children[1 - bit] != NULL) {
            result |= (1 << i);
            node = node->children[1 - bit];
        } else {
            node = node->children[bit];
        }
    }
    return result;
}

// Function to find the maximum XOR subarray
int max_xor_subarray(int* nums, int numsSize) {
    // Compute prefix XOR array
    int* prefix_xor = (int*)malloc((numsSize + 1) * sizeof(int));
    prefix_xor[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefix_xor[i + 1] = prefix_xor[i] ^ nums[i];
    }
    
    // Build Trie and find maximum XOR value
    struct TrieNode* root = createNode();
    int max_xor = -1;
    for (int i = 0; i <= numsSize; i++) {
        insert(root, prefix_xor[i]);
        max_xor = (max_xor > search(root, prefix_xor[i])) ? max_xor : search(root, prefix_xor[i]);
    }
    
    // Clean up memory
    free(prefix_xor);
    
    return max_xor;
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

