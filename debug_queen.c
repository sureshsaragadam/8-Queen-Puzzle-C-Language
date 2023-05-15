/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Suresh Saragadam 2011 <saragadamsuresh@gmail.com>
 * 
 * 
8-queen is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any
	 later version.
 * 
 * 8-queen is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



int wayback=1;
int found=0;
int total=0;
int ch;

int brd[8][8];

struct point 
{
int x;
int y;
};

struct point tp, ctp;

void print_board();
void save_board();
void init_board(int n, int m, struct point *);		

int trace_the_board_for(struct point, struct point *);
struct point back_track(struct  point, struct point *);

int row(int);
int col(int);
int fdu(int, int);
int fdd(int, int);
int bdd(int, int);
int bdu(int, int);

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, m, status = 1; 
    struct point sp={0,0}, path[7];

    tp = sp;
    ctp = sp;
 
    system("clear");

	init_board(n,m, path);

	status = trace_the_board_for(sp, path);

    if(status == 1)
	printf("\n\n* Backtrack Over *\n");

	printf("\n\nTotal found - %d\n", total);
	return(0);
}//main is defined.

	
int trace_the_board_for(struct point p, struct point track[])
{
    int b;
    char ch;
    struct point np;

    while ( (p.x <= 7) && (wayback) ) 
    {   
    while ( p.y <= 7 )
    {
        if (row(p.x) && col(p.y) && fdd(p.x,p.y) && fdu(p.x,p.y) && bdd(p.x,p.y) && bdu(p.x,p.y))
	    {
		    brd[p.x][p.y]=1;

            track[p.x]=p;

            tp=p;
            
            if ( p.x  == 7 )
            {
               
                    printf("\n\nQ PLACED             - [%d][%d]\n",tp.x,tp.y); 
                    printf("Track Point recorded, SEARCH PATH- ");
                    for (b=0; b<8; b++)
                    printf("[%d,%d]",track[b].x,track[b].y);

                printf("\nI found a solution...\n");
			    save_board();
                printf("\nI Stored the board...!");
                ch=getchar();

                break;
             }
             else 
             { 
                    printf("\n\nQ PLACED             - [%d][%d]\n",tp.x,tp.y); 
                    printf("Track Point recorded, SEARCH PATH- ");
                    for (b=0; b<8; b++)
                    printf("[%d,%d]",track[b].x,track[b].y);
//                        ch=getchar();
                p.x = p.x + 1;    
                p.y = 0;

                return trace_the_board_for(p, track);
	         }	
         }//to check the Queen Condition, IF CONDITION
	     else
         {
          printf("\nQueen can not be placed at > (%d,%d)", p.x, p.y);
                
          p.y = p.y + 1;    
        
         }
    }//for a ROW while all the columns are over, WHILE FOR ROW
  
         printf("\n\nCalling BackTrack - Track Point Recorded - [%d][%d]\n-------------------------------------------------",tp.x, tp.y);
         //ch=getchar();
         np = back_track(tp, track);
         tp=ctp;    
         printf("\nSEARCH with Track Point Set {%d,%d}  Returned Next Point {%d}{%d}\n",tp.x,tp.y,np.x, np.y);

            if (np.x == tp.x && np.y == tp.y)
            {
                printf("\nCatched THE END of the TRACK ????");
                wayback = 0;                
                ch=getchar(); 
                return 1;
            }
            else  
            {    
                return trace_the_board_for(np, track);
            }
    }//for all the ROWS are finished       
return (0);
}//trace the board is defined.


struct point back_track(struct  point tp, struct point track[])
{
    struct point btp;
    int b;

        if(tp.y < 7)
        {
                printf("\n<IN CONDITION 1>\n---- Track Record ---- IN BACKTRACK\n"); 
                for (b=0; b<8; b++)
                printf("[%d,%d]",track[b].x,track[b].y);
        printf("\nCondition - 1 for track point   [%d][%d]\t because y (%d < 7) +", tp.x, tp.y, tp.y);
        //ch=getchar();
            
        brd[tp.x][tp.y] = 0;
        track[tp.x].x = 0;
        track[tp.x].y = 0;

        btp = tp;
        ctp = track[tp.x-1];
        
                printf("\n@ Track Point Changed @ [%d][%d]\n",ctp.x, ctp.y);
  
        btp.y = btp.y + 1;

                printf("\n---- Track Record ---- CORRECTED\n"); 
                for (b=0; b<8; b++)
                printf("[%d,%d]",track[b].x,track[b].y);
        printf("\n\n--------------------------------------------------------------");
        printf("\nBackTrack <Condition 1 - Next Search Point> RETURNED  - [%d][%d]\n",btp.x, btp.y);
        return btp;
        }
        else if (tp.y == 7 && tp.x != 0) 
        {
                printf("\n<IN CONDITION 2>\n---- Track Record ---- In BackTrack\n"); 
                for (b=0; b<8; b++)
                printf("[%d,%d]",track[b].x,track[b].y);
        printf("\n\nCondition - 2 for track point [%d][%d]\t because (y == %d) ++",tp.x, tp.y, tp.y);
     //   ch=getchar();
     //   temp1 = tp;
     //   temp2.x = track[tp.x-1].x
     //   temp2.y = track[tp.x-1].y
 
        brd[tp.x][tp.y] = 0;    //current track point queen on board removed, is set zero
           
        btp = track[tp.x-1];    //now we have the backtrack point, i.e. copied from track record
        
        brd[btp.x][btp.y] = 0;  //preceding point of the track point on the board removeing

        track[tp.x-1].x = 0;    //setting the track record   
        track[tp.x-1].y = 0;    //track point on track record, is set zero    
        track[tp.x].x = 0;      //receding point on track record, is set zero       
        track[tp.x].y = 0;      //track record updated, i.e. removed last 2 queens

        ctp = track[tp.x-2];     //setting new trackpoint
                printf("\n@ Track Point Changed @ [%d][%d]\n",tp.x, tp.y);
        btp.y = btp.y + 1;
       
        printf("\n--------------------------------------------------------------");
        printf("\nBackTrack <Condition 1 - Next Search Point> RETURNED  - [%d][%d]\n",btp.x, btp.y);
        return btp;
        }
        else if ((tp.y == 7) && (tp.x == 0))
        {
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^ Back Track almost DONE ^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^ Back Track almost DONE ^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^ Back Track almost DONE ^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        ch=getchar();
        btp=tp;
        ctp=tp;
        return btp;
        }
}//backtrack




//fn to save the board
void save_board()
{
	total = total + 1;
    printf("\nTotal Solutions Found - %d", total);
}


//check the board row
int row(int n)
{
	int i;

	for(i=0; i<8; i++)
	{
		if (brd[n][i] == 1)
		return 0;
	}
return 1;
}	

//check the board column
int col(int m)
{
	int i;

	for(i=0; i<8; i++)
	{
		if (brd[i][m] == 1)
		return 0;
	}
return 1;
}	

//forward diagonal down path
int fdd(int n, int m)
{
	while ((n < 8) && (m >= 0))
	{	
		
		if (brd[n][m] == 1)
		return 0;
		else
		{
		n=n+1;
		m=m-1;
		}
	}
return 1;}	   

//forward diagonal up path
int fdu(int n, int m)
{
	while ((n >= 0) && (m < 8))
	{	
		
		if (brd[n][m] == 1)
		return 0;
		else
		{
		n=n-1;
		m=m+1;
		}
	}
return 1;
}

// backward diagonal down path
int bdd(int n, int m)
{
	while ((n < 8) && (m < 8))
	{	
		
		if (brd[n][m] == 1)
		return 0;
		else
		{

		n=n+1;
		m=m+1;
		}
	}
return 1;
}	   

// backward diagonal up path
int bdu(int n, int m)
{
	while ((n >= 0) && (m >= 0))
	{	
		
		if (brd[n][m] == 1)
		return 0;
		else
		{
		n=n-1;
		m=m-1;
		}
	}
return 1;
}	   


void init_board(int n, int m, struct point pathinit[])
{
	int i,j;

	for (i=0; i<8; i++)
	{
    pathinit[i].x=0;
    pathinit[i].y=0;
    for (j=0; j<8; j++)
	brd[i][j]=0;
    }
}

void print_board()
{
	int i,j;
	printf("In Print\n");
	
	for (i=0; i<8; i++)
	{
		printf ("\n");
	for (j=0; j<8; j++){
	printf(" %d",brd[i][j]);
	}
	}
}

