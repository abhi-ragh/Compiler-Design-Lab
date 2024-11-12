#include <stdio.h>
#include <string.h>

void main(){
    char op[2],arg1[3],arg2[3],result[5];    
        
    FILE *fp1,*fp2;

    fp1 = fopen("input.txt","r");
    fp2 = fopen("output.txt","w");

    if (fp1 == NULL || fp2 == NULL)
        printf("Error Opening File");

    while(fscanf(fp1,"%s %s %s %s", op, arg1, arg2, result)==4){
        fprintf(fp2,"\nMOV R0, %s",arg1);

        switch(op[0]){
            case '+':
                fprintf(fp2,"\nADD R0, %s",arg2);
                break;
            case '-':
                fprintf(fp2,"\nSUB R0, %s",arg2);
                break;
            case '*':
                fprintf(fp2,"\nMUL R0, %s",arg2);
                break;
            case '/':
                fprintf(fp2,"\nDIV R0, %s",arg2);
                break;
        }
        fprintf(fp2,"\nMOV %s, R0",result);
    }
}
