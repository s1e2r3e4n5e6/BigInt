#include "BigNumberLib.h"
#include <stdlib.h>

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Node* addBigNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    struct Node* temp = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry != 0) {
        int sum = carry;
        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum %= 10;

        struct Node* newNode = createNode(sum);
        if (result == NULL) {
            result = newNode;
            temp = result;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }

    return result;
}

struct Node* subtractBigNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    struct Node* temp = NULL;
    int borrow = 0;

    while (num1 != NULL || num2 != NULL) {
        int diff = borrow;
        if (num1 != NULL) {
            diff += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            diff -= num2->data;
            num2 = num2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        struct Node* newNode = createNode(diff);
        if (result == NULL) {
            result = newNode;
            temp = result;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }

    return result;
}

struct Node* multiplyBigNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = createNode(0);
    struct Node* tempResult = result;

    while (num2 != NULL) {
        int carry = 0;
        struct Node* tempNum1 = num1;
        result = tempResult;

        while (tempNum1 != NULL) {
            int product = (num2->data * tempNum1->data) + carry;

            if (result == NULL) {
                result = createNode(product % 10);
                tempResult = result;
            } else {
                while (result->next != NULL) {
                    result = result->next;
                }
                result->next = createNode(product % 10);
            }

            carry = product / 10;
            tempNum1 = tempNum1->next;
        }

        if (carry > 0) {
            while (result->next != NULL) {
                result = result->next;
            }
            result->next = createNode(carry);
        }

        num2 = num2->next;
        tempResult = addBigNumbers(tempResult, createNode(0));
    }

    return tempResult;
}

struct Node* divideBigNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;

    while (num2 != NULL) {
        if (num2->data != 0) {
            break;
        }
        num2 = num2->next;
    }

    if (num2 == NULL) {
        exit(1);
    }

    while (num1 != NULL) {
        int quotient = 0;
        struct Node* tempNum1 = num1;

        while (tempNum1 != NULL && isGreaterOrEqual(tempNum1, num2)) {
            tempNum1 = subtractBigNumbers(tempNum1, num2);
            quotient++;
        }

        if (result == NULL) {
            result = createNode(quotient);
        } else {
            struct Node* tempResult = result;
            while (tempResult->next != NULL) {
                tempResult = tempResult->next;
            }
            tempResult->next = createNode(quotient);
        }

        num1 = num1->next;
    }

    return result;
}

int isGreaterOrEqual(struct Node* num1, struct Node* num2) {
    if (num1 == NULL) {
        return 0;
    }
    if (num2 == NULL) {
        return 1;
    }

    num1 = reverseLinkedList(num1);
    num2 = reverseLinkedList(num2);

    while (num1 != NULL && num2 != NULL) {
        if (num1->data > num2->data) {
            return 1;
        } else if (num1->data < num2->data) {
            return 0;
        }
        num1 = num1->next;
        num2 = num2->next;
    }

    return 1;
}

#endif
