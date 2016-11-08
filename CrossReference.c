#include <stdio.h>
#include "list.h"

#define EMPTY ""

typedef enum { NOT_IDENT, IDENT, END_IDENT, COMMENT, END_COMMENT, STRING, SINGLE_COMMENT, PREPROCESSOR } Type;
typedef enum { true, false } boolean; 

char* LoadFile(FILE * f);
boolean IsIdentifier(char ch);

LList LinkedList;

int main(int argc, char* argv[]) {
		
	if (argc != 3) {
        printf("Usage: ./CrossReference <SourceFile> <OutputFile>");
        exit(1);
    }
	
	FILE * f = fopen (argv[1], "rb");
	char * source = LoadFile(f);
	
	
	InitList(&LinkedList);
	ProcessFile(source, strlen(source), argv[2]);
}

boolean IsIdentifier(char ch) {
    return isalnum(ch) || ch == '_' ? false : true;
}

char * DetermineIdentifiers(char ch) {
	static char BuildString[1000];
	static Type PreviousType = NOT_IDENT;
	static boolean IsPreprocessor = false;
	size_t CurrentLength = strlen(BuildString);
	
	if (PreviousType == END_IDENT) {
		PreviousType = NOT_IDENT;
		CurrentLength = 0;
		BuildString[0] = '\0';
	}

	if (ch == '#')
		IsPreprocessor = true;
	else if (ch == '\r')
		IsPreprocessor = false;
	
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
	if (IsIdentifier(ch) && (PreviousType == NOT_IDENT || PreviousType == IDENT || PreviousType == PREPROCESSOR)) {
		PreviousType = IDENT;
		BuildString[CurrentLength] = ch;
		BuildString[CurrentLength+1] = '\0';
	}
	if (PreviousType == IDENT && !IsIdentifier(ch)) {
		PreviousType = END_IDENT;
		return BuildString;
	}
	
	return EMPTY;
}

void ProcessFile(char * Source, int size, char * OutputFile) {
	int i;
	int LineCount = 1;
	char *Identifier;
	
	for (i = 0; i < size; i++) {
		
		Identifier = DetermineIdentifiers(Source[i]);
		if (Identifier != EMPTY) {
			AddNode(&LinkedList, Identifier, LineCount);
		}
		
		if (Source[i] == '\r') LineCount++;
	}
	
	ListNodes(&LinkedList, OutputFile);
}

char * LoadFile(FILE * File) {
	char * buffer;
	int length;
	
	if (File)
	{
		fseek(File, 0, SEEK_END);
		length = ftell (File);
		fseek(File, 0, SEEK_SET);
		buffer = malloc(length);
	
		if (buffer) {
			fread(buffer, 1, length, File);
		}
	fclose (File);
	}

	return buffer;
}