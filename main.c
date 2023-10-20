#include <stdio.h>
#include <stdlib.h>
#include "BigNumberLib.h"

int main() {
    struct Node *num1 = NULL, *num2 = NULL;
    struct Node *result = NULL;

    char ch;

    while (1) {
        ch = getchar();
        if (ch == '\n' || !isdigit(ch)) {
            break;
        }
        int digit = ch - '0';
        struct Node *newNode = createNode(digit);
        if (num1 == NULL) {
            num1 = newNode;
        } else {
            newNode->next = num1;
            num1 = newNode;
        }
    }

    while (1) {
        ch = getchar();
        if (ch == '\n' || !isdigit(ch)) {
            break;
        }
        int digit = ch - '0';
        struct Node *newNode = createNode(digit);
        if (num2 == NULL) {
            num2 = newNode;
        } else {
            newNode->next = num2;
            num2 = newNode;
        }
    }

    result = addBigNumbers(num1, num2);
    printBigNumber(result);

    result = subtractBigNumbers(num1, num2);
    printBigNumber(result);

    result = multiplyBigNumbers(num1, num2);
    printBigNumber(result);

    result = divideBigNumbers(num1, num2);
    printBigNumber(result);

    free(num1);
    free(num2);
    free(result);

    return 0;
}
