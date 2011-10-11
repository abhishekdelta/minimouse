#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
#define INICOL  0
#define TARCOL  1
#define MAXX    4
#define MAXY    4
#define STARTX  4
#define STARTY  4
#define DESTX   0
#define DESTY   0


#define WEST(x,y)   (x)-1,(y)
#define NORTH(x,y)  (x),(y)+1
#define EAST(x,y)   (x)+1,(y)
#define SOUTH(x,y)  (x),(y)-1
void showMap(int map[MAXY+1][MAXX+1],int x,int y,int flag=0)
{
     cout<<"\n";
     for(int i=0;i<MAXY+1;i++)
     {
             for(int j=0;j<MAXX+1;j++)
             {
                     if(i==STARTY && j==STARTX && flag)
                      cout<<"S"<<"\t";
                     else if(i==DESTY && j==DESTX && flag)
                      cout<<"D"<<"\t";
                     else if(i==y && j==x && !flag)
                      cout<<"X"<<"\t";
                     else
                      cout<<map[i][j]<<"\t";
             }
             cout<<"\n";
     }
}
void floodfill(int map[MAXY+1][MAXX+1],int x,int y)
{
 if(!(x<0 || x>MAXX || y<0 || y>MAXY))
 {
        if(map[y][x]!=INICOL)
         return;
        map[y][x]=TARCOL;
        if(x==DESTX && y==DESTY)
        {
                    
                    cout<<"\nreached! Map is :";
                    showMap(map,x,y);
                 
                    exit(1);
        }
        
        showMap(map,x,y);
       
        floodfill(map,WEST(x,y));
        floodfill(map,NORTH(x,y));
        floodfill(map,EAST(x,y));
        floodfill(map,SOUTH(x,y));
 }
 return;
}

int main()
{
    int map[MAXY+1][MAXX+1]={
         0,0,0,0,0,
         0,2,0,0,2,
         2,0,2,0,0,
         0,0,0,2,0,
         0,0,0,0,0
         };
    cout<<"X -> Current Mouse Position\n1 -> Path Travelled\n2 -> Block\n0 -> Path Not Travelled Yet";
    cout<<"MAP INIT:";
    showMap(map,0,0,1);
    cout<<"\nALGO START : ";
    floodfill(map,STARTX,STARTY);
    cout<<"MAP AFTER FLOODFILL:";
    showMap(map,DESTX,DESTY,1);    
}
