#include <stdio.h>
#include <stdlib.h>
int main(){
    int i, j;
    int numA, numB, numC;
    char *cur = malloc(sizeof(char) * 500);
    *cur = 0;
    for(j = 0; j < 20; j++){
        scanf("%s", cur);
        numA = 0;   
        numB = 0;
        numC = 0;
        for(i = 0; i < 500; i++){
            if(*(cur + i) == 'A'){
                numA++;
            }else if(*(cur + i) == 'B'){
                numB++;
            }else if(*(cur + i) == 'C'){
                numC++;
            }
        }
        printf("\n In the past 500 chars there have been:\n A's: %d \n B's %d \n C's %d", numA, numB, numC);
    }
    return 0;
}