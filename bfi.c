#include <stdio.h>
#include <stdlib.h>

// A Brainfuck interpreter.
// Usage: ./a.out program.bf

FILE* fp;
char data[30000] = {0};             // cells
int ptr = 0;                        // data pointer

int ip = 0;                         // instruction pointer
int instructions[100000] = {0};     // instructions 
int last_instruction;               // pointer to the last instruction

int c;

void skip_loop(){
    int aux = ip + 1;
    int match = 0;

    while(aux <= last_instruction){
        if(instructions[aux] == ']'){
            if(match == 0){
                ip = aux + 1;
                break;
            }
            else{
                match--;
            }
        }
        else if(instructions[aux] == '['){
            match++;
        }
        aux++;
        }
}

void return_to_loop(){
    int aux = ip - 1;
    int match = 0;

    while(aux >= 0){
    if(instructions[aux] == '['){
        if(match == 0){
            ip = aux + 1;
            break;
        }
        else{
            match--;
        }
    }
    else if(instructions[aux] == ']'){
        match++;
    }
    aux--;
    }
}

void execute_instruction(){
    switch(instructions[ip]){
        case '>':
            ptr++;
            ip++;
            break;

        case '<':
            ptr--;
            ip++;
            break;

        case '+':
            data[ptr]++;
            ip++;
            break;

        case '-':
            data[ptr]--;
            ip++;
            break;

        case '.':
            putchar(data[ptr]);
            ip++;
            break;

        case ',':
            data[ptr] = getchar();
            ip++;
            break;

        case '[':
            if(data[ptr] == 0){
                skip_loop();        // data[ptr] is zero, continue execution after matching ].
            }
            else{
                ip++;
            }
            break;

        case ']':
            if(data[ptr]){
                return_to_loop();   // data[ptr] is non zero, continue execution after matching [.
            }
            else{
                ip++;
            }
            break;
            
        default:
            ip++;
    }
}

int main(int argc, char* argv[]){
    fp = fopen(argv[1], "r"); 

    if(fp){
        while((c = getc(fp)) != EOF){
                instructions[ip++] = c;
            }
        fclose(fp);
    }

    last_instruction = ip - 1;
    ip = 0;

    do{
        execute_instruction();
    }while(ip <= last_instruction);
    
    return 0;
}