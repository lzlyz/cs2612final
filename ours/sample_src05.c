struct Student {
    int id;
    char name[50];
};

union Data {
    int num;
    char ch;
};

enum Color {
    RED,
    GREEN,
    BLUE
};

typedef int *IntPtr;

struct Node {
    int data;
    struct Node *next;
};

int numbers[10];

int (*functionPtr)(int, int);

int (*funcPtrArray[5])(int);

int numbers2[10][100];