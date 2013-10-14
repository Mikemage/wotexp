#include  <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "exp.h"

void usage(){
    printf("wrong input, wotexp #skillclass #level\n");
}

void printfGroupThousand(int number) {
    if(number == 0){
        printf("0");
        return;
    }
    if(number < 0){
        number = number * -1;
        printf("-");
    }
    if(number / 1000 > 0) {
        printfGroupThousand(number / 1000);
        printf(",");
        printf("%03d", number % 1000);
    }
    else{
        printf("%d", number);
    }
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


void showNextStep(int skclass, int sklevel, int currentExp) {
    int toNextLevel = 0;
    if(skclass == 0) {
        if(sklevel == 100)
            toNextLevel = sk[0][1];
        else
            toNextLevel = mainsk[sklevel+1] - currentExp;
    }
    else if(skclass < 6){
        if(sklevel == 100){
            if(skclass < 4){
                toNextLevel = sk[skclass][1] - currentExp;
            }
            else{
                printf("Exp to next level unknown!\n");
            }
        }
        else
            toNextLevel = sk[skclass-1][sklevel+1] - currentExp;
    }
    else {
        printf("Exp to next level unknown!\n");
    }
    printf("To next level, you need ");
    printfGroupThousand(toNextLevel);
    printf(" exp.\n");
}

void formatOutput(int skclass, int sklevel, int afterclass, int afterlevel, int currentExp, int afterExp, int isPaid) {
    if(isPaid)
        printf("Paid: \nFrom ");
    else
        printf("Free: \nFrom ");
    if(skclass == 0) {
        printf("Major class %3d\n", sklevel);
        printf("To   Major class %3d, Exp lost = ", afterlevel);
        printfGroupThousand(currentExp - afterExp);
        printf(", Residual Exp = ");
        printfGroupThousand(afterExp - getExp(afterclass, afterlevel));
        printf("\n");
    }
    else {
        printf("Perk/Skill %d, %3d%%\n", skclass, sklevel);
        printf("To   Perk/Skill %d, %3d%%, Exp lost = ", afterclass, afterlevel);
        printfGroupThousand(currentExp - afterExp);
        printf(", Residual Exp = ");
        printfGroupThousand(afterExp - getExp(afterclass, afterlevel));
        printf("\n");
    }
    showNextStep(afterclass, afterlevel, afterExp);
}
void showTargetStep(int skclass, int sklevel, int currentExp, int targetclass, int targetlevel) {
    int requiredExp = 0;
    if(skclass > 4 || sklevel > 100 || targetclass > 4 || targetlevel > 100 ||
            (skclass == targetclass && sklevel > targetlevel) ) {
        printf("Wrong input!!\n");
        return;
    }
    if(skclass == targetclass){
        if(skclass == 0) {
            requiredExp = mainsk[targetlevel] - mainsk[sklevel];
        }
        else {
            requiredExp = sk[skclass -1][targetlevel] - sk[skclass -1][sklevel]; 
        }
    }
    else {
        if(skclass == 0) {
            requiredExp =  mainsk[100] - currentExp;
            currentExp = 0;
        }
        requiredExp += sk[targetclass-1][targetlevel] - currentExp;
    }
    if(targetclass == 0){
        printf("To Master %d%%, you need ", targetlevel);
        printfGroupThousand(requiredExp);
        printf(" exp.\n");
    }
    else {
        printf("To %d skill %d%%, you need ", targetclass, targetlevel);
        printfGroupThousand(requiredExp);
        printf(" exp.\n");
    }

}
int max(int a, int b){
    return a > b ? a:b;
}
void showRetrainMaster(int skclass, int sklevel, int currentExp, int isSameClass) {
    int rtnClass, rtnLevel, afterExp;
    rtnClass = skclass;
    printf("Retrain master, ");
    if(isSameClass) {
        printf("same class\n");
        rtnLevel = max(sklevel * 0.9, 75);
    }
    else {
        printf("different class\n");
        rtnLevel = max(sklevel * 0.8, 75);
    }
    afterExp = getExp(rtnClass, rtnLevel);
    formatOutput(skclass, sklevel, rtnClass, rtnLevel, currentExp, afterExp, 1);

/*    if(isSameClass)
        rtnLevel = max(sklevel * 0.8, 50);
    else
        rtnLevel = max(sklevel * 0.6, 50);
    afterExp = getExp(rtnClass, rtnLevel);
    formatOutput(skclass, sklevel, rtnClass, rtnLevel, currentExp, afterExp, 0);
*/
}

void showRetrainSkill(int skclass, int sklevel, int currentExp) {
    int rtnClass, rtnLevel, afterExp;
    if(skclass == 1 && sklevel == 0)
        return;
    printf("Retrain Skill/Perk:\n");
    afterExp = currentExp * 0.9;
    whichlevel(afterExp, 0, &rtnLevel, &rtnClass);
    formatOutput(skclass, sklevel, rtnClass, rtnLevel, currentExp, afterExp, 1);

/*
    afterExp = currentExp * 0.8;
    whichlevel(afterExp, 0, &rtnLevel, &rtnClass);
    formatOutput(skclass, sklevel, rtnClass, rtnLevel, currentExp, afterExp, 0);
*/
}

void showRetrain(int skclass, int sklevel, int currentExp) {
    if(skclass == 0) {
        showRetrainMaster(skclass, sklevel, currentExp, 1);
        showRetrainMaster(skclass, sklevel, currentExp, 0);
    }
    else {
        showRetrainSkill(skclass, sklevel, currentExp);
    }
}

int main(int argc, char ** argv){
    int skillclass = 0;
    int skilllevel = 0;
    int currentExp;
    int targetclass = 0;
    int targetlevel = 0;
    int hasTarget = 0;
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
    if(argc == 5) {
        if(sscanf(argv[3], "%d", &targetclass) && 
           sscanf(argv[4], "%d", &targetlevel)) {
            hasTarget = 1;
        }
        
    }

    generateList();
    currentExp = getExp(skillclass, skilllevel);
    printf("Current exp ");
    printfGroupThousand(currentExp);
    printf("\n");
    showNextStep(skillclass, skilllevel, currentExp);
    printf("============\n");
    showRetrain(skillclass, skilllevel, currentExp);
    printf("============\n");
    if(hasTarget){
        showTargetStep(skillclass, skilllevel, currentExp, targetclass, targetlevel);
        if(targetclass == 1 && targetlevel == 0)
            return 0;
        printf("============\n");
        showRetrain(targetclass, targetlevel, getExp(targetclass, targetlevel));
    }
    return 0;
}
