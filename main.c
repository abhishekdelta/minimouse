#include<avr/io.h>
#include<stdlib.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>

#include "definitions.h"
#include "minimouse.h"
#include "motordriver.h"
#include "motordriver.c"


int curx,cury,cell,curdir;


int moveBot(int dir)
{
   

    switch(dir)
    {
               case UP:       if(curdir==LEFT)
                               turnRight();
                              else if(curdir==DOWN)
                               turnBack();
                              else if(curdir==RIGHT)
                               turnLeft();
                              break;
               case LEFT:     if(curdir==UP)
                               turnLeft();
                              else if(curdir==DOWN)
                               turnRight();
                              else if(curdir==RIGHT)
                               turnBack();
                              break;
               case DOWN:     if(curdir==UP)
                               turnBack();
                              else if(curdir==LEFT)
                               turnLeft();
                              else if(curdir==RIGHT)
                               turnRight();
                              break;
               case RIGHT:    if(curdir==UP)
                               turnRight();
                              else if(curdir==DOWN)
                               turnLeft();
                              else if(curdir==LEFT)
                               turnBack();
                              break;
    }
    return moveFront();
   
}

int tryToMove(int map[MAXY+1][MAXX+1],int dir)
{
   

    switch(dir)
    {
                  case UP:   if(curx<0 || curx>MAXX || cury<1 || cury>MAXY)
                              return INVALID;
                             if(map[cury-1][curx]>0)
                              return PRESET;
                             if(map[cury-1][curx]==-1)
                              return BLOCK;
                             if(map[cury-1][curx]==0)
                             {
                              return moveBot(UP);
                             }
                             
                  case LEFT: if(curx<1 || curx>MAXX || cury<0 || cury>MAXY)
                              return INVALID;
                             if(map[cury][curx-1]==-1)
                              return BLOCK;
                             if(map[cury][curx-1]>0)
                              return PRESET;
                             if(map[cury][curx-1]==0)
                             {
                               return moveBot(LEFT);
                             }
                             
                            
                  case DOWN: if(curx<0 || curx>MAXX || cury<0 || cury>MAXY-1)
                              return INVALID;
                             if(map[cury+1][curx]>0)
                              return PRESET;
                             if(map[cury+1][curx]==-1)
                              return BLOCK; 
                             if(map[cury+1][curx]==0)
                             {
                               return moveBot(DOWN);
                             }
                             
                             
                  case RIGHT:if(curx<0 || curx>MAXX-1 || cury<0 || cury>MAXY)
                              return INVALID;
                             if(map[cury][curx+1]>0)
                              return PRESET;
                             if(map[cury+1][curx]==-1)
                              return BLOCK; 
                             if(map[cury][curx+1]==0)
                             {
                              return moveBot(RIGHT);
                             }
                             
                            
    }
   
}
                              
                    
void goAgain(int map[MAXY+1][MAXX+1])
{
     while(!(curx==DESTX && cury==DESTY))
     {
           int max=0,dirpath;
           int path=0x00;

                    if(cury>=1)
                     if(map[cury-1][curx]>0)
                      sbi(path,UP);
                      
                    if(curx>=1)
                     if(map[cury][curx-1]>0)
                      sbi(path,LEFT);
                      
                    if(cury<MAXY)
                     if(map[cury+1][curx]>0)
                      sbi(path,DOWN);
                      
                    if(curx<MAXX)
                     if(map[cury][curx+1]>0)
                      sbi(path,RIGHT);

                      if((path&1<<UP)!=0)
                       {
                                          if(max<map[cury-1][curx])
                                          {
                                           max=map[cury-1][curx];
                                           dirpath=UP;
                                          }
                       }
                       if((path&1<<LEFT)!=0)
                       {
                                          if(max<map[cury][curx-1])
                                          {
                                           max=map[cury][curx-1];
                                           dirpath=LEFT;
                                          }
                       }
                       if((path&1<<DOWN)!=0)
                       {
                                          if(max<map[cury+1][curx])
                                          {
                                           max=map[cury+1][curx];
                                           dirpath=DOWN;
                                          }
                       }
                       if((path&1<<RIGHT)!=0)
                       {
                                          if(max<map[cury][curx+1])
                                          {
                                           max=map[cury][curx+1];
                                           dirpath=RIGHT;
                                          }
                       }
                      

                        if(dirpath==UP)
                        {
                                   moveBot(UP);
                                   cury--;
                        }
                        if(dirpath==LEFT)
                        {
                                   moveBot(LEFT);
                                   curx--;
                        }
                        if(dirpath==DOWN)
                        {
                                   moveBot(DOWN);
                                   cury++;
                        }if(dirpath==RIGHT)
                        {
                                   moveBot(RIGHT);
                                   curx++;
                                   
                        }
                        continue;

     }
}            
void comeBack(int map[MAXY+1][MAXX+1])
{
     while(!(curx==STARTX && cury==STARTY))
     {
           int min=255,dirpath;
                   
                      
                    int path=0x00;
                    if(cury>=1)
                     if(map[cury-1][curx]>0)
                      sbi(path,UP);
                      
                    if(curx>=1)
                     if(map[cury][curx-1]>0)
                      sbi(path,LEFT);
                      
                    if(cury<MAXY)
                     if(map[cury+1][curx]>0)
                      sbi(path,DOWN);
                      
                    if(curx<MAXX)
                     if(map[cury][curx+1]>0)
                      sbi(path,RIGHT);
     
                       if((path&1<<UP)!=0)
                       {
                                          if(min>map[cury-1][curx])
                                          {
                                           min=map[cury-1][curx];
                                           dirpath=UP;
                                          }
                       }
                       if((path&1<<LEFT)!=0)
                       {
                                          if(min>map[cury][curx-1])
                                          {
                                           min=map[cury][curx-1];
                                           dirpath=LEFT;
                                          }

                       }
                       if((path&1<<DOWN)!=0)
                       {
                                          if(min>map[cury+1][curx])
                                          {
                                           min=map[cury+1][curx];
                                           dirpath=DOWN;
                                          }
                       }
                       if((path&1<<RIGHT)!=0)
                       {
                                          if(min>map[cury][curx+1])
                                          {
                                           min=map[cury][curx+1];
                                           dirpath=RIGHT;
                                          }
                       }
                      

                        if(dirpath==UP)
                        {
                                   moveBot(UP);
                                
                                   cury--;
                        }
                        if(dirpath==LEFT)
                        {
                                   moveBot(LEFT);
                                   curx--;
                                  
                        }
                        if(dirpath==DOWN)
                        {
                                   moveBot(DOWN);
                                 
                                   cury++;
                        }if(dirpath==RIGHT)
                        {
                                   moveBot(RIGHT);
                                   curx++;
                                  
                        }
                        continue;

     }
}          
       
void startBot(int map[MAXY+1][MAXX+1])
{
     int path;
     int res;
    
     while(!(curx==DESTX && cury==DESTY))
     {
                    
                         path=0x0F;
                         res=tryToMove(map,UP);
                         
                         if(res==OK)
                         {
                         
                          if(map[cury-1][curx]==0)
                            map[--cury][curx]=++cell;
                          continue;
                         }
                         if(res==BLOCK)
                         {
                          map[cury-1][curx]=-1;
                          cbi(path,UP);   
                         }
                         else if(res==INVALID)
                         {
                          cbi(path,UP);
                         }
                    
                         res=tryToMove(map,LEFT);
                        
                         if(res==OK)
                         {
                          if(map[cury][curx-1]==0);
                           map[cury][--curx]=++cell;
                          continue;
                         }
                         if(res==BLOCK)
                         {
                          map[cury][curx-1]=-1;
                          cbi(path,LEFT);
                         }
                         else if(res==INVALID)
                         {
                          cbi(path,LEFT);
                         }
                       
                         res=tryToMove(map,DOWN);
                         if(res==OK)
                         {
                          if(map[cury+1][curx]==0)
                           map[++cury][curx]=++cell;
                          continue;
                         }
                         if(res==BLOCK)
                         {
                          map[cury+1][curx]=-1;
                          cbi(path,DOWN);
                         }
                         else if(res==INVALID)
                         {
                          cbi(path,DOWN);
                         }
                       
                         res=tryToMove(map,RIGHT);
                         if(res==OK)
                         {
                          if( map[cury][curx+1]==0)
                           map[cury][++curx]=++cell;
                          continue;
                         }
                         if(res==BLOCK)
                         {
                          map[cury][curx+1]=-1;
                          cbi(path,RIGHT);
                         }
                         if(res==INVALID)
                         {
                          cbi(path,RIGHT);
                         }
                      
                       int min=255,dirpath;
                       
                       if((path&1<<UP)!=0)
                       {
                                          if(min>map[cury-1][curx])
                                          {
                                           min=map[cury-1][curx];
                                           dirpath=UP;
                                          }
                       }
                       if((path&1<<LEFT)!=0)
                       {
                                          if(min>map[cury][curx-1])
                                          {
                                           min=map[cury][curx-1];
                                           dirpath=LEFT;
                                          }
                       }
                       if((path&1<<DOWN)!=0)
                       {
                                          if(min>map[cury+1][curx])
                                          {
                                           min=map[cury+1][curx];
                                           dirpath=DOWN;
                                          }
                       }
                       if((path&1<<RIGHT)!=0)
                       {
                                          if(min>map[cury][curx+1])
                                          {
                                           min=map[cury][curx+1];
                                           dirpath=RIGHT;
                                          }
                       }
                      

                        if(dirpath==UP)
                        {
                                 
                                   moveBot(UP);
                                
                                   cury--;
                        }
                        if(dirpath==LEFT)
                        {   
                                   moveBot(LEFT);
                                   curx--;
                               
                        }
                        if(dirpath==DOWN)
                        {   
                                   moveBot(DOWN);
                                 
                                   cury++;
                        }if(dirpath==RIGHT)
                        {   
                                   moveBot(RIGHT);
                                   curx++;
                                   
                        }
                    
                        continue;
     }
}
          
int main()
{
    int map[MAXY+1][MAXX+1];
	for(int i=0;i<MAXY+1;i++)
	{
		for(int j=0;j<MAXX+1;j++)
		{
			map[i][j]=0;
		}
	}
    curx=STARTX;
    cury=STARTY;
    curdir=UP;
    cell=1;
    map[curx][cury]=1;
    startBot(map);
    comeBack(map);
    goAgain(map);
    return 0;
    
}
