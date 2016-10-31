#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>


typedef enum { NOT_IDENT, IDENT, COMMENT, STRING, SINGLE_COMMENT } Type;
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
    return isalnum(ch) || ch == '_' ? true : false;
}

void ProcessFile(char * Source, int size) {
	int i;
	int LineCount = 1;
	
	for (i = 0; i < size; i++) {
		
		printf("%c\n", Source[i]);
		
		
		
		
		
		
		if (Source[i] == '\r') LineCount++;
		

		
	}
		printf("%i", LineCount);
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