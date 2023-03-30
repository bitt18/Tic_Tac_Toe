#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

void get_rules(char [], char []);
void show_board_positions();
void show_current_board(int (*)[3]);
int check_win(int (*board)[3]);
int get_move(char[],char[], int(*)[3]);
int valid_move(int, int(*)[3]);

int main()
{
	int board[3][3]={{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
	int (*bptr)[3]=board;
	int move,row,column,i,j,attempt1,attempt2,tot_moves=0;
	char plyr1[20],plyr2[20];
	printf("______ Tic-Tac-Toe _______\n\n");
	printf("Enter Player 1's nickname ");
	gets(plyr1);
	printf("Enter Player 2's nickname ");
	gets(plyr2);
	get_rules(plyr1,plyr2);
	show_board_positions();
	while(tot_moves<10)
	{
	    move=get_move(plyr1,plyr2,bptr);
	    if(move==-1)
            break;
        tot_moves++;
    	move--;
    	row=move/3;
    	column=move%3;
    	board[row][column]=1;
    	show_current_board(bptr);
    	if(check_win(bptr))
        {
            printf("Congrats %s, you have won",plyr1);
            break;
        }
        if(tot_moves==9)
        {
            printf("\nGame has ended in a draw between %s and %s",plyr1,plyr2);
            break;
        }
    	move=get_move(plyr2,plyr1,bptr);
	    if(move==-1)
            break;
        tot_moves++;
    	move--;
    	row=move/3;
    	column=move%3;
    	board[row][column]=2;
    	show_current_board(bptr);
    	if(check_win(bptr))
        {
            printf("Congrats %s, you have won",plyr1);
            break;
        }
	}
	return 0;
}

void get_rules(char p1[], char p2[])
{
	printf("\nRules\n");
	printf("%s's sign: X (Capital letter X)\n",p1);
	printf("%s's sign: O (Capital letter O)\n",p2);
	printf("To exit, enter 0\n");
}

void show_board_positions()
{
	printf("\nThe block numbers are\n\n");
	int i;
	for(i=1;i<=3;i++)
	{
    	printf(" %d | %d | %d",3*i-2,3*i-1,3*i);
    	printf("\n---|---|---\n");
	}
	printf("\n");
}

void show_current_board(int (*board)[3])
{
    printf("\nCurrent board\n");
    int i,j,num;
    char ch;
	for(i=0;i<3;i++)
	{
	    for(j=0;j<3;j++)
        {
            num=*(*(board+i)+j);
            ch=(num==-1)? ' ' : (num==1)? 'X' : 'O';
            printf(" %c ",ch);
            if(j!=2)
                printf("|");
        }
    	printf("\n---|---|---\n");
	}
	printf("\n");

}

int get_move(char p1[],char p2[],int (*board)[3])
{
    int move,attempts=0;
    printf("%s, Enter which cell you want to put your sign in ",p1);
    scanf("%d",&move);
    while(attempts<3)
    {
        attempts++;
        if(valid_move(move,board)==0)
        {
            printf("\nBox already occupied. Enter an empty box\nNumber of invalid moves left: %d\n\n",4-attempts);
            scanf("%d",&move);
        }
        else
            return move;
    }
    if(valid_move(move,board)==0)
    {
        printf("You have entered more than 3 invalid moves. %s wins the game.",p2);
        return -1;
    }
}

int valid_move(int move, int (*board)[3])
{
    int row,col,box;
    move--;
    row=move/3;
    col=move%3;
    box=board[row][col];
    if(box==1 || box==2)
        return 0;
    else
        return 1;
}

int check_win(int (*board)[3])
{
    int i,j,row_flag,col_flag,ld_flag,rd_flag,row_win,col_win;
    int ldiagonal=board[0][0];
	int rdiagonal=board[0][2];
	col_flag=row_flag=ld_flag=rd_flag=0;
	for(i=0;i<3;i++)
	{
    	row_win=board[i][0];
    	col_win=board[0][i];
    	for(j=0;j<3;j++)
    	{
                if(row_win==board[i][j] && board[i][j]!=-1)
                    row_flag++;
                if(col_win==board[j][i] && board[j][i]!=-1)
                    col_flag++;
                if(i==j && board[i][j]==ldiagonal && board[i][j]!=-1)
                    ld_flag++;
                if(i+j==2 && board[i][j]==rdiagonal && board[i][j]!=-1)
                    rd_flag++;
    	}
    	if(row_flag==3 || col_flag==3)
            break;
        else
            row_flag=col_flag=0;
	}
	if(row_flag==3 || col_flag==3 || ld_flag==3 || rd_flag==3)
        return 1;
    else
        return 0;
}