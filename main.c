#include <stdio.h>
#include <stdlib.h>
#include<time.h>


int opening();
int roll_a_dice();
int calculate_score(int,int);
int play_user(int);
int play_computer(int);
void scoresheet(int,int);
char computer_strategy_decider(int,int);

int main()
{
    srand(time(NULL));
    int whoStarts=opening();//based on the result of the opening, either user or computer will start the game
    int roundCounter=1;//counter of game rounds.
    int userRoundScore,computerRoundScore,overallUserScore=0,overallComputerScore=0;//starting scores of players

    while(roundCounter<=6){
        if(whoStarts==1){//this means user will start the game
            userRoundScore=play_user(roundCounter);
            computerRoundScore=play_computer(roundCounter);
        }
        else{//this means computer will start the game
            computerRoundScore=play_computer(roundCounter);
            userRoundScore=play_user(roundCounter);
        }
        overallUserScore+=userRoundScore;//adding every roundScores to overall scores
        overallComputerScore+=computerRoundScore;
        scoresheet(overallComputerScore,overallUserScore);//then display these scores in this function
        roundCounter++;
    }

    if(overallComputerScore>overallUserScore)
        printf("I AM THE WINNER!\n");
    else if(overallUserScore>overallComputerScore)
        printf("YOU ARE THE WINNER!\n");
    else
        printf("DRAW!\n");


return 0;

}

int roll_a_dice(){
    return 1+(rand()%6);
}
int opening(){
    char rollChoice;
    int computerDice,userDice;
    printf("Welcome to the Big Pig game.\n");
    printf("Lets get started!\n\n");
    do{
        fflush(stdin);
        computerDice=roll_a_dice();
        printf("I have rolled the dice and got %d!\n",computerDice);
        printf("Shall I roll the dice for you(Y/N)? ");
        scanf("%c",&rollChoice);
        while(rollChoice!='Y' && rollChoice!='N'){
            fflush(stdin);
            printf("Please enter 'Y' or 'N' : ");
            scanf("%c",&rollChoice);
        }

    }while(rollChoice!='Y');

    userDice=roll_a_dice();
    printf("I have rolled the dice for you and got %d!\n\n",userDice);
    if(userDice>computerDice)//in equality, computer starts
        return 1;//indicates that user will start the round
    else
        return 0;//indicates that computer will start the round

}
int calculate_score(int dice1, int dice2){
    if(dice1!=dice2){
        if(dice1==1 || dice2==1)
            return 0;
        else
            return dice1+dice2;
    }
    else{
        if(dice1==1)
            return 25;
        else
            return 2*(dice1+dice2);
    }
}
int play_user(int roundCounter){
    printf("Round %d -- Your Turn:\n",roundCounter);
    printf("-----------------------------------------------------------------------\n");
    char choice;//user enters 'Y'
    int dice1,dice2,singleScore,roundScore=0;
    int endTurnFlag=0;

    do{
        fflush(stdin);
        dice1=roll_a_dice();
        dice2=roll_a_dice();
        printf("You got -> [Dice1]:%d [Dice2]:%d\n",dice1,dice2);
        singleScore=calculate_score(dice1,dice2);
        printf("Score:%d\n",singleScore);
        roundScore+=singleScore;
        if(dice1==dice2){
            printf("Doubles! Roll again!\n");
            continue;
        }
        else{
            if(dice1==1||dice2==1){
                printf("You got a single one! End of your turn!\n");
                endTurnFlag=1;
            }
            else{
                fflush(stdin);
                printf("Do you want to continue (Y/N)? ");
                scanf("%c",&choice);
                while(choice!='Y' && choice!='N'){
                    fflush(stdin);
                    printf("Please enter 'Y' or 'N' : ");
                    scanf("%c",&choice);
                }
                if(choice=='Y')
                    continue;
                else{
                    endTurnFlag=1;
                    break;
                }
            }
        }
    }while(!endTurnFlag);

    printf("Your round score:%d\n\n",roundScore);
    return roundScore;
}
int play_computer(int roundCounter){
    printf("Round %d -- My Turn:\n",roundCounter);
    printf("-----------------------------------------------------------------------\n");
    int dice1,dice2,singleScore,roundScore=0;
    int endTurnFlag=0;

    do{

        fflush(stdin);
        dice1=roll_a_dice();
        dice2=roll_a_dice();
        printf("I got -> [Dice1]:%d [Dice2]:%d\n",dice1,dice2);
        singleScore=calculate_score(dice1,dice2);
        printf("Score:%d\n",singleScore);
        roundScore+=singleScore;
        int strategy=computer_strategy_decider(dice1,dice2);
        if(strategy=='D'){
            printf("Doubles! Roll again!\n");
            continue;
        }
        else{
            if(strategy=='E'){
                printf("I got a single one! End of my turn!\n");
                endTurnFlag=1;
            }
            else{
                if(strategy=='C')
                    continue;
                else{
                    endTurnFlag=1;
                    break;
                }
            }
        }
    }while(!endTurnFlag);

    printf("My round score:%d\n\n",roundScore);
    return roundScore;
}
char computer_strategy_decider(int dice1,int dice2){

//D stands for "doubles"
//E stands for " 'end' of the turn"
//C stands for " 'continue' rolling the dice"
//S stands for " 'stop' rolling the dice"


        if(dice1==dice2){
            return 'D';
        }
        else{
            if(dice1==1||dice2==1){
                return 'E';

            }
            else{
                int randomChoice=rand()%2;
                printf("Do you want to continue (Y/N)? ");

                if(randomChoice==1){
                    printf("Y\n");
                    return 'C';
                }

                else{
                    printf("N\n");
                    return 'S';
                }
            }
        }
}
void scoresheet(int computerScore,int userScore){
    printf("Our scoresheet:\n");
    printf("==============================================\n");
    printf("My Score\tYour Score\n");
    printf("%d\t\t%d\n\n",computerScore,userScore);
}




