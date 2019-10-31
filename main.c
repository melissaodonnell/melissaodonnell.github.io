/* Melissa Caviglia O'Donnell
 * CS-352 Fall 2018
 * Purpose: To read in a sequence of words, group them by "noVowel equivalence"
            and print out the results
*/

typedef struct w {
    char *fullWord;
    struct w *next;
} fullWordNode;

typedef struct n {
    char *noVowelPattern;
    fullWordNode *wList;
    fullWordNode *tail;
    int cnt;
    struct n *next;
} noVowelNode;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* freeList frees the memory pointed to by hd.  */
void freeList(noVowelNode *hd) {
    noVowelNode *tptr;
    fullWordNode *wptr, *twptr;
    while (hd != NULL) {
        free(hd->noVowelPattern);
        wptr = hd->wList;
        while (wptr != NULL) {
            free(wptr->fullWord);
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
void printList(noVowelNode *hd) {
    fullWordNode *wptr;
    while (hd != NULL) {
        for (wptr = hd->wList; wptr != NULL; wptr = wptr->next)
            printf("%s ", wptr->fullWord);
        printf("\n");
        hd = hd->next;
    }
}

/* isGoodWord returns 1 if str is a good word (only letters) and 0 otherwise */
int isGoodWord(char *str) {
    while (*str != '\0') {
        if (!isalpha(*str))
            return 0;
        ++str;
    }
    return 1;
}

/* addNoVowelGroup adds a new nvNode with pattern pattern to the tail of the
   nvlist pointed at by tail. It also creates a wordNode with word. It
   returns a pointer to the node if succesfful and NULL otherwise
*/
noVowelNode *addNoVowelGroup(char *pattern, char *word, noVowelNode *tail) {
    noVowelNode *newNoVowel;
    fullWordNode *newWordNode;

    newWordNode = malloc(sizeof(fullWordNode));
    if (newWordNode == NULL) {
        return NULL;
    }

    newWordNode->fullWord = strdup(word);
    if (newWordNode->fullWord == NULL) {
        free(newWordNode);
        return NULL;
    }
    newWordNode->next = NULL;

    newNoVowel = malloc(sizeof(noVowelNode));
    if (newNoVowel == NULL) {
        free(newWordNode->fullWord);
        free(newWordNode);
        return NULL;
    }

    newNoVowel->noVowelPattern = strdup(pattern);
    if (newNoVowel->noVowelPattern == NULL) {
        free(newWordNode->fullWord);
        free(newWordNode);
        free(newNoVowel);
        return NULL;
    }
    newNoVowel->wList = newNoVowel->tail = newWordNode;
    newNoVowel->cnt = 1;
    newNoVowel->next = NULL;
    tail->next = newNoVowel;

    return newNoVowel;
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
void outOfMemory(noVowelNode *list) {
    fprintf(stderr, "Out of memory\n");
    freeList(list);
    exit(1);
}

/* findNoVowelGroup looks for a node in the list pointed to by hd
   whose pattern matches pattern. If it
   finds one it returns a pointer to it, otherwise NULL
*/

noVowelNode *findNoVowelGroup(char *pattern, noVowelNode *hd) {
    while (hd != NULL) {
        if (strcmp(pattern, hd->noVowelPattern) == 0)
            return hd;
        hd = hd->next;
    }
    return NULL;
}

/* addWord adds the word str to the list of words of node nv. It returns
   a pointer to the new wordNode if successful and NULL otherwise */
fullWordNode *addWord(char *str, noVowelNode *nv){
    fullWordNode *newNode;
    newNode = malloc(sizeof(fullWordNode));
    if (newNode == NULL)
        return NULL;
    newNode->fullWord = strdup(str);
    if (newNode->fullWord == NULL) {
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
    noVowelNode hd, *tail;  //hd is a dummy header node
    noVowelNode *ptr;

    hd.next = NULL;
    tail = &hd;

    while (scanf("%64s", buff) > 0) {
        if (isGoodWord(buff)) {
            createPattern(pattern, buff);
            if (*pattern == '\0')
                continue;   // ignore if all vowels
            if ((ptr = findNoVowelGroup(pattern, hd.next))) {
                if (!addWord(buff, ptr))
                    outOfMemory(hd.next);
            } else {
                if ((tail = addNoVowelGroup(pattern, buff, tail)) == NULL) {
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