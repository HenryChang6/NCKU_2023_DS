#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_EXP_SIZE 100 
//infix to postfix

int IsOperator(char ch){
    return(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' );
}

int Precedence(char ch){
    if(ch == '^') return 3;
    else if(ch == '*' || ch == '/') return 2;
    else if(ch == '+'||ch == '-') return 1;
    return -1;
}

int main(int argc, char* argv[]) {
    
    char infix[MAX_EXP_SIZE + 1], stack[MAX_EXP_SIZE + 1], postfix[MAX_EXP_SIZE + 1];
    int  stack_top_index = -1, postfix_top_index = -1;
    scanf("%s", infix);
    for(int i=0; i < strlen(infix); i++){
        //檢查是不是 Opearator 跟 Operand 以外的東西
        if(infix[i] == ' '|| infix[i] == '\t') continue;

        //檢查是不是 Operand 直接加入postfix expression
        else if(isalnum(infix[i])){
            postfix[++postfix_top_index] = infix[i];
        }

        //檢查輸入是不是 '(' 直接放進stack
        else if(infix[i] == '('){
            stack[++stack_top_index] = infix[i];
        }    

        //檢查輸入是不是 ')' 直到遇到 '(' 不然就瘋狂pop
        else if(infix[i] == ')'){
            while(stack[stack_top_index] != '('){
                //其實下面兩行就等於 postfix[++postfix_top_index] = stack[stack_top_index--]; 我後面會直接這樣寫
                postfix[++postfix_top_index] = stack[stack_top_index];
                stack_top_index--;
            }
            //'('也要把它處理掉
            stack_top_index--;
        }

        //檢查是不是Operator
        else if(IsOperator(infix[i])){
            //這個while的作用是要先處理掉所有不能直接將Opearator放進stack的情況 
            while(stack_top_index > -1 && Precedence(stack[stack_top_index]) >= Precedence(infix[i])){
                //stack top's precedence 比較大 要先從stack吐出來
                if(Precedence(stack[stack_top_index]) > Precedence(infix[i]))
                    postfix[++postfix_top_index] = stack[stack_top_index--];
                //precedence相同 所以比associativity
                else if(Precedence(stack[stack_top_index]) == Precedence(infix[i])){
                    // ^特例處理: right associativity 可以直接放進stack 所以while裡面不用寫 '^'情況的code
                    if(infix[i] != '^') 
                        postfix[++postfix_top_index] = stack[stack_top_index--];
                }
                //stack top's precedence 比較大 可以直接放進去stack 所以while裡面不用寫<情況的code
            }
            //上面的while已經幫我們將例外排除 現在可以安心的把operator放進stack了
            stack[++stack_top_index] = infix[i];
        }
    }
    //把stack都清乾淨
    while(stack_top_index > -1){
        // error detection
        if(stack[stack_top_index] == '(') {
            printf("Invalid expression!");
            break;
        }
        postfix[++postfix_top_index] = stack[stack_top_index--];
    }
    postfix[++postfix_top_index] = '\0';
    printf("%s", postfix);
    return 0;
}
