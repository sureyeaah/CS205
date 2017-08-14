#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

// shift characters of the word recursively to decrease length by 1.
char shift(char* word, int len) {
	char ret;
	// base case.
	if(!len)
		return '\0';
	else {
		// current 0th character is replaced.
		ret = word[0];
		word[0] = shift(word + 1, len - 1);
	}
	return ret;
}

// removes given letter from word of given. returns false if not found
bool removeLetter(char* word, int len, char letter) {
	// if length is 0, nothing left
	if(!len) return false;
	// check if starting word matches and removes it. else tries in further substring.
	if(word[0] == letter) {
		shift(word, len);
		return true;
	} else removeLetter(word + 1, len - 1, letter);
}
// checks recursively whether the word is even or not
bool isEvenWord(char* word) {
	int len = strlen(word);
	if(!len) return true; // case of empty string
	// try to remove a corresponding letter as the first one
	if(!removeLetter(word+1, len-1, word[0])) {
		return false;
	}
	else {
		return isEvenWord(word + 1);
	}
}

int main(void) {
	// get word
	printf("Enter word: ");
	char* word = (char*) malloc(sizeof(char)*1000);
	scanf("%s", word);
	// output
	if(isEvenWord(word))
		printf("The word is even.\n");
	else
		printf("The word is not even.\n");
}