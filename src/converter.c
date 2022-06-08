#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stringcmp(char*, char*);
void convertToBinary(char*);
int convertLine(char*, FILE*, FILE* );
char* stringToBinary(char*);
int intToBinary(int);
char* binaryDigit(int);

char line[1000], op[50], outname[50], last[50];;

void convertToBinary(char* path) {
    FILE* f=fopen(path, "r"); //öffnet gegebene Datei
    strcpy(outname, path); //kopiert Dateiname zu outname
    strcat(outname, ".mac"); //zuordnet Ausdateiname und nennt es als dateiname.mac 
    FILE* out = fopen(outname, "w");  //darstellt neue Datei mit outname
    if(f == NULL) { //kontrolliert ob diese Dateien öffnet können
        printf("%s kann nicht geschaffen worden", path);
    }
    if(out == NULL) {
        printf("%s kann nicht geschaffen worden", outname);
    }
    while (!feof(f)) { //liest erste Wort der Datei
        fscanf(f, "%s", &op[0]);
        convertLine(op, f, out); //ausführt convertLine Funktion für jede einzige Operation
    }
    fclose(f);
    fclose(out);
}

int convertLine(char* operation, FILE* currentFile, FILE* out) {        

    char arg1[50],arg2[50], arg3[50], str[1000];

    auto void getArgument(int);
    auto void removeComma(char*);
    auto char* removeSpaces(char*);
    auto void firstLineCheck(FILE*);

    if(stringcmp(operation, "#") || operation[0] == '#') {
        fgets(line, 1000, currentFile); //liest ganze Linie wenn operation # ist
        line[strlen(line) - 1] = '\0'; //löscht '\n' um leere neue Linie zu vermeiden
        strcat(operation, line); //hinzufügt operation vor Linie
        fputs(operation, out); //schreibt Kommentarzeile zu Ausdatei
        return 0;
    } else if(stringcmp(operation, "ADD")) {
        firstLineCheck(out); //kontroliert ob aktuelle Linie ist erste Linie der File, wenn sie nicht schreibt '\n'
        fputs("000010001 ", out); //schreibt opcode der ADD operation zu Ausdatei
        getArgument(3); //nimmt 3 Argument wie Compileprozess und umformt sie in gewünschte Form
        int elm1=atoi(arg1+1);
        int elm2=atoi(arg2+1);
        int elm3=atoi(arg3+1);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1))); //konvertiert jede Argument Binärform danach transformiert sie 8-Digitform
        fputc(' ', out); //schreibt Lücke nach jeder Argument
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "ADDI")) {
        firstLineCheck(out);
        fputs("000010010 ", out);
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "SUB")) {
        firstLineCheck(out);
        fputs("000010011 ", out);
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3+1);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ',out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ',out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "SUBI")) {
        firstLineCheck(out);
        fputs("000010100 ", out);
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "MUL")) {
        firstLineCheck(out);
        fputs("000010101 ", out);
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3+1);
        fprintf(out," %s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "MULI")) {
        firstLineCheck(out);
        fputs("000010110 ", out);
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation,"DIV")) {
        firstLineCheck(out);
        fputs("000010111 ", out);
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3+1);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation,  "DIVI")) {
        firstLineCheck(out);
        fputs("000011000 ", out);
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "DECR")) {
        firstLineCheck(out);
        fputs("000011001 ", out);
        getArgument(1);
        int elm1 = atoi(arg1+1);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "INCR")) {
        firstLineCheck(out);
        fputs("000011010 ", out);
        getArgument(1);
        int elm1 = atoi(arg1+1);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "SHOW")) {
        firstLineCheck(out);
        fputs("000100001 ", out);
        fgets(str, 1000, currentFile); //liest ganze Linie und speichert diese Linie in str 
        char* token = strtok(str , ","); //trennt Argumente mit Komma
        while (token != NULL) {
            token=removeSpaces(token);
            if(token[0] == '"' || token[0] == '\'') { //wenn erste Charakter ' oder " ist, konvertiert direkt Binärform
                fputs(stringToBinary(token), out);
                fputc(' ', out);
            } else if(token[0] == '$') { //wenn erste Charakter $ ist, löscht $ und konvertiert Adress
                char* res = token + 1;
                int result = atoi(res);
                fprintf(out, "%s", binaryDigit(intToBinary(result)));
                fputc(' ' ,out);
            }
            token = strtok(NULL, ",");
        }
        fputc(' ', out);
        return 0;
    } else if(stringcmp(operation, "INPUT")) {
        firstLineCheck(out);
        fputs("000100010 ", out);
        getArgument(1);
        int elm1 = atoi(arg1+1);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        return 0;                
    } else if(stringcmp(operation, "SET")) {
        firstLineCheck(out);
        fputs("000100011 ", out);
        getArgument(2);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2);
        fprintf(out, "%s", binaryDigit(intToBinary(elm1)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        return 0;                
    } else if(stringcmp(operation, "JMP")) {
        firstLineCheck(out);
        fputs("000110001 ", out);
        getArgument(1);
        fprintf(out, "%s", stringToBinary(arg1));
        fputc(' ', out);
    
    } else if(stringcmp(operation, "JLT")) {
        firstLineCheck(out);
        fputs("000110010 ", out);
        getArgument(3);
        int elm2 = atoi(arg2+1);
        int elm3;
        if(arg3[0] == '$') {
            elm3 = atoi(arg3+1);
        } else {
            elm3 = atoi(arg3);
        }
        fprintf(out, "%s", stringToBinary(arg1));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
        
    } else if(stringcmp(operation, "JGT")) {
        firstLineCheck(out);
        fputs("000110011 ", out);
        getArgument(3);
        int elm2 = atoi(arg2+1);
        int elm3;
        if(arg3[0] == '$') {
            elm3 = atoi(arg3+1);
        } else {
            elm3 = atoi(arg3);
        }
        fprintf(out, "%s", stringToBinary(arg1));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm2)));
        fputc(' ', out);
        fprintf(out, "%s", binaryDigit(intToBinary(elm3)));
        fputc(' ', out);
       
    } else if(stringcmp(operation, "SYS")) {
        firstLineCheck(out); 
        fputs("001000001 ", out);
        fgets(str, 1000, currentFile);
        char* command = removeSpaces(str) + 1;
        command[strlen(command)-3] = '\0';
        fprintf(out, "%s", stringToBinary(command));
        fputc(' ', out);
        
    } else if(stringcmp(operation,"END")) {
        firstLineCheck(out);
        fputs("011111111 ", out);
        exit(0);
    } else { //Wenn Operation nicht definiert, d.h es Schleifeanfang ist
        firstLineCheck(out);
        fprintf(out, "%s", stringToBinary(operation));
        fputc(' ', out);
    }

    //nimmt Argumente(1,2 oder 3)
    void getArgument(int amountOfArgs) {
        switch (amountOfArgs) {
            case 1:
                fscanf(currentFile, "%s", arg1);
                break;
            case 2:
                fscanf(currentFile, "%s", arg1);
                removeComma(arg1);
                fscanf(currentFile, "%s", arg2);
                break;
            case 3:
                fscanf(currentFile, "%s", arg1);
                removeComma(arg1);
                fscanf(currentFile, "%s", arg2);
                removeComma(arg2);
                fscanf(currentFile, "%s", arg3);
                break;
        }
    }

    //löscht Komma, die nach gegebene Argument steht
    void removeComma(char* a) {
        for(int i = 0; i < sizeof(a); i++) {
            if(a[i] == ','){
                a[i] = '\0';    
            }
        }
        
    }
    
    //löscht Lücke vor und nach der String
    char* removeSpaces(char* a) {
        char* tempc;
        for(int i = 0; i < strlen(a); i++) {
            if(a[i] != ' ') {
                break; 
            } else {
                tempc = a + 1;
            }
        }
        for(int i = strlen(a); i >= 0; i++) {
            if(a[i] != ' ') {
                break;
            } else {
                a[i] = '\0';
            }
            tempc = a;
        }
        return tempc;
    }

    void firstLineCheck(FILE* fc) { //wenn Cursor Beginn der Datei steht, schreibt nicht neu Linie Charakter('\n')
        if(ftell(fc) != 0) {
            fputc('\n' ,fc);
        }
    }
    return 0;
}

int stringcmp(char* a, char* b) { //vergleicht zwei String und return 1, wenn sie gelich sind
    int i = 0;
    while(1) {
        if(a[i] != b[i] || (a[i] == 0 && b[i] != 0) || (a[i] != 0 && b[i] == 0)) {
            return 0;
        } else if(a[i] == 0 && b[i] == 0){
            return 1;
        }
        i++;
    }
}

//konvertiert String zu Binärform
char* stringToBinary(char* s) {
    if(s == NULL) {
        return 0; 
    }
    size_t len = strlen(s); //speichert länge der String
    char *binary = malloc(len*8 + 1); //reserviert Speicher für Binärform der String (plus eins ist für \0)
    binary[0] = '\0'; //löscht inhalt der binary
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i]; //nimmt jede Charakter in String
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) { //kontroliert jede bit der Charakter mit Bitwise Operationen
                strcat(binary, "1");
            } else {
                strcat(binary, "0");
            }
        }
    }
    return binary;
}

//umformt Integer, din in Binärform ist, zu 8-Digit Binärform um geordnete Machinefile zu erreichen
char* binaryDigit(int num) {

    char nulls[50] = "0";
    char result[50];
    
    sprintf(result, "%d", num);

    if(strlen(result) < 8) {
        for(int i = 0; i< 7 - strlen(result); i++) {
            strcat(nulls, "0");
        }
    }

    strcat(nulls, result);
    strcpy(last, nulls);
    return last;
}

//konvertiert Integer zu Binärform mit recursive Funktion
int intToBinary(int num){
    if(num == 0){
        return 0;
    }if(num == 1){ 
        return 1;
    }
    return (num % 2) + 10 * intToBinary(num / 2);
}