#include <stdio.h>

// A Brainfuck interpreter.

FILE* fp;
char data[30000] = {0};             // cells
int ptr = 0;                        // data pointer

int ip = 0;                         // instruction pointer
int instructions[100000] = {0};     // instructions 
int last_instruction;               // pointer to the last instruction

int valid_command(int c){
    return (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']');
}

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
    }
}

int main(int argc, char* argv[]){
    int c;
    fp = fopen(argv[1], "r");

    if(fp){
        while((c = getc(fp)) != EOF){
            if(valid_command(c)){
                instructions[ip++] = c;
            }
        }
        fclose(fp);

        last_instruction = ip - 1;
        ip = 0;

        while(ip <= last_instruction){
            execute_instruction();
        }
    }

    else{
        printf("Could not open file %s.\n", argv[1]);
    }
    
    return 0;
}