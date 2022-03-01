// ;;--(basic without errs)Reverse Polish Notation test--
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAP 1024
int OP_STACK[CAP] = {0};
int loc;
int head=0;

#define PLUS 1
#define MIN 2
#define MUL 3
#define DIV 4

void flush(){

}

void push(int val)
{
    head += 1;
    OP_STACK[head] = val;
}
int pop(){
    return OP_STACK[head];
    head -= 1;
}
void pop_n_res(){
    loc = head;
    head -= 2;
}
void resize_stack(){
    int trace = 1;
    for(int z=loc+1;z<CAP;z++){
        OP_STACK[trace] = OP_STACK[z];
        trace++;
    }
}

void result()
{
    printf("%d",OP_STACK[0]);
}

void rev_pol_not(char *rpn_not)
{
    int set2 = 0;
    int sign_set = 0;
    int sval=0;
    for(int i = 0; i <= strlen(rpn_not); i++){
        switch(rpn_not[i]){
            case '+':
                //printf("OP= %c\n",rpn_not[i]);
                sign_set = 1;
                sval = PLUS;
                break;
            case '-':
                //printf("OP= %c\n",rpn_not[i]);
                sign_set = 1;
                sval = MIN;
                break;
            case '*':
                //printf("OP= %c\n",rpn_not[i]);
                sign_set = 1;
                sval = MUL;
                break;
            case '/':
                //printf("OP= %c\n",rpn_not[i]);
                sign_set = 1;
                sval = DIV;
                break;
            default:
                sign_set = 0;
        }

        if(set2 == 2 && sign_set == 0 && (rpn_not[i] == ' ' && rpn_not[i+1] == '\0')){
            printf("Reverse Polish Notations expects 2 value and 1 operator e.g = 'value' 'value' 'OP'\n");
        }

        // Extra error at end
        else if(set2 == 2 && sign_set == 0 && rpn_not[i] == '\0'){
            printf("Reverse Polish Notations expects 2 value and 1 operator e.g = 'value' 'value' 'OP'\n");
        }

        //WorkLeft
        else if(set2 == 2 && sign_set == 1){
            set2 -= set2;
            sign_set -= sign_set;
            if(sval == PLUS){
                pop_n_res();
                OP_STACK[0] += OP_STACK[1] + OP_STACK[2];
                resize_stack();
                sval -= sval;
            }
            else if(sval == MIN){
                pop_n_res();
                OP_STACK[0] += OP_STACK[1] - OP_STACK[2];
                resize_stack();
                sval -= sval;
            }
            else if(sval == MUL){
                pop_n_res();
                OP_STACK[0] += OP_STACK[1] * OP_STACK[2];
                resize_stack();
                sval -= sval;
            }
            else if(sval == DIV){
                pop_n_res();
                OP_STACK[0] += OP_STACK[1] / OP_STACK[2];
                resize_stack();
                sval -= sval;
            }
            else{
                printf("Unexpected value '%d'\n", sval);
                sval -= sval;
            }
        }

        if(rpn_not[i] != ' ' || rpn_not[i] != ' '){
                if(rpn_not[i] >= '0' && rpn_not[i] <= '9'){
                    char *tmp = (char*)malloc(sizeof(char)*strlen(rpn_not));
                    int t = 0;

                    for(int i2 = i;i2 < strlen(rpn_not);i2++){
                        tmp[t] = rpn_not[i2];
                        t++;
                        if(rpn_not[i2+1] == ';'
                           || rpn_not[i2] == ' ' ||
                           rpn_not[i2+1] == '\0'){

                            i = i2;
                            set2 += 1;
                            int push_ = atoi(tmp);
                            push(push_);
                            //printf("%d\n",atoi(tmp));
                            break;
                        }
                    }
                }

            }
    }
}

int main(int ARGC,char **ARGV)
{
    FILE *expr_file = fopen("expr.emm","r");
    char *expr = (char*)malloc(sizeof(char)*CAP);

    while(fgets(expr,CAP,expr_file)){
       rev_pol_not(expr);
       result();
       flush();
       printf("\n");
    }

    return 0;
}
