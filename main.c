//  A SIMPLE COMPILER IN C

// Importing libraries
#include <stdio.h> //standard IO library

#include <stdlib.h> //standard library function - memory allocation

#include <ctype.h> //Isidigit()

#include <string.h> //String Manipulation

/*
To create this project we are considering using 3 components which are
1. Tokenizer
2. Parser
3. Code Generator
*/

// TOKENIZER

// Enumeration for different types of tokens
typedef enum {
    TOKEN_NUMBER, 
    TOKEN_PLUS, 
    TOKEN_MINUS,
    TOKEN_MULTIPLY, 
    TOKEN_DIVIDE,
    TOKEN_END,
} TokenType;


// Defining Structures to represent a particular token

typedef struct{
    TokenType type;
    int value;

} Token;

// Function to tokenize the input string
Token  *tokenize(const char *input){
    // memory allocation
    Token *tokens = malloc(256 * sizeof(Token));
    int pos = 0;

    while(*input){
        if (isdigit(*input)){
            tokens[pos].type = TOKEN_NUMBER;
            input++;
            pos++;

        }else if(*input == '+'){
            tokens[pos].type = TOKEN_PLUS;
            input++;
            pos++;

        }else if(*input == '-'){
            tokens[pos].type = TOKEN_MINUS;
            input++;
            pos++;

        }else if( *input == '*'){
            tokens[pos].type = TOKEN_MULTIPLY;
            input++;
            pos++;

        }else if( *input == *"/"){
            tokens[pos].type = TOKEN_DIVIDE;
            input++;
            pos++;

        } else{
            //Skip any other character
            input++;
        }
    }
    // Mark the end of the token
    tokens[pos].type = TOKEN_END;
    return tokens;
}



// Coding the parser of the compiler
// We are basically going to create a function that evaluates and parse the token
// Function to 
// 1. Parse Token
// 2. Evaluate token Expression
int parse(Token *tokens, int *result){
    int pos = 0; // A
    if(tokens[pos].type != TOKEN_NUMBER){
        return 0; //invalid expression

    }
    *result = tokens[pos].value;
    pos++;

    // Loop through the tokens and evaluatet the expression
    while(tokens[pos].type != TOKEN_END){
        if(tokens[pos].type == TOKEN_PLUS){
            pos++;
            if(tokens[pos].type != TOKEN_NUMBER){
                return 0;
            }
            *result += tokens[pos].value;
        }else if(tokens[pos].type == TOKEN_MINUS){
            pos++;
            if(tokens[pos].type != TOKEN_NUMBER){
                return 0;
            }
            *result -= tokens[pos].value;
        }else if(tokens[pos].type == TOKEN_MULTIPLY){
            pos++;
            if(tokens[pos].type != TOKEN_NUMBER){
                return 0;
            }
            *result *= tokens[pos].value;
        }else if(tokens[pos].type == TOKEN_DIVIDE){
            pos++;
            if(tokens[pos].type != TOKEN_NUMBER){
                return 0;
            }
            *result /= tokens[pos].value;
        }else{
        
            // Invalid Token
            return 0;
        }
        pos++;
    }
    return 1;  //Successful parsing and evaluation
}


// Assembly Code Generation (Third Component)
// Code Generator Definition [Assembly-Like Instructions]

void generate_assembly(Token *tokens){
    int pos = 0;
    // Load the first numebr -> register
    
    printf("LOAD %d\n", tokens[pos].value);
    pos++;
    

    while(tokens[pos].type != TOKEN_END){

        if (tokens[pos].type == TOKEN_PLUS){
            // If the token is +, generated ADD instruction
            pos++;
            printf("ADD %d\n", tokens[pos].value);
        } else if(tokens[pos].type == TOKEN_MINUS){
            // If the token is -, generated MINUS instruction
            pos++;
            printf("SUB %d\n", tokens[pos].value);   
        } else if(tokens[pos].type == TOKEN_MULTIPLY){
            // if the token is *, generated MULTIPLY instruction
            pos++;
            printf("MUL %d\n", tokens[pos].value);
        } else if(tokens[pos].type == TOKEN_DIVIDE){
            // if the token is /, generated DIVIDE instruction
            pos++;
            printf("DIV %d\n", tokens[pos].value);
        }
        pos++;

    }
}


// Main Function
int main(){
    // Declare a buffer to hold the input string
    char input[256];
    printf("Enter the Arithmetic Expression e.g 3 + 5 * 3 / 3   ");
    fgets(input, sizeof(input), stdin);

     // Reallsing new line character 
     size_t len = strlen(input);

     if(len > 0 && input[len -1] == '\n'){
        input[len-1] = '\0';

     }
     

    // Tokenizing the actual input entered by the user
    Token *tokens = tokenize(input);


   


    int result;

    if (parse(tokens, &result)){
        printf("Parsed result: %d\n", result);

        // Generate the assembly line instruction
        generate_assembly(tokens);
    } else{
        printf("Invalid Expression");
    }
    free(tokens);
    return 0;  // Exist code for 
}




