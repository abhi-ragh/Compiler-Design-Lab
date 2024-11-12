#include <stdio.h>
#include <string.h>

int i=0,j=0;

char action[20],stack[20],input[20];

void reduce_to_e();

void main(){
   printf("Grammar:\nE -> E+E\nE -> E*E\nE -> (E)\nE -> id\n");
   printf("Enter Input: ");
   scanf("%s", input);
   
   printf("\nINPUT\t\tSTACK\t\tACTION\n");
   
   while(j < strlen(input)){
      stack[i++] = input[j++];
      stack[i] = '\0';
      
      printf("%s\t\t%s\t\tSHIFT\n",stack,input + j);
      
      reduce_to_e();
   }
}

void reduce_to_e(){
   int flag = 1;
   while(flag){
      flag = 0;
      
      if (i>=2 && stack[i-2] == 'i' && stack[i-1] == 'd'){
         stack[i-2] = 'E';
         i -= 1;
         stack[i] = '\0';
         flag = 1;
         
         printf("%s\t\t%s\t\tREDUCE to E\n",stack , input + j);
      }
      
      else if (i>=3 && stack[i-3] == 'E' && stack[i-2] == '+' && stack[i-1] == 'E'){
         stack[i-3] = 'E';
         i -= 2;
         stack[i] = '\0';
         flag = 1;
         
         printf("%s\t\t%s\t\tREDUCE to E\n", stack, input + j);
      }
      
      else if (i>=3 && stack[i-3] == 'E' && stack[i-2] == '*' && stack[i-1] == 'E'){
         stack[i-3] = 'E';
         i -= 2;
         stack[i] = '\0';
         flag = 1;
         
         printf("%s\t\t%s\t\tREDUCE to E\n", stack, input + j);
      }
      
      else if (i>=3 && stack[i-3] == '(' && stack[i-2] == 'E' && stack[i-1] == ')'){
         stack[i-3] = 'E';
         i -= 2;
         stack[i] = '\0';
         flag = 1;
         
         printf("%s\t\t%s\t\tREDUCE to E\n", stack, input + j);
      }
   }
   
   if (i==1 && stack[0] == 'E' && input[j] == '\0')
         printf("%s\t\t%s\t\tACCEPT\n",stack, input + j);
}
