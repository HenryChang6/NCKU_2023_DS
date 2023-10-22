#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_EXP_SIZE 101 
//postfix to prefix

struct LinkedList{
    char key;
    struct LinkedList *right;
    struct LinkedList *left;
};

typedef struct LinkedList Node;

Node* Create_Node(char key_data, Node* right, Node* left){
    Node *new_node = malloc(sizeof(Node));
    new_node->key = key_data;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

Node* Build_Tree(char postfix[MAX_EXP_SIZE]){
    Node* stack[MAX_EXP_SIZE];
    int stack_top = 0;
    for(int i=0; i<strlen(postfix); i++){
        if(!isalnum(postfix[i])){
            Node* right = stack[--stack_top];
            Node* left = stack[--stack_top];
            stack[stack_top++] = Create_Node(postfix[i],right,left);
        }
        else{
            //Is operand, so add it to the stack directly
            stack[stack_top++] = Create_Node(postfix[i],NULL,NULL);
        }
    }
    return stack[0];
}

void Print_prefix(Node* Tree){
    if(Tree != NULL){
        printf("%c",Tree->key);
        Print_prefix(Tree->left);
        Print_prefix(Tree->right);
    }
}

int main(int argc, char* argv[]) {
    char postfix[MAX_EXP_SIZE];
    scanf("%s", postfix);
    Node* tree = Build_Tree(postfix);
    Print_prefix(tree);
    return 0;
}
