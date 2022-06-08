#ifndef CONVERTER_H
#define CONVERTER_H

int stringcmp(char*, char*);
FILE* convertToBinary(char*);
int convertLine(char* ,FILE* ,FILE* );
char* stringToBinary(char*);
int intToBinary(int);
char* binaryDigit(int);

#endif