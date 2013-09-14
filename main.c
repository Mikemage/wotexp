#include  <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "exp.h"

int skillclass = 0;
int skilllevel = 0;
int paid = 0;


void usage(){
    printf("wrong input, wotexp #skillclass #level\n");
}

int whichlevel(int exp, int ismaster, int *level, int *skclass){
    if(ismaster){
        for(int i = TOTAL_LEVEL -1; i > 0; i--){
            if(mainsk[i]< exp){
                *skclass = 0;
                *level = i;
                return 1;
            }
        } 
    }
    else{
        for(int i = 0; i < TOTAL_PERK; i++){
            if(sk[i][TOTAL_LEVEL - 1] < exp)
                continue;
            for(int j = TOTAL_LEVEL - 1; j > 0; j--){
                if(sk[i][j] < exp){
                    *skclass = i+1;
                    *level = j;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void generateList() {
    //generate main class
    mainsk[0] = 0;
    for(int i = 0; i+1 < TOTAL_LEVEL; i++) {
        mainsk[i+1] = mainsk[i] + ceil(2.0 * 25.0 * pow(100.0, i/100.0));
    }
    sk[0][0] = 0;
    for(int i = 0; i< TOTAL_PERK; i++){
        if(i > 0)
            sk[i][0] = sk[i-1][TOTAL_LEVEL-1];
        for(int j = 0; j+1 < TOTAL_LEVEL; j++) {
            sk[i][j+1] = sk[i][j] + ceil(pow(2, i+2) * 25.0 * pow(100.0, j/100.0));
//            printf("%d, %03d %d %d\n", i, j+1, sk[i][j+1], sk[i][j+1] - sk[i][j]);
        }
    }
}

int getExp(int skclass, int level) {
    int rtn = 0;
    if(skclass == 0)
        rtn = mainsk[level];
    else
        rtn = sk[skclass-1][level];

    return rtn;
}

int main(int argc, char ** argv){
    int rtnClass, rtnLevel;
    int currentExp, afterExp;
    if(argc < 3) {
        usage();
        return 0;
    }
    
    if(!sscanf(argv[1], "%d", &skillclass)){
        usage();
        return 0;
    }
    if(!sscanf(argv[2], "%d", &skilllevel)) {
        usage();
        return 0;
    }

    generateList();
    currentExp = getExp(skillclass, skilllevel);
    printf("current exp %d\n", currentExp);
    if(skillclass == 0) {
        afterExp = currentExp * 0.75;
        whichlevel(afterExp, 1, &rtnLevel, &rtnClass);
        printf("From class %d, %d%% to %d, %d%%\n", skillclass, skilllevel, rtnClass, rtnLevel);

        afterExp = currentExp * 0.5;
        whichlevel(afterExp, 1, &rtnLevel, &rtnClass);
        printf("From class %d, %d%% to %d, %d%%\n", skillclass, skilllevel, rtnClass, rtnLevel);
    }
    else {
        afterExp = currentExp * 0.9;
        whichlevel(afterExp, 0, &rtnLevel, &rtnClass);
        printf("From class %d, %d%% to %d, %d%% exp lost= %d\n", skillclass, skilllevel, rtnClass, rtnLevel, currentExp - afterExp);

        afterExp = currentExp * 0.8;
        whichlevel(afterExp, 0, &rtnLevel, &rtnClass);
        printf("From class %d, %d%% to %d, %d%% exp lost = %d\n", skillclass, skilllevel, rtnClass, rtnLevel, currentExp - afterExp);
    }
    return 0;
}
