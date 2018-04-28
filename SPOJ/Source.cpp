#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int MAXPHONESIZE = 10;

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (10)

// Converts key current character into index
// use only '0' through '9'
#define CHAR_TO_INDEX(c) ((int)c - (int)'0')

// trie node
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = NULL;

	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

	if (pNode)
	{
		int i;

		pNode->isEndOfWord = false;

		for (i = 0; i < ALPHABET_SIZE; i++)
			pNode->children[i] = NULL;
	}

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
bool insert(struct TrieNode *root, const char *key)
{
	int level;
	int length = strlen(key);
	int index;
	bool ret = true;

	struct TrieNode *pCrawl = root;

	for (level = 0; level < length; level++)
	{
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
		if (pCrawl->isEndOfWord) ret = false;
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
	for (index = 0; index < ALPHABET_SIZE; index++) {
		if (pCrawl->children[index]) {
			ret = false;
			break;
		}
	}
	return ret;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
	int level;
	int length = strlen(key);
	int index;
	struct TrieNode *pCrawl = root;

	for (level = 0; level < length; level++)
	{
		index = CHAR_TO_INDEX(key[level]);

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isEndOfWord);
}

int main()
{

	int tc;
	int nums;
	char phonenum[MAXPHONESIZE + 1];
	int i, n;
	bool consistent;
	struct TrieNode *root;

	scanf("%d", &tc);
	for (i = 0; i < tc; i++) {
		scanf("%d", &nums);
		consistent = true;
		root = getNode();
		for (n = 0; n < nums; n++) {
			scanf("%s", phonenum);
			if ((consistent == true) && (insert(root, phonenum) == false)) consistent = false;
		}
		if (consistent) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
