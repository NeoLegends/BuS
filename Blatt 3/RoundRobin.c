#include <stdio.h>

void outputLine(int processes[], int Q, int totalWait, int numProc){
    int i;
    float avgWait;
    avgWait = (int) ((100 * (totalWait))/numProc);   //Nachkommastellen abschneiden
    avgWait = avgWait/100;
    printf("  ");
    if(Q < 10){
        printf("0");
    }
    printf("%i  ", Q);
    for(i = 0; i < numProc; i++){
        if(processes[i] < 10){
            printf("0");
        }
        printf("%i  ", processes[i]);
    }
    printf("%.2f  \n", avgWait);

}

void outputBasic(int numProc){
    int i;
    printf("#  Q  ");
    for(i = 1; i <= numProc; i++){
        printf("P%i  ", i);
    }
    printf("Avg.Time\n");
    printf("#");
    for(i = 1; i <= numProc; i++){
        printf("-----");
    }
    printf("\n");
}

void reset(int a1[], int a2[], int b[],int c[], int numProc){
    int i;
    for(i = 0; i < numProc; i++){
        a2[i] = a1[i];
        b[i] = -1;
        c[i] = 0; 
    }
}

int main(void){
    int numOfProcesses = 8;
    int t_P[numOfProcesses], t_End[numOfProcesses], tLastActive[numOfProcesses], 
        tempT_P[numOfProcesses];
    int totalRunTime = 0;
    int t, i, curQ, curT;
    int maxQ = 13;
    int totalWait;
    int curP;

    t_P[0] = 6;
    t_P[1] = 13;
    t_P[2] = 7;
    t_P[3] = 3;
    t_P[4] = 4;
    t_P[5] = 9;
    t_P[6] = 10;
    t_P[7] = 11;

    for(i = 0; i < numOfProcesses; i++){
        totalRunTime += t_P[i];
    }
    outputBasic(numOfProcesses);

    for(curQ = 1; curQ <= maxQ; curQ++){    //calculate for every incrementing Q
        curT = 0;
        curP = 0;
        totalWait = 0;
        reset(t_P, tempT_P, tLastActive, t_End, numOfProcesses);

        for(t = 0; t < totalRunTime; t++){
            while(!tempT_P[curP] || (curT-curQ == 0 && t != 0)){    //swap processes until one which has runtime left. (can't be a deadlock due to t < totalRunTime)
                curP = (curP + 1)%numOfProcesses;
                curT = 0;               //counts clocks this process already had.
            }
            if(!curT){                  //this process wasn't assigned in the last cycle.
                totalWait += t - (tLastActive[curP] + 1);
            }
            tLastActive[curP] = t;
            tempT_P[curP]--;
            curT++;
            if(!tempT_P[curP]){         //no computational time required anymore
                t_End[curP] = t + 1;
            }
        }
        outputLine(t_End, curQ, totalWait, numOfProcesses);
    }



}

