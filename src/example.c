#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int* primeFactors(int n);
char* primeFactorsAsString(int n);

int main() {
   
    PrintXY(1, 1, "--n = )", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
    PrintXY(1, 2, "--PrimeFactorise(n) = ", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
    char *buffer = (char*) malloc(256); //creates tempory storage
    int start = 0;
    int cursor = 0;
    buffer[0] = '\0';

    int key;

    DisplayMBString((unsigned char*) buffer, start, cursor, 5, 1);


    while (1) {
        GetKey(&key);

        if (key == KEY_CTRL_EXE) {                                                      //clears all the text

            int isInt = 1;
            for(int i = 0; i < strlen(buffer); i++){
                if(!isdigit(buffer[i])){
                    isInt = 0;
                    break;
                }
            }

            if(isInt){
                int input = atoi(buffer); //converts string into int
                char bufferTwo[102] = "";
                strcat(bufferTwo, primeFactorsAsString(input));

                if(strcmp(bufferTwo, "--Ur number is too big!                       ") == 0){
                    PrintXY(1, 4, "--ERROR!                     ", 0, TEXT_COLOR_RED);
                    PrintXY(1, 5, bufferTwo, 0, TEXT_COLOR_RED); //prints the prime factors
                }
                else{

                    


                    //PrintXY(1, 4, bufferTwo, 0, TEXT_COLOR_BLUE); //prints the prime factors
                    //PrintXY(1, 5, "--                      ", 0, TEXT_COLOR_BLACK);

                    //==================================//


                    // initialize the lines to be outputted
                    char lineOne[24] = {0}; lineOne[0] = lineOne[1] = '-';
                    char lineTwo[24] = {0}; lineTwo[0] = lineTwo[1] = '-';
                    char lineThree[24] = {0}; lineThree[0] = lineThree[1] = '-';
                    char lineFour[24] = {0}; lineFour[0] = lineFour[1] = '-';

                    int p = 0;
                    int maxLineLength = 21;

                    //check maxlinelength if it is ' ', if so then print, if not go back a line and recheck
                    for(int i = 0; i < maxLineLength; i ++){
                        if (bufferTwo[maxLineLength - i] == ' '){
                            strncpy(lineOne+2, bufferTwo, maxLineLength - i);
                            p = p + (maxLineLength - i);
                            break;
                        }
                    }

                    for(int i = 0; i < maxLineLength; i ++){
                        if (bufferTwo[maxLineLength - i + p] == ' '){
                            strncpy(lineTwo+2, bufferTwo + p, maxLineLength - i + p);
                            p = p + (maxLineLength - i);
                            break;
                        }
                    }

                    for(int i = 0; i < maxLineLength; i ++){
                        if (bufferTwo[maxLineLength - i + p] == ' '){
                            strncpy(lineThree+2, bufferTwo + p, maxLineLength - i + p);
                            strcpy(lineFour + 2, bufferTwo + maxLineLength - i + p);
                            break;
                        }
                    }

                    //bugs:
                    //  fix extra spaces at the start of line2,3,4
                    //  error messages not overlayed properly


                    //print all the lines
                    PrintXY(1, 4, lineOne, 0, TEXT_COLOR_BLUE);
                    PrintXY(1, 5, lineTwo, 0, TEXT_COLOR_BLUE);
                    PrintXY(1, 6, lineThree, 0, TEXT_COLOR_BLUE);
                    PrintXY(1, 7, lineFour, 0, TEXT_COLOR_BLUE);

                    //==================================//

                }

                
            }
            else{
                PrintXY(1, 4, "--ERROR!                  ", 0, TEXT_COLOR_RED);
                PrintXY(1, 5, "--Input must be an int!", 0, TEXT_COLOR_RED);
            }

            buffer[0] = '\0'; //adds '' to the start of the string
            start = 0; //resets the start and the curser to 0
            cursor = 0;
            DisplayMBString((unsigned char*) buffer, start, cursor, 5, 1);  //displays curser
        } else if (key && key < 30000) {                                                 //adds text
            cursor = EditMBStringChar((unsigned char*) buffer, 256, cursor, key); //move curser
            DisplayMBString((unsigned char*) buffer, start, cursor, 5, 1);        //render inputed letter
        } else {
            EditMBStringCtrl((unsigned char*) buffer, 256, &start, &cursor, &key, 5, 1);
        }
    }
 
    return 0;
}


int* primeFactors(int n)
{
    if (n < 2) {
        static int result[2];
        result[0] = 1;
        result[1] = n;
        return result; //return 1 and n
    }
    //
    else if (n > 99999999){
        static int result[1];
        result[0] = 69;
        return result;
    }
    //

    int size;
    size = 0;
    static int factors[33];
    //Max int has 32 factors, plus first spot in array for length of array.

    while (n%2 == 0) // check if n is divisible by 2
    {
        size++;
        factors[size] = 2; // if so, append 2 to Factors
        n = n/2;
    }

    for (int i = 3; i <= n; i = i+2) //check if n is divible by  2i+1 (odd numbers)
    {
        while (n%i == 0)
        {
            size++;
            factors[size] = i; // if so, append n to factors
            n = n/i;
        }
    }
    if (n > 2)
    {
        size++;
        factors[size] = n;
    }

    factors[0] = size;
    return factors;
}

char* primeFactorsAsString(int n) {
    int *factors;

    factors = primeFactors(n);

    if (factors[0] > 25) {
        return "Ur number is too big!                       ";
    }
    static char result[100];
    result[0] = 0;
    char buffer[100];


    for (int i = 1; i < factors[0]; i++)
    {
        sprintf(buffer, "%d, ", factors[i]);
        strcat(result, buffer);
    }

    sprintf(buffer, "%d", factors[factors[0]]); //store factors in buffer
    strcat(result, buffer); //merge results with buffer
    strcat(result, "                                                   "); //merge results with a long space

    return result;
}