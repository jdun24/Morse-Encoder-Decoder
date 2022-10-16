/*
Author: Joseph Dunagan
Date: 05/24/2022
Description:    A command line program that can take an input file of english or morse and 
                translate\decode that file into an output file
Usage: C was used

//Command lines
//      gcc -g -Wall dunagan_joseph_assn1.c -o exe
//      ./exe english.txt -e morse.txt  //OR
//      ./exe morse.txt -mc english.txt
*/

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
void englishToMorse(char,FILE*);
void encrypt(char*, FILE*, FILE*);//first file is being read, second is being written into
void morseToEnglish(char* , FILE*);
void decode(char*, FILE*, FILE*);

int main(int argc, char* argv[]){
    if(argc != 4){   //Correct amount of args needs to be entered
        printf("Error -- usage: <exe> <input file> <-mc|-e> <output file>\n");
        return 0;   //can't execute rest of code without proper command usage
    }
    
    FILE *input = fopen(argv[1], "r");	//argv[1] is second arg in ./exe input.txt out.txt
    FILE *out = fopen(argv[3],"w");	//argv[2] is 3rd arg in ./exe input.txt out.txt
    
    char line[MAX_LINE_LENGTH]; 
    if(input == NULL){       //checks to make sure file has contents, prints out whats happening
        printf("The file was empty");
        return -1;
    }else{
        if(strcmp(argv[2],"-e") == 0){
	            printf("Translating %s to morse code...\n",argv[1]);
        }else if(strcmp(argv[2],"-mc") == 0){
                printf("decoding %s into english...\n",argv[1]);
        }   
    }
    
    if(strcmp(argv[2],"-e") == 0){      //Checks the desired action and acts accordingly, eng to morse
        encrypt(line, input, out);
        printf("%s file completed, output dumped to %s\n",argv[0],argv[3]);
    }else if(strcmp(argv[2],"-mc") == 0){   //Checks the desired action and acts accordingly, morese to eng
        decode(line, input, out);
        printf("%s file completed, output dumped to %s\n",argv[0],argv[3]);
    }else{  //invalid input was given to reach here
        printf("Incorrect input... terminating program");
        fclose(out);
        fclose(input);
        return 0;
    }
    
    fclose(out);
    fclose(input);
    return 0;
}

void encrypt(char* line, FILE* input, FILE* out){   
    int index = 0;
    while(fgets(line, MAX_LINE_LENGTH, input) != NULL){//gets lines
        for(index = 0;line[index] != '\0';index++){   //loops through each line, letter by letter
            englishToMorse(line[index], out);      //actually prints out translation
            if(line[index] == ' '){
                fputs("/|",out);                //End of each word prints out this seperator
            }else if(line[index + 1] != '\0' && line[index+1] != '\n'){//Only prints pipe if not at the end of a line
                fputs("|",out);
            }
        }
        fputs("\n",out);        //Everytime the while loop runs, a new line is created
    }
}

void decode(char* line, FILE* input, FILE* out){
    char* letter; 
    while(fgets(line, MAX_LINE_LENGTH, input) != NULL){//gets lin
        letter = strtok(line, "|"); //splits at pipelines, yeilding letters
        while(letter != NULL) {  
            //printf("%s ", letter); 
            morseToEnglish(letter, out);
            letter = strtok(NULL, "|"); //keep tokenizing notice NULL 
        }   
    }
    fputs("\n",out);
}

void englishToMorse(char ch,FILE *out){// prints corrosponding morse code
    //printf("%c\n", ch);
    switch(ch){
        case 'a':
        case 'A':
            //printf("*-");
            fputs("*-",out);
        break;
        case 'b':
        case 'B':
            //printf("-***");
            fputs("-***",out);
        break;
        case 'c':
        case 'C':
            //printf("-*-*");
            fputs("-*-*",out);
        break;
        case 'd':
        case 'D':
            //printf("-**");
            fputs("-**",out);
        break;
        case 'e':
        case 'E':
            //printf("*");
            fputs("*",out);
        break;
        case 'f':
        case 'F':
            //printf("**-*");
            fputs("**-*",out);
        break;
        case 'g':
        case 'G':
            //printf("--*");
            fputs("--*",out);
        break;
        case 'h':
        case 'H':
            //printf("****");
            fputs("****",out);
        break;
        case 'i':
        case 'I':
            //printf("**");
            fputs("**",out);
        break;
        case 'j':
        case 'J':
            //printf("*---");
            fputs("*---",out);
        break;
        case 'k':
        case 'K':
            //printf("-*-");
            fputs("-*-",out);
        break;
        case 'l':
        case 'L':
            //printf("*-**");
            fputs("*-**",out);
        break;
        case 'm':
        case 'M':
            //printf("--");
            fputs("--",out);
        break;
        case 'n':
        case 'N':
            //printf("-*");
            fputs("-*",out);
        break;
        case 'o':
        case 'O':
            //printf("---");
            fputs("---",out);
        break;
        case 'p':
        case 'P':
            //printf("*--*");
            fputs("*--*",out);
        break;
        case 'q':
        case 'Q':
            //printf("--*-");
            fputs("--*-",out);
        break;
        case 'r':
        case 'R':
            //printf("*-*");
            fputs("*-*",out);
        break;
        case 's':
        case 'S':
            //printf("***");
            fputs("***",out);
        break;
        case 't':
        case 'T':
            //printf("-");
            fputs("-",out);
        break;
        case 'u':
        case 'U':
            //printf("**-");
            fputs("**-",out);
        break;
        case 'v':
        case 'V':
            //printf("***-");
            fputs("***-",out);
        break;
        case 'w':
        case 'W':
            //printf("*--");
            fputs("*--",out);
        break;
        case 'x':
        case 'X':
            //printf("-**-");
            fputs("-**-",out);
        break;
        case 'y':
        case 'Y':
            //printf("-*--");
            fputs("-*--",out);
        break;
        case 'z':
        case 'Z':
            //printf("--**");
            fputs("--**",out);
        break;
        case '\n':
        case '/':
        case '|':
        case ' ':
        break;
        default:
            fputs("XXXX", out);
            break;
    }
}
void morseToEnglish(char *code,FILE *in){// prints corrosponding english from the code
    char* newLetter;
    if(strcmp(code , "*-") == 0){
        fputs("A",in);
    }else if(strcmp(code , "-***") == 0){
        fputs("B",in);
    }else if(strcmp(code , "-*-*") == 0){
        fputs("C",in);
    }else if(strcmp(code , "-**") == 0){
        fputs("D",in);
    }else if(strcmp(code , "*") == 0){
        fputs("E",in);
    }else if(strcmp(code , "**-*") == 0){
        fputs("F",in);
    }else if(strcmp(code , "--*") == 0){
        fputs("G",in);
    }else if(strcmp(code , "****") == 0){
        fputs("H",in);
    }else if(strcmp(code , "**") == 0){
        fputs("I",in);
    }else if(strcmp(code , "*---") == 0){
        fputs("J",in);
    }else if(strcmp(code , "-*-") == 0){
        fputs("K",in);
    }else if(strcmp(code , "*-**") == 0){
        fputs("L",in);
    }else if(strcmp(code , "--") == 0){
        fputs("M",in);
    }else if(strcmp(code , "-*") == 0){
        fputs("N",in);
    }else if(strcmp(code , "---") == 0){
        fputs("O",in);
    }else if(strcmp(code , "*--*") == 0){
        fputs("P",in);
    }else if(strcmp(code , "--*-") == 0){
        fputs("Q",in);
    }else if(strcmp(code , "*-*") == 0){
        fputs("R",in);
    }else if(strcmp(code , "***") == 0){
        fputs("S",in);
    }else if(strcmp(code , "-") == 0){
        fputs("T",in);
    }else if(strcmp(code , "**-") == 0){
        fputs("U",in);
    }else if(strcmp(code , "***-") == 0){
        fputs("V",in);
    }else if(strcmp(code , "*--") == 0){
        fputs("W",in);
    }else if(strcmp(code , "-**-") == 0){
        fputs("X",in);
    }else if(strcmp(code , "-*--") == 0){
        fputs("Y",in);
    }else if(strcmp(code , "--**") == 0){
        fputs("Z",in);
    }else if (strcmp(code, "/") == 0){
        fputs(" ", in);
    }else if(strcmp(code, "XXXX") == 0){
        fputs("#", in);
    }else{
        newLetter = strtok(code, "\n");
        morseToEnglish(newLetter, in);
        fputs("\n", in);
    }
}