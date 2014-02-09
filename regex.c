/*
Author: 	Patrick Hennessy
Date:		11-19-2013
E-mail:	PH7VC@mail.missouri.edu
*/

//Includes
#include <stdio.h>	// Using: printf
#include <regex.h>	// Using: regcomp, regexec, regfree, regex_t, regmatch_t
#include <stdlib.h>	// Using: malloc
#include <string.h>	// Using: strcpy

//Definitions 
typedef enum{false, true} bool;
 
//Prototypes
bool regex_matches(char* pattern, char* str);
char* regex_getMatch(char* pattern, char* str);

//Main program 
int main(int argv, char **argc)
{              
	//	 
	char* pattern = "[0-9]{3}-[0-9]{3}-[0-9]{4}";
	char* str = "aAlkj$#zs#s1356314-413-2513asf#1as%dfaSs*dfasf";
	 
	printf("%s\n", regex_getMatch(pattern,str));
	   
	return 0;
}

/*
	Desc: Returns weather the string has a match of a regex pattern
	Args: 
		char* pattern: expression passed as a string
		char* str:		string to check for a match
	Returns:	bool_t, or int {0,1}
*/
bool regex_matches(char* pattern, char* str) 
{ 
	regex_t regex; // Regex object
		
	/*Regcomp compiles the given regex object with the pattern. 
		Uses POSIX extended regex. This is more advanced regex like range of tokens
		Nosub tells it to only return error codes
	*/
	int errors = regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB);	
	
	/* Regexec will execute a regular expression on a given string
			If it doesnt find a match, it returns an error code
	*/
	errors = regexec(&regex, str, 0, NULL, 0);

	//When regcomp is called, it mallocs memory for the expression and must be freed
	regfree(&regex); 

	//If the error code is 0, we return true meaning there is a match
	if(!errors) 
		return true; 
	
	else 
		return false; 
}
/*
	Desc: Returns the substring of the first match of a regex pattern
	Args: 
		char* pattern: expression passed as a string
		char* str:		string to check for a match
	Returns:	char* substr. Contains the first match of the regex pattern
*/ 
char* regex_getMatch(char* pattern, char* str) 
{ 
	regex_t regex; 		// Regex object
	regmatch_t match[1]; // Struct that will store info about the match
	 
	/* Regcomp compiles the given regex object with the pattern. 
			Uses POSIX extended regex. This is more advanced regex like range of tokens
	*/
	regcomp(&regex, pattern, REG_EXTENDED); 
	
	/* Regexec will execute a regular expression on a given string
			If it doesnt find a match, it returns an error code
			Stores the matched substring into the match struct
	*/
	int nomatch = regexec(&regex, str, 1, match, 0);

	// When regcomp is called, it mallocs memory for the expression and must be freed
	regfree(&regex); 
	
	// If the execution function returns false, we return a NULL string
	if(nomatch) { 
		return NULL; 
	} 
	
	// If a match was found, we need to find the substring
	int start = match[0].rm_so; 	//rm_so stands for Regex Match Start Of
	int end = match[0].rm_eo; 		//rm_eo stands for Regex Match End Of
	int size = (end - start); 		//This gives us the size of the substring

	char* substr = malloc(sizeof(char) * size);	//Allocate memory for a new substring 
	strncpy(substr, str+match[0].rm_so, size); 	//Copy the match into the substring. str+match[0].rm_so offsets the strcpy
	substr[size] = '\0'; 								//Manually add a null terminator because regex will not do it and neither will strcpy
	
	return substr; 
}




