#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/converter.h"

#define ADRESS_AMOUNT 32 //max Anzahl der Adresse(zB. $1,$2..) man kann es abwechseln
#define LOOP_AMOUNT 32  //max Anzahl der Schleifen man kann es abwechseln
#define HELP_MENU "\n  Usage: ./uCompiler [OPTION] [FILE]\n"\
                  "  Help Menu: ./uCompiler --help\n"\
                  "  Documentation: ./uCompiler --doc\n"\
                  "  Compile File: ./uCompiler --file \"filename\"\n"\
                  "  Convert machine code: ./uCompiler --machinefile \"filename\"\n\n"
#define DOCUMENT "cat doc/documentation.txt"

void compileFile(char*);
int runOperation(char*, FILE*);
void showError(char*);
char* checkFile(char*);
int getVariableByAdr(int);

//struct um Adresse mit Variable identifizieren
typedef struct {
    int adress;
    int value;
} variable; 

//struct um Schleifeanfangen mit Byte der Cursor im File identifizieren
typedef struct {
    char name[50];
    int byte;
} loopStart; 

variable vars[ADRESS_AMOUNT]; //Arraylist für Variable
loopStart loops[LOOP_AMOUNT]; //Arraylist für Schleifen

int varCount=0; //um index nächster Variabel zu definieren
int loopCount=0; //um index nächster Schleife zu definieren
int lineCount=1; //um Line, die Fehler begreift, zu Benutzer zeigen  

int main(int argc, char* argv[]) {
    //nur Argumentation
    if(argc>1) {
        for(int i = 1; i < argc; i++) {
            if(stringcmp(argv[i], "--help")) {
                printf("%s", HELP_MENU);
            } else if(stringcmp(argv[i], "--file")) {
                if(argc >= 3) {
                    compileFile(checkFile(argv[i+1]));
                } else {
                    printf("geben sie bitte Dateiname nach --file Argument\n");
                }
            } else if(stringcmp(argv[i], "--machinefile")) {
                if(argc >= 3) {
                    convertToBinary(checkFile(argv[i+1]));
                } else {
                    printf("geben sie bitte Dateiname nach --machinefile Argument\n");
                }
            } else if(stringcmp(argv[i], "--doc")) {
                printf("\n");
                system(DOCUMENT);
                printf("\n");
            } else {
                printf("\nVerwenden Sie das Argument \"--help\", um das Anwendungsdokument anzuzeigen\n\n");
            }
        }        
    } else {
        printf("\nVerwenden Sie das Argument \"--help\", um das Anwendungsdokument anzuzeigen\n\n");
    }
    return 0;
}

//um Error mit Line zu zeigen
void showError(char* errorType) {
    printf("\nERROR: %s\n ->Line: %d\n\n", errorType, lineCount);
    exit(0);
}

//um value der Variabel mit adress zu erreichen
int getVariableByAdr(int adress) {
    if(adress < 0 || adress > 31) {
        showError("Man kann die Adresse, die nur zwischen $0-$31 sind, erreichen dürfen.");
    } else {
        for(int i = 0; i < ADRESS_AMOUNT; i++) {
            if(vars[i].adress == adress) {
                return i;
            }
        }
    }
    return -1;
}

//nach gebenen Operation(ADD, SET...) liest notwendige Argumente und ausführt sie 
int runOperation(char* operation, FILE* currentFile) {        

    char character, arg1[50], arg2[50], arg3[50], str[1000];

    auto void nextLine();
    auto void getArgument(int);
    auto void removeComma(char*);
    auto char* removeSpaces(char*);

    if(stringcmp(operation, "#")) { //wenn Linie Kommentarlinie ist, macht nie   
        nextLine(); 
        return 0;
    } else if(operation[0] == '#') { //wenn Linie Kommentarlinie ist, macht nie   
        nextLine(); 
        return 0;
    } else if(stringcmp(operation, "ADD")) {
        getArgument(3); //liest 3 Argumente
        int elm1 = atoi(arg1+1); //umformt Argumente zu geeignete Form
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3+1);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value+vars[getVariableByAdr(elm3)].value; //nimmt Value mit Adress und macht gewünschte Operation
        nextLine(); //liest gegebene File bis '\n'
        return 0;
    } else if(stringcmp(operation,  "ADDI")) {
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value + elm3;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "SUB")) {
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3+1);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value - vars[getVariableByAdr(elm3)].value;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "SUBI")) {
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value - elm3;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "MUL")) {
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3+1);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value * vars[getVariableByAdr(elm3)].value;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "MULI")) {
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value * elm3;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "DIV")) {
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3+1);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value / vars[getVariableByAdr(elm3)].value;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "DIVI")) {
        getArgument(3);
        int elm1 = atoi(arg1+1);
        int elm2 = atoi(arg2+1);
        int elm3 = atoi(arg3);
        vars[getVariableByAdr(elm1)].value = vars[getVariableByAdr(elm2)].value / elm3;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "DECR")) {
        getArgument(1);
        int elm1 = atoi(arg1+1);
        vars[getVariableByAdr(elm1)].value--;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "INCR")) {
        getArgument(1);
        int elm1 = atoi(arg1+1);
        vars[getVariableByAdr(elm1)].value++;
        nextLine();
        return 0;
    } else if(stringcmp(operation, "SHOW")) {
        fgets(str, 1000, currentFile); //nimmt ganze Linie. Auf diese Weise kann man unendlich viele String oder Variabel zeigen
        char* token = strtok(str , ","); //trennt diese Linie mit ',' zur Argumente
        while (token != NULL){
            char* result;
            token = removeSpaces(token); //löscht leere Charaktere vor und nach dieser String 
            if(token[0] == '"' || token[0] == '\'') { //wenn erste char dieser String ist ' oder " löscht erste und letzte Charakter
                result = token + 1;
                if(result[strlen(result)-1] == '\'' || result[strlen(result)-1] == '"') {
                    result[strlen(result)-1] = '\0';
                } else{
                    result[strlen(result)-3] = '\0';
                }
                printf("%s", result);
            } else if(token[0] == '$') { //wenn erste Charakter dieser String is $
                char* res = token + 1; //löscht $ um Variabel zu erreichen
                int result = atoi(res);
                if(result != -1) {
                    printf("%d", vars[getVariableByAdr(result)].value);
                } else {
                    printf("Adress $%d ist leer", result);
                }
            } else {
                showError("falsce Eingabe");
            }
            token = strtok(NULL, ",");
        }
        printf("\n");
        return 0;
    } else if(stringcmp(operation, "INPUT")) {
        getArgument(1);
        if(arg1[0] == '$') {
            int adr = atoi(arg1 + 1);
            if(adr < 0 || adr > 31) {
                showError("Man kann die Adresse, die nur zwischen $0-$31 sind, erreichen dürfen.");
            } else {
                int ind = getVariableByAdr(adr);
                if(ind != -1) { //wenn variabel ist schon gibt dann wechselt
                    scanf("%d", &vars[ind].value); //nimmt Eingabe von Benutzer und speichert sie als Variabel
                } else {
                    scanf("%d", &vars[varCount].value); //nimmt Eingabe von Benutzer und speichert sie als Variabel
                    vars[varCount].adress = adr; //set aktuelle varCount als adress
                    varCount++;
                }
            }
        } else {
            showError("falsce Eingabe");
        }
        nextLine();
        return 0;                
    } else if(stringcmp(operation, "SET")) {
        getArgument(2); //liest 2 Argumen
        int value = atoi(arg2); //2.Argument ist Wert
        if(arg1[0] == '$') { //erste Argument ist virtuelle Adress
            int adr = atoi(arg1 + 1); //löscht $ sign
            if(adr < 0 || adr > ADRESS_AMOUNT - 1) {
                showError("Man kann die Adresse, die nur zwischen $0-$31 sind, erreichen dürfen.");
            } else {
                int ind = getVariableByAdr(adr);
                if(ind != -1) { //wenn Adress schon definiert ist, dann wechselt Wert
                    vars[ind].value = value;
                } else { //wenn Adress nicht definiert worden,dann wird neue Variabel erschaffen
                    vars[varCount].adress = adr;
                    vars[varCount].value = value;
                    varCount++;
                } 
            }
        } else {
            showError("falsche Eingabe");
        }
        nextLine();
        return 0;                
    } else if(stringcmp(operation, "JMP")) {
        getArgument(1); //liest Schleifename
        for(int i = 0; i < LOOP_AMOUNT; i++) { //sucht Schleifename in loops
            if(stringcmp(loops[i].name,arg1)) {
                fseek(currentFile, loops[i].byte, SEEK_SET); //wenn Schleife gibt, dann wird Cursor zur Schleifeanfang hinträgt
                nextLine();
                return 0;                
            }
        }   
        nextLine();
    } else if(stringcmp(operation, "JLT")) {
        getArgument(3); //liest 3 Argument
        int value;
        char* adrc = arg2+1; //2.Argument ist Adress einer Variabel
        int adr = atoi(adrc);
        if(arg3[0] == '$') { //Wenn erste Charakter dritter Argument $ ist, dann nimmt compiler sie als Adress 
            char* elm3 = arg3 + 1;
            int tempVal = atoi(elm3);
            value = vars[getVariableByAdr(tempVal)].value;
        } else { //sonst nimmt compiler 3.Argument als integer
            value = atoi(arg3);
        } if(vars[getVariableByAdr(adr)].value < value) { //wenn 2.Argument kleiner als Dritter, wird Cursor zurAnfang der Schleife hinträgt
            for(int i = 0; i < LOOP_AMOUNT; i++) {
                if(stringcmp(loops[i].name, arg1)) {
                    fseek(currentFile, loops[i].byte, SEEK_SET);
                    nextLine();
                    return 0;                
                }
            }
        }
        nextLine();
    } else if(stringcmp(operation, "JGT")) { //gleich wie JLT aber JGT kontroliert ob 2.Argument größer als Dritte
        getArgument(3);
        int value;
        char* adrc = arg2+1;
        int adr = atoi(adrc);
        if(arg3[0] == '$') {
            char* elm3 = arg3+1;
            int tempVal = atoi(elm3);
            value = vars[getVariableByAdr(tempVal)].value;
        } else {
            value = atoi(arg3);
        } if(vars[getVariableByAdr(adr)].value > value) {
            for(int i = 0; i < LOOP_AMOUNT; i++) {
                if(stringcmp(loops[i].name, arg1)) {
                    fseek(currentFile, loops[i].byte, SEEK_SET);
                    nextLine();
                    return 0;                
                }
            }
        }
        nextLine();
    } else if(stringcmp(operation, "SYS")) {
        fgets(str, 1000, currentFile); //liest ganze Linie
        char* command = removeSpaces(str) + 1; //löscht ' oder "
        command[strlen(command) - 3] = '\0'; //löscht ' oder "
        system(command); //ausführt Befehl
        nextLine();
    } else if(stringcmp(operation, "END")) {
        exit(0); //beendet Programm
    } else { //wenn operation nicht definiert, dann nimmt compiler dieser String als Schleife Anfang
        strcpy(loops[loopCount].name, operation); //definiert Schleifename
        loops[loopCount].byte = ftell(currentFile); //speichert Byte der Cursor
        loopCount++;
        nextLine();
    }

    //liest bis '\n' um neue Linie zu erreichen
    void nextLine() {
        while(character != EOF) {
            character = fgetc(currentFile);
            if(character == '\n') {
                lineCount++;
                break;
            }
        }
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
    return 0;
}

//liest erste Wort aller Zeile von Datei und ausführt dieser operation und dieser Prozess dauert bis Dateiende 
void compileFile(char* path) {
    char operation[50];
    FILE* fPointer = fopen(path, "r");
    if(fPointer == NULL) {
        printf("%s konnte nicht geöffnet werden\n", path);
    } else {
        while(!feof(fPointer)) {
            fscanf(fPointer, "%s", &operation[0]);
            runOperation(operation, fPointer); 
        }   
    }
    fclose(fPointer);
}

//kontrolliert Datei weil wenn Argumente wie $1,10 steht, dann könnte Datei nict kompliert 
char* checkFile(char* path) {
    char character;
    FILE* f = fopen(path, "r"); //liest Datei
    FILE* out = fopen("temp.file", "w"); //erstellt temp.file für Korrektur
    //liest Datei und kopiert es in temp.file mit Lücke nach Komma, wenn da kein Lücke gibt
    while(!feof(f)) {
        character = fgetc(f);
        if(character == EOF) {
            break;
        } else if(character == ',') {
            fputc(character, out);
            character = fgetc(f);
            if(character == ' ') {
                fputc(character, out);
            } else {
                fputc(' ', out);
                fputc(character, out);
            }
        } else {
            fputc(character, out);
        }
    }
    
    fclose(f);
    fclose(out);
    remove(path); //löscht originale Datei
    rename("temp.file", path); //umbenennt temp.file wie originale Datei
    return path;
}
