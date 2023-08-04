// Oma Persaud
// Lab 10 
// August 08, 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEofALPHABET 26

// Trie structure
struct Trie
{	
    struct Trie* children[SIZEofALPHABET];
    int count;
};

// Inserts the word to the trie structure
void insert(struct Trie **ppTrie, char *word)
{
    struct Trie * cur = *ppTrie;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if (cur -> children[index] == NULL)
        {
            cur -> children[index] = (struct Trie*)malloc(sizeof(struct Trie));

            for (int j = 0; j < SIZEofALPHABET; j++)
            {
                cur -> children[index] -> children[j] = NULL;
            }

            cur -> children[index] -> count = 0;
        }
        cur = cur -> children[index];
    }
    cur -> count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{

    struct Trie* cur = pTrie;

    for (int i = 0; word[i] != '\0'; i++) 
    {
        int index = word[i] - 'a';

        if (cur -> children[index] == NULL) 
        {
            return 0;
        }
        cur = cur -> children[index];
    }
    return cur -> count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL) 
    {
        return NULL;
    }

    for (int i = 0; i < SIZEofALPHABET; i++) 
    {
        if (pTrie->children[i] != NULL) 
        {
            deallocateTrie(pTrie->children[i]);
        }
    }

    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
  //  struct Trie * i = (struct Trie*)malloc(sizeof(struct Trie));
  //  int i;
  
   
  //  return i;

}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE* inFile = fopen("dictionary.txt","r");
	int InWords = 0;
	int i, n, *word;
	*pInWords = NULL;
	
	if (inFile)
	{
        

		fclose(inFile);
	}
	
	return InWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);

	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();

	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}

	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);

	if (pTrie != NULL)
		printf("There is an error in this program\n");

    return 0;
}