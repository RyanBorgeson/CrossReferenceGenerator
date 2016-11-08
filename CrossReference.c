/**
 * Project 2 - Cross Reference Generator
 * This program extracts each identifier from a c source file along
 * with its line number then stores the line numbers in a queue which is
 * then placed into a node with its corresponding identifier. Each identifier
 * is then printed to the specified output file in alphabetical order.
 * @Author Ryan Borgeson
 * @Date 11/8/2016
 **/
#include <stdio.h>
#include "list.h"

#define EMPTY ""

typedef enum { NOT_IDENT, IDENT, END_IDENT, COMMENT, END_COMMENT, STRING, SINGLE_COMMENT, PREPROCESSOR } Type;
typedef enum { true, false } boolean; 

/* Function prototypes. */
int main(int argc, char * argv[]);
boolean IsIdentifier(char ch);
char * DetermineIdentifiers(char ch);
void ProcessFile(char * Source, int size, char * OutputFile);
char * LoadFile(FILE * File);

/* Global linked list. */
LList LinkedList;

int main(int argc, char * argv[]) {
	
	// Check for appropriate usage.
	if (argc != 3) {
        printf("Usage: ./CrossReference <SourceFile> <OutputFile>");
        exit(1);
    }
	
	// Open the file and get the contents.
	FILE * SourceFile = fopen(argv[1], "rb");
	char * Contents = LoadFile(SourceFile);
	
	// Initialize the linked list.
	InitList(&LinkedList);
	
	// Process file and file contents.
	ProcessFile(Contents, strlen(Contents), argv[2]);
}

/**
 * Determine if the character is the start or contents elements
 * that an identifier would contain.
 * @param ch A character.
 * @return Returns a boolean of true if there is a valid identifier.
 **/
boolean IsIdentifier(char ch) {
    return isalnum(ch) || ch == '_' ? false : true;
}

/**
 * Determine Identifiers one character at a time. This will output
 * a character if it suspects the character belongs to a valid identifier.
 * @param ch A character.
 * @return Returns the character if it is a part an identifier.
 **/
char * DetermineIdentifiers(char ch) {
	// Static variables that hold identifiers.
	static char BuildString[1000];
	static Type PreviousType = NOT_IDENT;
	static boolean IsPreprocessor = false;
	size_t CurrentLength = strlen(BuildString);
	
	// Check to see if the previous character was an identifier.
	if (PreviousType == END_IDENT) {
		PreviousType = NOT_IDENT;
		CurrentLength = 0;
		BuildString[0] = '\0';
	}

	// Check for preprocessors.
	if (ch == '#')
		IsPreprocessor = true;
	else if (ch == '\r')
		IsPreprocessor = false;
	
	// Check for special escape characters or comments.
	// Both single and multiline comments will be ignored.
	if (ch == '/') 
		PreviousType = SINGLE_COMMENT;
	else if (ch == '"' && PreviousType != STRING && IsPreprocessor == false) 
		PreviousType = STRING;
	else if (ch == '"' && PreviousType == STRING && IsPreprocessor == false) 
		PreviousType = NOT_IDENT;
	else if (ch == '*' && PreviousType == SINGLE_COMMENT) 
		PreviousType = COMMENT;
	else if (ch == '*' && PreviousType == COMMENT) 
		PreviousType = END_COMMENT;
	else if (ch == '/' && PreviousType == END_COMMENT) 
		PreviousType = NOT_IDENT;
	else if (ch == '\r' && PreviousType == SINGLE_COMMENT)
		PreviousType = NOT_IDENT;
	
	
	if (PreviousType == STRING) 
		return EMPTY;
	
	if (PreviousType == NOT_IDENT && isdigit(ch)) {
		PreviousType = NOT_IDENT;
		return EMPTY;
	}
	// Build the string if all character tests are valid.
	if (IsIdentifier(ch) && (PreviousType == NOT_IDENT || 
			PreviousType == IDENT || 
			PreviousType == PREPROCESSOR)) {
		PreviousType = IDENT;
		BuildString[CurrentLength] = ch;
		BuildString[CurrentLength+1] = '\0';
	}
	
	// Return if the identifier is complete.
	if (PreviousType == IDENT && !IsIdentifier(ch)) {
		PreviousType = END_IDENT;
		return BuildString;
	}
	
	return EMPTY;
}

/**
 * Process file cotents by determining each identifier and adding
 * it to a linked list. Output the results to a text file.
 * @param Source The file contents.
 * @param Size The size of the contents.
 * @param OutputFile The name of the output file.
 **/
void ProcessFile(char * Source, int size, char * OutputFile) {
	int LineCount = 1, i;
	char *Identifier;
	
	// Loop through each line in the file.
	for (i = 0; i < size; i++) {
		
		// Determine and save identifiers
		Identifier = DetermineIdentifiers(Source[i]);
		if (Identifier != EMPTY)
			AddNode(&LinkedList, Identifier, LineCount);
		
		// Increment line count if the end of a line is reached.
		if (Source[i] == '\r') LineCount++;
	}
	
	// Prints the linked list to the output file.
	ListNodes(&LinkedList, OutputFile);
}

/**
 * Load the contents of the file into an array.
 * @param File The file to read from.
 * @return Returns a pointer to an array of the file contents.
 **/
char * LoadFile(FILE * File) {
	char * Buffer;
	int Length;
	
	// If the file exists read the contents.
	if (File)
	{
		fseek(File, 0, SEEK_END);
		Length = ftell (File);
		fseek(File, 0, SEEK_SET);
		Buffer = malloc(Length);
	
		if (Buffer)
			fread(Buffer, 1, Length, File);
		fclose (File);
	}

	// Return the buffer once read is complete.
	return Buffer;
}