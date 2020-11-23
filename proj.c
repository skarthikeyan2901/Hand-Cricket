#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int target = 0;      // target as a global variable

// struct player

typedef struct player
{
    int score;
    char name[100];
} player;

// Stack starts
typedef struct node
{
    struct node *next;
    struct player *p;
} node;

int isEmpty(node *top)
{
    return top->next == NULL;
}

node* create()
{
    node *s = (node *)malloc(sizeof(node));
    if (s == NULL)
    {
        printf("Out of memory\n");
    }
    s->next = NULL;
    return s;
}

void push(node *top, player *p1)
{
    node *new = (node *)malloc(sizeof(node));
    new->p = p1;

    if (top->next == NULL)
    {
        top->next = new;
        new->next = NULL;
    }
    else
    {
        new->next = top->next;
        top->next = new;
    }
}

node* peek(node *top)
{
    return top->next;
}

player* pop(node *top)
{
    if (!isEmpty(top))
    {
        player *tmp = top->next->p;
        node *tp = top;
        node *tmp1 = tp->next;
        tp->next = tp->next->next;
        free(tmp1);
        return tmp;
    }
    else
    {
        printf("Stack is empty\n");
        return 0;
    }
}

//Stack ends

void bat(node *top, int overs);
void bat2(node *top, int overs, int team_no);

void order(struct player *team, int n, node *top, int overs, int innings, int team_no)
{
    printf("Enter the order\n");
    int temp[10];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp[i]);
        do
        {
            if(temp[i] < 1 || temp[i] > n)
            {
                printf("Enter another valid number for the order!\n");
                scanf("%d", &temp[i]);
            }
        } while (temp[i] < 1 || temp[i] > n);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        push(top, team + temp[i]-1);
    }
    printf("\n");
    if(innings == 1)
    {
        bat(top, overs);
    }
    else{
        bat2(top, overs, team_no);
    }
}

void score_board(struct player *team1, struct player *team2, int n)
{
    printf("\n-----------------------------SCORE BOARD------------------------------\n\n");
    printf("               Team 1                ||               Team 2\n");
    printf("-----------------------------------------------------------------------------\n");
    for(int i = 0; i < n; i++)
    {
        printf("       %10s  %3d               ||         %10s  %3d\n", (team1 + i)->name, (team1 + i)->score, (team2 + i)->name, (team2 + i)->score);
    }
}

int main()
{
    player *team1, *team2;
    int n;
    int overs;
    printf("\n----------------------------------------HAND CRICKET GAME------------------------------------------\n\n");
    printf("Enter the number of players for each team: ");
    scanf("%d", &n);
    printf("\n");
    printf("Enter the number of overs: ");
    scanf("%d", &overs);

    team1 = (player *)malloc(n * sizeof(player));
    team2 = (player *)malloc(n * sizeof(player));

    node *top = create();

    printf("\n--Enter the names for Team 1 players--\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter Player %d name: ", i + 1);
        scanf("%s", team1[i].name);
    }

    printf("\n--Enter the names for Team 2 players--\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter Player %d name: ", i + 1);
        scanf("%s", team2[i].name);
    }

    printf("\n");

    int team1Choice, team2Choice, toss, batorbowlChoice, flag;
    do
    {
        flag = 0;
        printf("Team 1, Choose your choice:  \n1 for heads or 2 for tails\n");
        scanf("%d", &team1Choice);
        if (team1Choice == 1)
        {
            team2Choice = 2;
            printf("Team 2's Choice is Tails\n");
        }
        else if (team1Choice == 2)
        {
            team2Choice = 1;
            printf("Team 2's Choice is Heads\n");
        }
        else
        {
            printf("Invalid Choice! Try again!\n\n");
            flag = 1;
        }
        printf("\n");
    } while(flag == 1);
    

    toss = rand() % 2;
    toss += 1;
    if (toss == 1)
        printf("And it's Heads\n\n");
    else
        printf("And it's Tails\n\n");

    if (toss == team1Choice)
    {
        printf("Team 1 Won the Toss\n");
        do
        {
            printf("Choose\n1 - Batting\n2 - Bowling: ");
            scanf("%d", &batorbowlChoice);
            if(batorbowlChoice > 2 || batorbowlChoice < 1)
            {
                printf("Invalid choice! Try again!\n\n");
            }
        } while(batorbowlChoice > 2 || batorbowlChoice < 1);

        printf("\n");

        if (batorbowlChoice == 1)
        {
            order(team1, n, top, overs,1,1);
            printf("-----------------------\n2nd Innings Begins\n-----------------------\n");
            order(team2, n, top, overs,2,2);
        }
        else
        {
            order(team2, n, top, overs,1,2);
            printf("-----------------------\n2nd Innings Begins\n-----------------------\n");
            order(team1, n, top, overs,2,1);
        }
    }
    else
    {
        printf("Team 2 Won the Toss\n");
        do
        {
            printf("Choose\n1 - Batting\n2 - Bowling: ");
            scanf("%d", &batorbowlChoice);
            if(batorbowlChoice > 2 || batorbowlChoice < 1)
            {
                printf("Invalid choice! Try again!\n\n");
            }
        } while(batorbowlChoice > 2 || batorbowlChoice < 1);

        printf("\n\n");

        if (batorbowlChoice == 1)
        {
            order(team2, n, top, overs,1,2);
            printf("-----------------------\n2nd Innings Begins\n-----------------------\n");
            order(team1, n, top, overs,2,1);
        }
        else
        {
            order(team1, n, top, overs,1,1);
            printf("-----------------------\n2nd Innings Begins\n-----------------------\n");
            order(team2, n, top, overs,2,2);
        }
    }
    score_board(team1, team2, n);
    printf("\n\n\t\t\t THANK YOU FOR PLAYING!!!!!\n\n");
}

void bat(node *top, int overs)
{
    int score = 0;
    int i = 0;
    int totalScore = 0;
    int balls = overs*6;
    node *temp = peek(top);

    printf("%s walks in to bat now!\n\n", temp->p->name);
    
    while (i < balls && top->next != NULL)
    {
        int currentBall, currentRun;

        do
        {
            currentBall = atoi(getpass("Bowler enter your number (1 to 6) "));
            if(currentBall > 6 || currentBall < 1)
            {
                printf("You entered an invalid number! Try again!\n\n");
            }
        } while(currentBall > 6 || currentBall < 1);

        do
        {
            currentRun = atoi(getpass("Batsman enter your number (1 to 6) "));
            if(currentRun > 6 || currentRun < 1)
            {
                printf("You entered an invalid number! Try again!\n\n");
            }
        } while(currentRun > 6 || currentRun < 1);

        printf("\n");

        if (currentRun == currentBall)
        {
            player *tmp = pop(top);

            tmp->score = score;
            printf("----------------- %s is Out ----------------\n\n", tmp->name);
            if (score == 0)
                printf("-------------- Hahahaha Duck Out -----------------\n\n");
            printf("%s Score is: %d\n\n", tmp->name, score);
            score = 0;
            node *t = peek(top);
            if(t != NULL)
            {
                printf("%s walks in to bat now!\n\n", t->p->name);
            }
        }
        else
        {
            if (currentRun == 6)
                printf("Sixerrrrrr!!!\n\n");
            else if (currentRun == 4)
                printf("Into the gap for Four!\n\n");
            score += currentRun;
            target += currentRun;
            totalScore += currentRun;
        }
        i++;
        printf("Total score is: %d\n\n", totalScore);
    }
    target += 1;
    printf("Target is: %d\n\n",target);
    int f = 0;
    if(top->next != NULL)
    {
        while(top->next != NULL)
        {
            if(f == 0)
            {
                player *tt = pop(top);
                tt->score = score;
                f = 1;
            }
            else{
                pop(top);
            }
        }
    }
}

void bat2(node *top, int overs, int team_no)
{
    int score = 0;
    int i = 0;
    node *temp = peek(top);
    int balls = overs*6;
    int ballsRem = balls;

    printf("%s walks in to bat now!\n\n", temp->p->name);

    while (i < balls && top->next != NULL && target > 0)
    {
        int currentBall, currentRun;

        do
        {
            currentBall = atoi(getpass("Bowler enter your number (1 to 6) "));
            if(currentBall > 6 || currentBall < 1)
            {
                printf("You entered an invalid number! Try again!\n\n");
            }
        } while(currentBall > 6 || currentBall < 1);

        do
        {
            currentRun = atoi(getpass("Batsman enter your number (1 to 6) "));
            if(currentRun > 6 || currentRun < 1)
            {
                printf("You entered an invalid number! Try again!\n\n");
            }
        } while(currentRun > 6 || currentRun < 1);

        printf("\n");
        ballsRem -= 1;

        if (currentRun == currentBall)
        {
            player *tmp = pop(top);

            tmp->score = score;
            printf("----------------- %s is Out ----------------\n\n", tmp->name);
            if (score == 0)
                printf("--------------- Hahahaha Duck Out -----------------\n\n");
            printf("%s Score is: %d\n\n", tmp->name, score);
            score = 0;
            node *t = peek(top);
            if(t != NULL)
            {
                printf("%s walks in to bat now!\n\n", t->p->name);
            }
        }
        else
        {
            if (currentRun == 6)
                printf("Sixerrrrrr!!!\n\n");
            else if (currentRun == 4)
                printf("Into the gap for Four!\n\n");
            score += currentRun;
            target -= currentRun;
        }

        i++;

        if(target > 0 && balls > 0 && top->next != NULL)
        {
            printf("\n%d more runs to win in %d balls\n\n", target, ballsRem);
        }
    }

    if(target <= 0)
    {
        if(team_no == 1)
        {
            printf("\n\nTEAM 1 WON THE GAME!!!!!!!\n\n");
        }
        else{
            printf("\n\nTEAM 2 WON THE GAME!!!!!!!\n\n");
        }
    }
    else if(target > 1)
    {
        if(team_no == 1)
        {
            printf("\n\nTEAM 2 WON THE GAME!!!!!!!\n\n");
        }
        else{
            printf("\n\nTEAM 1 WON THE GAME!!!!!!!\n\n");
        }
    }
    else
    {
        printf("\n\nIT'S A DRAW!!!!\n\n");
    }
    int f = 0;
    if(top->next != NULL)
    {
        while(top->next != NULL)
        {
            if(f == 0)
            {
                player *tt = pop(top);
                tt->score = score;
                f = 1;
            }
            else{
                pop(top);
            }
        }
    }
}


