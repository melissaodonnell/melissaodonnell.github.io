/* Melissa Caviglia O'Donnell
 * CS-352 Fall 2018
 * Purpose: To read in a sequence of words, group them by "noVowel equivalence"
            and print out the results
*/

typedef struct w {
    char *word;
    struct w *next;
} wordNode;

typedef struct n {
    char *pattern;
    wordNode *wList;
    wordNode *tail;
    int cnt;
    struct n *next;
} nvNode;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* freeList frees the memory pointed to by hd.  */
void freeList(nvNode *hd) {
    nvNode *tptr;
    wordNode *wptr, *twptr;
    while (hd != NULL) {
        free(hd->pattern);
        wptr = hd->wList;
        while (wptr != NULL) {
            free(wptr->word);
            twptr = wptr->next;
            free(wptr);
            wptr = twptr;
        }
        tptr = hd->next;
        free(hd);
        hd = tptr;
    }
}

/* printList prints the list pointed to by hd */
void printList(nvNode *hd) {
    wordNode *wptr;
    while (hd != NULL) {
        for (wptr = hd->wList; wptr != NULL; wptr = wptr->next)
            printf("%s ", wptr->word);
        printf("\n");
        hd = hd->next;
    }
}

/* goodWord returns 1 if str is a good word (only letters) and 0 otherwise */
int goodWord(char *str) {
    while (*str != '\0') {
        if (!isalpha(*str))
            return 0;
        ++str;
    }
    return 1;
}

/* addNVgroup adds a new nvNode with pattern pattern to the tail of the
   nvlist pointed at by tail. It also creates a wordNode with word. It
   returns a pointer to the node if succesfful and NULL otherwise
*/
nvNode *addNVgroup(char *pattern, char *word, nvNode *tail) {
    nvNode *newNV;
    wordNode *newWordNode;

    newWordNode = malloc(sizeof(wordNode));
    if (newWordNode == NULL) {
        return NULL;
    }

    newWordNode->word = strdup(word);
    if (newWordNode->word == NULL) {
        free(newWordNode);
        return NULL;
    }
    newWordNode->next = NULL;

    newNV = malloc(sizeof(nvNode));
    if (newNV == NULL) {
        free(newWordNode->word);
        free(newWordNode);
        return NULL;
    }

    newNV->pattern = strdup(pattern);
    if (newNV->pattern == NULL) {
        free(newWordNode->word);
        free(newWordNode);
        free(newNV);
        return NULL;
    }
    newNV->wList = newNV->tail = newWordNode;
    newNV->cnt = 1;
    newNV->next = NULL;
    tail->next = newNV;

    return newNV;
}

/* createPattern takes a word and a pointer to memory at least as large as
   word. It copies into pattern a string that is word with its vowels
   stripped out and its remaining letters converted to lower case
*/
void createPattern(char *pattern, char *word) {
    char c;
    while (*word != '\0') {
        c = tolower(*word);
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
            *pattern++ = c;
        ++word;
    }
    *pattern = '\0';
}

/* outOfMemory handles the error of being out of memory */
void outOfMemory(nvNode *list) {
    fprintf(stderr, "Out of memory\n");
    freeList(list);
    exit(1);
}

/* findNVgroup looks for a node in the list pointed to by hd
   whose pattern matches pattern. If it
   finds one it returns a pointer to it, otherwise NULL
*/

nvNode *findNVgroup(char *pattern, nvNode *hd) {
    while (hd != NULL) {
        if (strcmp(pattern, hd->pattern) == 0)
            return hd;
        hd = hd->next;
    }
    return NULL;
}

/* addWord adds the word str to the list of words of node nv. It returns
   a pointer to the new wordNode if successful and NULL otherwise */
wordNode *addWord(char *str, nvNode *nv){
    wordNode *newNode;
    newNode = malloc(sizeof(wordNode));
    if (newNode == NULL)
        return NULL;
    newNode->word = strdup(str);
    if (newNode->word == NULL) {
        free(newNode);
        return NULL;
    }
    newNode->next = NULL;
    nv->tail->next = newNode;            //tail can't be NULL
    nv->tail = newNode;
    return newNode;
}

int main() {
    int errSeen = 0;
    char buff[65], pattern[65];
    nvNode hd, *tail;  //hd is a dummy header node
    nvNode *ptr;

    hd.next = NULL;
    tail = &hd;

    while (scanf("%64s", buff) > 0) {
        if (goodWord(buff)) {
            createPattern(pattern, buff);
            if (*pattern == '\0')
                continue;   // ignore if all vowels
            if ((ptr = findNVgroup(pattern, hd.next))) {
                if (!addWord(buff, ptr))
                    outOfMemory(hd.next);
            } else {
                if ((tail = addNVgroup(pattern, buff, tail)) == NULL) {
                    outOfMemory(hd.next);
                }
            }
        } else {
            fprintf(stderr, "Bad word: %s\n", buff);
            errSeen = 1;
        }
    }

    printList(hd.next);
    freeList(hd.next);
    return errSeen;
}