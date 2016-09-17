#include<windows.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<iostream>
using namespace std;

enum Direction {UP,DOWN,LEFT,RIGHT};

void gotoRowCol(int rpos, int cpos)
{
    int xpos=cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

void Sleep(double m)
{
    for(int i=0; i<999999*m; i++)
    {

    }
}

void L2R(int Row,int Col_Start,int Col_End,char sym)
{
    for(int Init_Col=Col_Start; Init_Col<Col_End; Init_Col++)
    {
        gotoRowCol(Row, Init_Col);
        cout<<sym;
    }
}

void T2B(int Column,int Row_Start,int Row_End,char sym)
{
    for(int Init_Row=Row_Start; Init_Row<Row_End; Init_Row++)
    {
        gotoRowCol(Init_Row, Column);
        cout<<sym;
    }
}

void R2L(int Row,int Col_Start,int Col_End,char sym)
{
    for(int Init_Col=Col_Start; Init_Col>Col_End; Init_Col--)
    {
        gotoRowCol(Row, Init_Col);
        cout<<sym;
    }
}

void B2T(int Column,int Row_Start,int Row_End,char sym)
{
    for(int Init_Row=Row_Start; Init_Row>Row_End; Init_Row--)
    {
        gotoRowCol(Init_Row, Column);
        cout<<sym;
    }
}

void initsnake(int SP[100][2],int SS,int row,int column)
{
    SP[0][0]=row/2;
    SP[0][1]=(column-5)/2;
    SP[1][0]=row/2+1;
    SP[1][1]=(column-5)/2;
    SP[2][0]=row/2+2;
    SP[2][1]=(column-5)/2;
}

void init2ndsnake(int SP[100][2],int SS,int row,int column)
{
    SP[0][0]=row/2;
    SP[0][1]=(column+5)/2;
    SP[1][0]=row/2+1;
    SP[1][1]=(column+5)/2;
    SP[2][0]=row/2+2;
    SP[2][1]=(column+5)/2;
}

void printsnake(int SP[100][2],int SS,char S)
{
    for(int s=0; s<SS; s++)
    {
        gotoRowCol(SP[s][0],SP[s][1]);
        cout<<S;
    }
}

void shifting(int SP[100][2],int SS)
{
    for(int s=SS-1; s>0; s--)
    {
        SP[s][0]=SP[s-1][0];
        SP[s][1]=SP[s-1][1];
    }
}

void Movesnake(int SP[100][2],int SS,Direction D,int row,int column)
{
    shifting(SP,SS);

    switch(D)
    {
    case UP:
        SP[0][0]--;
        if(SP[0][0]==0)
            SP[0][0]= row-1;
        break;
    case DOWN:
        SP[0][0]++;
        if(SP[0][0]==row)
            SP[0][0]=1;
        break;
    case LEFT:
        SP[0][1]--;
        if(SP[0][1]==0)
            SP[0][1]= column-1;
        break;
    case RIGHT:
        SP[0][1]++;
        if(SP[0][1]==column)
            SP[0][1]=1;
        break;
    }
}

void FoodGeneration(int SP[100][2],int SS,int FC[1][2],char S,bool &FE,
                    int row,int column)
{
    bool check;
    int rr,rc;

    do
    {
        check=true;
        rr=rand()%row;
        rc=rand()%column;

        for(int s=0; s<SS; s++)
        {
            if(((SP[s][0]==rr)&& (SP[s][1]==rc))||(rr==0||rr==row)||(rc==0||rc==column))
            {
                check=false;
            }
        }
    }
    while(check==false);
    FC[0][0]=rr;
    FC[0][1]=rc;

    FE=false;

    gotoRowCol(rr,rc);
    cout<<S;
}

void PrintScore(int score1,int score2,int column)
{
    gotoRowCol(4,column+5);
    cout<<"*ScoreBoard*";
    gotoRowCol(7,column+5);
    cout<<"Player1:"<<score1;
    gotoRowCol(10,column+5);
    cout<<"Player2:"<<score2;
}

void Instruction()
{
    cout<< "Player_1 controls: Arrow keys"
        << "\nPlayer_2 controls: w a s d"
        << "\nPlease Turn off Capslock."
        << "\nNow Press Any Key to start";
        getch();
        system("cls");
}

int main()
{
    srand(time(0));
    system("mode 300,300");
    int R=0;
    int column=80;
    int rows=80;
    int SS=3,SS2=3;
    int sp[100][2];
    int sp2[100][2];
    int Fc[1][2];
    bool Fe=true,GE=false;
    char S= -37;
    Direction D=UP,D2=UP;
    int count1=0;
    int count2=0;
    Instruction();
    L2R(R,R, column, S);
    T2B(column, R, rows, S);
    R2L(rows, column, R, S);
    B2T(R, rows, R, S);

    initsnake(sp,SS,rows,column);
    init2ndsnake(sp2,SS2,rows,column);
    do
    {
        PrintScore(count1,count2,column);
        if(Fe)
        {
            FoodGeneration(sp,SS,Fc,'*',Fe,rows,column);
        }
        printsnake(sp,SS,S);
        printsnake(sp2,SS2,-80);
        if(kbhit())
        {
            int Z=getch();
            if(Z==224)
            {
                switch(getch())
                {
                case 72: //^
                    if(D!=DOWN)
                        D=UP;
                    break;
                case 80: //v
                    if(D!=UP)
                        D=DOWN;
                    break;
                case 75: //<
                    if(D!=RIGHT)
                        D=LEFT;
                    break;
                case 77: //>
                    if(D!=LEFT)
                        D=RIGHT;
                    break;
                }
            }
            else
                switch(Z)
                {
                case 119: //^
                    if(D2!=DOWN)
                        D2=UP;
                    break;
                case 115: //v
                    if(D2!=UP)
                        D2=DOWN;
                    break;
                case 97: //<
                    if(D2!=RIGHT)
                        D2=LEFT;
                    break;
                case 100: //>
                    if(D2!=LEFT)
                        D2=RIGHT;
                    break;
                }
        }
        Sleep(10.0);
        printsnake(sp,SS,' ');
        printsnake(sp2,SS2,' ');
        Movesnake(sp,SS,D,rows,column);
        Movesnake(sp2,SS2,D2,rows,column);
        if((sp[0][0]==Fc[0][0])&&(sp[0][1]==Fc[0][1]))
        {
            Fe=true;
            SS=SS+1;
            count1++;
        }
        if((sp2[0][0]==Fc[0][0])&&(sp2[0][1]==Fc[0][1]))
        {
            Fe=true;
            SS2=SS2+1;
            count2++;
        }
        for(int x=1; x<SS; x++)
        {
            if((sp[0][0]==sp[x][0])&&sp[0][1]==sp[x][1])
            {
                count1-=1;
            }
        }
        for(int x=1; x<SS2; x++)
        {
            if((sp2[0][0]==sp2[x][0])&&sp2[0][1]==sp2[x][1])
            {
                count2-=1;
            }
        }
        for(int i=1; i<SS2; i++)
        {
            if((sp[0][0]==sp2[i][0])&&sp[0][1]==sp2[i][1])
            {
                if(count1>0)
                {
                    count1=count1-1;
                    break;
                }
            }
        }
        for(int i=1; i<SS; i++)
        {
            if((sp2[0][0]==sp[i][0])&&sp2[0][1]==sp[i][1])
            {
                if(count2>0)
                {
                    count2=count2-1;
                    break;
                }
            }
        }
        if(count1==15 || count2==15)
            GE=true;
    }
    while(GE==false);
    PrintScore(count1,count2,column);
    if(count1==15)
    {
        system("cls");
        cout<< "Player 1 Wins!!!";
    }
    else if(count2==15)
    {
        system("cls");
        cout<< "Player 2 Wins!!!";
    }
    getch();
    return 0;
}
