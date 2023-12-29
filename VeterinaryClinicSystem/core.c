#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

int inputInt() {
    char newline = 'x';
    int value;

    do {
        scanf("%d%c", &value, &newline);

        if (newline != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }

    } while (newline != '\n');

    return value;
}


int inputIntPositive() {

    int IntPositive = inputInt();
    if (IntPositive <= 0)
        do {
            printf("ERROR! Value must be > 0: ");
            IntPositive = inputInt();
        } while (IntPositive <= 0);

        return IntPositive;
}

int inputIntRange(int lowerBound, int upperBound) {

    int temp = inputInt();

    while (temp < lowerBound || temp > upperBound) {
        printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        temp = inputInt();
    }

    return temp;
}

char inputCharOption(char ValidCharacters[]) {
    char ValidChar;
    char newLine;
   
    int isThere = 0, i=0;

    do {
        
        scanf("%c%c", &ValidChar, &newLine);
       
        if (newLine != '\n') {
            clearInputBuffer();
        }
       
        if ((ValidCharacters[0] == ValidChar || ValidCharacters [1] == ValidChar) && newLine == '\n') {
            isThere = 1;
        }

        if (isThere != 1) {
            printf("ERROR: Character must be one of [");
            for (i = 0; ValidCharacters[i] != '\0'; i++)
                printf("%c", ValidCharacters[i]);
            printf("]: ");
        }

    } while (isThere != 1);

    return ValidChar; 
}

void inputCString(char* Cstring, int minChar, int maxChar) {
    char ch = 'x';
    int size;
    int done = 1;

    do {
        size = 0;

        while (ch != '\n' && size <= maxChar) {
            ch = getchar();
            Cstring[size] = ch;
            size++;
        }

        if (ch == '\n' && size <= (maxChar + 1)) {
            size--;
            Cstring[size] = '\0';
        }
        else {
            Cstring[maxChar] = '\0';
            clearInputBuffer();
        }


        if (size < minChar || size > maxChar) {
            if (minChar == maxChar) {
                printf("Invalid %d-digit number! Number: ", minChar);
                ch = 'x';
            }
            else if (size > maxChar) {
                printf("ERROR: String length must be no more than %d chars: ", maxChar);
                ch = 'x';
            }
            else if (size < minChar) {
                printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
                ch = 'x';
            }
        }
        else
        {
            done = 0;
        }

    } while (done);


}

void displayFormattedPhone(const char* phoneString) {
    int i;
    //int max = 10;

    /* flag */ int invalidNumbers = 0;

    // if pointer is not null, calculate the size -> it's going to be 1 more for '\0'.
    if (phoneString != NULL) {

        for (i = 0; i <= 9; i++) {
            if (!(phoneString[i] >= '0' && phoneString[i] <= '9'))
                invalidNumbers = 1;
        }
    }

    // displaying only the correct one
    if (strlen(phoneString) == 10 && invalidNumbers != 1) {
        printf("(");
        for (i = 0; i < 3; i++)
            printf("%c", phoneString[i]);
        printf(")");
        for (i = 3; i < 6; i++)
            printf("%c", phoneString[i]);
        printf("-");
        for (i = 6; i < 10; i++)
            printf("%c", phoneString[i]);
    }
    else
        printf("(___)___-____");

}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

