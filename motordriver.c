void delay(int ms)
{
     for(int i=0;i<ms;i++)
             _delay_ms(1);
}
int getLED(int i)
{
     switch(i)
     {
             
              case 1 : return ((INPWORD&(1<<LED1))>1)?1:0;
              case 2 : return ((INPWORD&(1<<LED2))>1)?1:0;
              case 3 : return ((INPWORD&(1<<LED3))>1)?1:0;
              case 4 : return ((INPWORD&(1<<LED4))>1)?1:0;
              case 5 : return ((INPWORD&(1<<LED5))>1)?1:0;
     }         
}
int botAtNode()
{
    if(getLED(1)&&getLED(2)&&getLED(3)&&getLED(4))
     return 1;
    return 0;
}
int botBlocked()
{
    return getLED(5);
}
void motorStop(int i)
{
      switch(i)
      {
              case 1 : 
                       cbi(OUTWORD,MOTOR1P);
                       cbi(OUTWORD,MOTOR1N);
                       break;
              case 2 : 
                       cbi(OUTWORD,MOTOR2P);
                       cbi(OUTWORD,MOTOR2N);
                       break;
      }
}    
void motorForward(int i)
{
     
     switch(i)
     {
              case 1 : 
                       sbi(OUTWORD,MOTOR1P);
                       cbi(OUTWORD,MOTOR1N);
                       break;
              case 2 : 
                       sbi(OUTWORD,MOTOR2P);
                       cbi(OUTWORD,MOTOR2N);
                       break;
     }
}    
void motorReverse(int i)
{
     switch(i)
     {
              case 1 : 
                       cbi(OUTWORD,MOTOR1P);
                       sbi(OUTWORD,MOTOR1N);
                       break;
              case 2 : 
                       cbi(OUTWORD,MOTOR2P);
                       sbi(OUTWORD,MOTOR2N);
                       break;
     }
}
int moveFront()
{

    motorForward(1);
    motorForward(2);
    //delay(ms);
    while(1)
    {
            if(botAtNode())
            {
                           motorStop(1);
                           motorStop(2);
                           return OK;
            }
            if(botBlocked())
            {
                            motorStop(1);
                            motorStop(2);
                            motorReverse(1);
                            motorReverse(2);
                            //delay(ms);
                            while(1)
                            {
                                    if(botAtNode())
                                    {
                                                   motorStop(1);
                                                   motorStop(2);
                                                   return BLOCK;
                                    }
                            }
            }
    }
}
void turnLeft()
{
     motorReverse(1);
     motorForward(2);
     //delay(ms);
     while(1)
     {
             if(botAtNode())
             {
                            motorStop(1);
                            motorStop(2);
                            return;
             }
     }
}
void turnRight()
{
     motorReverse(2);
     motorForward(1);
     //delay(ms);
     while(1)
     {
             if(botAtNode())
             {
                            motorStop(1);
                            motorStop(2);
                            return;
             }
     }
}
void turnBack()
{
     turnLeft();
     turnRight();
}

             
                             
     
                                    
                            
    
