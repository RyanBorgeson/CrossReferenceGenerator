#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>


typedef enum { NOT_IDENT, IDENT, END_IDENT, COMMENT, STRING, SINGLE_COMMENT } Type;
typedef enum { true, false } boolean; 

char* LoadFile(FILE * f);
boolean IsIdentifier(char ch);


int main() {
	
	FILE * f = fopen ("SampleFile.txt", "rb");
	char * source = LoadFile(f);
	
	int Size = strlen(source);
	int i;
	
	ProcessFile(source, Size);
}

boolean IsIdentifier(char ch) {
    return isalnum(ch) || ch == '_' ? false : true;
}

char * IsType(char ch) {
	static char BuildString[1000];
	static int StringCount = 0;
	static Type PreviousType = NOT_IDENT;
	size_t CurrentLength = strlen(BuildString);
	
	if (PreviousType == END_IDENT) {
		PreviousType = NOT_IDENT;
		CurrentLength = 0;
		BuildString[0] = '\0';
	}
	
	if (ch == '/') {
		printf("COMMENT");
	}
	
	if (PreviousType == NOT_IDENT && isdigit(ch)) {
		PreviousType = NOT_IDENT;
		return "";
	}
	if (IsIdentifier(ch) && (PreviousType == NOT_IDENT || PreviousType == IDENT)) {
		PreviousType = IDENT;
		BuildString[CurrentLength] = ch;
		BuildString[CurrentLength+1] = '\0';
	}
	if (PreviousType == IDENT && !IsIdentifier(ch)) {
		PreviousType = END_IDENT;
		return BuildString;
	}
	
	
	return "";
}

void ProcessFile(char * Source, int size) {
	int i;
	int LineCount = 1;
	char *String;
	
	for (i = 0; i < size; i++) {
		//IsType(Source[i]);
		
		String = IsType(Source[i]);
		if (String != "")
			printf("%s\n", String);
		
		
		
		
		
		
		if (Source[i] == '\r') LineCount++;
		

		
	}
		//printf("%i", LineCount);
}


char * LoadFile(FILE * f) {
	
	
	
	char * buffer;
	int length;
	
	if (f)
	{
	  fseek (f, 0, SEEK_END);
	  length = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  buffer = malloc (length);
	  if (buffer)
	  {
		fread (buffer, 1, length, f);
	  }
	  fclose (f);
	}

	return buffer;
}