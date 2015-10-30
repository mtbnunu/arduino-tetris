/*
Author: Jae Yeong Bae
        UBC ECE
        jocker.tistory.com       
Date:   Jan.18.2013
File:   Tetris v2
Changelog:
        v2: displays score at gameover
        
Purpose:
        killing time.. + for fun
          
Circuits+Pins:
        Led Matrix:
        2 74HC575 Shift Registers in order: Green,Blue,Red
        pins: Latch = 3
              Clock = 2
              Data = 4
              Row Anodes = 5 to 13 (8pins) shared between both matrix
        buttons (as digital):
          A4 = left
          A5 = down
          A6 = right
          A7 = up (rotate)

Comment:
        This is my second Arduino Project. 
        Code may be messy and inefficient.
        References from Arduino Library and datasheets.
*/




unsigned char latchPin = 3;
unsigned char clockPin = 2;
unsigned char dataPin = 4;
unsigned char rowPin = 5;


long delays = 0;
short delay_ = 500;
long bdelay = 0;
short buttondelay = 150;
short btdowndelay = 30;
short btsidedelay = 80;
unsigned char blocktype;
unsigned char blockrotation;

int lines = 0;
boolean  block[8][18]; //2 extra for rotation
boolean  pile[8][16];
boolean disp[8][16];

boolean lib[10][5][7];




void setup() {

lib[0][1][0] = 1;
lib[0][2][0] = 1;
lib[0][3][0] = 1;
lib[0][0][1] = 1;
lib[0][4][1] = 1;
lib[0][3][2] = 1;
lib[0][0][2] = 1;
lib[0][4][2] = 1;
lib[0][2][3] = 1;
lib[0][0][3] = 1;
lib[0][4][3] = 1;
lib[0][1][4] = 1;
lib[0][0][4] = 1;
lib[0][4][4] = 1;
lib[0][0][5] = 1;
lib[0][4][5] = 1;
lib[0][1][6] = 1;
lib[0][2][6] = 1;
lib[0][3][6] = 1;
lib[1][2][0] = 1;
lib[1][1][1] = 1;
lib[1][2][1] = 1;
lib[1][2][2] = 1;
lib[1][2][3] = 1;
lib[1][2][4] = 1;
lib[1][2][5] = 1;
lib[1][1][6] = 1;
lib[1][2][6] = 1;
lib[1][3][6] = 1;
lib[2][1][0] = 1;
lib[2][2][0] = 1;
lib[2][3][0] = 1;
lib[2][0][1] = 1;
lib[2][4][1] = 1;
lib[2][4][2] = 1;
lib[2][3][3] = 1;
lib[2][2][4] = 1;
lib[2][1][5] = 1;
lib[2][0][6] = 1;
lib[2][1][6] = 1;
lib[2][2][6] = 1;
lib[2][3][6] = 1;
lib[2][4][6] = 1;
lib[3][0][0] = 1;
lib[3][1][0] = 1;
lib[3][2][0] = 1;
lib[3][3][0] = 1;
lib[3][4][0] = 1;
lib[3][3][1] = 1;
lib[3][2][2] = 1;
lib[3][3][3] = 1;
lib[3][4][4] = 1;
lib[3][0][5] = 1;
lib[3][4][5] = 1;
lib[3][1][6] = 1;
lib[3][2][6] = 1;
lib[3][3][6] = 1;
lib[4][3][0] = 1;
lib[4][2][1] = 1;
lib[4][3][1] = 1;
lib[4][1][2] = 1;
lib[4][3][2] = 1;
lib[4][0][3] = 1;
lib[4][3][3] = 1;
lib[4][0][4] = 1;
lib[4][1][4] = 1;
lib[4][2][4] = 1;
lib[4][3][4] = 1;
lib[4][4][4] = 1;
lib[4][3][5] = 1;
lib[4][3][6] = 1;
lib[5][0][0] = 1;
lib[5][1][0] = 1;
lib[5][2][0] = 1;
lib[5][3][0] = 1;
lib[5][4][0] = 1;
lib[5][0][1] = 1;
lib[5][0][2] = 1;
lib[5][1][2] = 1;
lib[5][2][2] = 1;
lib[5][3][2] = 1;
lib[5][4][3] = 1;
lib[5][4][4] = 1;
lib[5][0][5] = 1;
lib[5][4][5] = 1;
lib[5][1][6] = 1;
lib[5][2][6] = 1;
lib[5][3][6] = 1;
lib[6][2][0] = 1;
lib[6][3][0] = 1;
lib[6][1][1] = 1;
lib[6][0][2] = 1;
lib[6][0][3] = 1;
lib[6][1][3] = 1;
lib[6][2][3] = 1;
lib[6][3][3] = 1;
lib[6][0][4] = 1;
lib[6][4][4] = 1;
lib[6][0][5] = 1;
lib[6][4][5] = 1;
lib[6][1][6] = 1;
lib[6][2][6] = 1;
lib[6][3][6] = 1;
lib[7][0][0] = 1;
lib[7][1][0] = 1;
lib[7][2][0] = 1;
lib[7][3][0] = 1;
lib[7][4][0] = 1;
lib[7][4][1] = 1;
lib[7][3][2] = 1;
lib[7][2][3] = 1;
lib[7][1][4] = 1;
lib[7][1][5] = 1;
lib[7][1][6] = 1;
lib[8][1][0] = 1;
lib[8][2][0] = 1;
lib[8][3][0] = 1;
lib[8][0][1] = 1;
lib[8][4][1] = 1;
lib[8][0][2] = 1;
lib[8][4][2] = 1;
lib[8][1][3] = 1;
lib[8][2][3] = 1;
lib[8][3][3] = 1;
lib[8][0][4] = 1;
lib[8][4][4] = 1;
lib[8][0][5] = 1;
lib[8][4][5] = 1;
lib[8][1][6] = 1;
lib[8][2][6] = 1;
lib[8][3][6] = 1;
lib[9][1][0] = 1;
lib[9][2][0] = 1;
lib[9][3][0] = 1;
lib[9][0][1] = 1;
lib[9][4][1] = 1;
lib[9][0][2] = 1;
lib[9][4][2] = 1;
lib[9][1][3] = 1;
lib[9][2][3] = 1;
lib[9][3][3] = 1;
lib[9][4][3] = 1;
lib[9][4][4] = 1;
lib[9][3][5] = 1;
lib[9][1][6] = 1;
lib[9][2][6] = 1;

  int seed = 
  (analogRead(0)+1)*
  (analogRead(1)+1)*
  (analogRead(2)+1)*
  (analogRead(3)+1);
  randomSeed(seed);
  random(10,9610806);
  seed = seed *random(3336,15679912)+analogRead(random(4)) ;
  randomSeed(seed);  
  random(10,98046);

  
  cli();//stop interrupts

//set timer0 interrupt at 2kHz
  TCCR1A = 0;// set entire TCCR0A register to 0
  TCCR1B = 0;// same for TCCR0B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR1A = 259;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR1A |= (1 << WGM01);
  // Set CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);   
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE0A);

  sei();//allow interrupts  
  
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(A7, INPUT); //up
  pinMode(A6, INPUT); //right
  pinMode(A5, INPUT); //left
  pinMode(A4, INPUT); //down 
  
  int i;
  for(i=0;i<8;i++)
    pinMode(rowPin+i,OUTPUT);
  
  newBlock();
  updateLED();    

  Serial.begin(9600);
}

void loop() {
  
  if (delays < millis())
   {
     delays = millis() + delay_;
     movedown();
   }
   
   

   //buttun actions
  int button = readBut();
  
  if (button == 1) //up=rotate
    rotate();
  if (button == 2) //right=moveright
    moveright();    
  if (button == 3) //left=moveleft
    moveleft();
  if (button == 4) //down=movedown
    movedown();  
  
  
  Serial.print(analogRead(A4));
  Serial.print(analogRead(A5));
  Serial.print(analogRead(A6));  
  Serial.println(analogRead(A7));
   

}

boolean moveleft()
{  
  if (space_left())
  {
    int i;
    int j;
    for (i=0;i<7;i++)
    {
      for (j=0;j<16;j++)      
      {
        block[i][j]=block[i+1][j];
      }
    }
    
    for (j=0;j<16;j++)      
    {
      block[7][j]=0;
    }    

    updateLED();
    return 1;
  }

  return 0;
}

boolean moveright()
{
  if (space_right())
  {
    int i;
    int j;
    for (i=7;i>0;i--)
    {
      for (j=0;j<16;j++)      
      {
        block[i][j]=block[i-1][j];
      }
    }

    for (j=0;j<16;j++)      
    {
      block[0][j]=0;
    }    
    
   updateLED(); 
   return 1;   
  
  }
  return 0;
}

int readBut()
{
  if (bdelay > millis())
  {
    return 0;
  }
  if (analogRead(A4) > 500)
  {
    //left
    bdelay = millis() + btsidedelay;    
    return 3;
  }
  
  if (analogRead(A5) > 500)
  {
    //down
    bdelay = millis() + btdowndelay;    
    return 4;
  }    
  if (analogRead(A6) > 500)
  {
    //right
    bdelay = millis() + btsidedelay;
    return 2;
  }  
  if (analogRead(A7) > 500)
  {
    //up
    bdelay = millis() + buttondelay;
    return 1;
  }  
  
  return 0;
}

void updateLED()
{
  int i;
  int j;  
  for (i=0;i<8;i++)
  {
    for (j=0;j<16;j++)
    {
      disp[i][j] = block[i][j] | pile[i][j];
    }
  }
}

void rotate()
{
  
  //skip for square block(3)
  if (blocktype == 3) return;
  
  int xi;
  int yi;
  int i;
  int j;
  //detect left
  for (i=7;i>=0;i--)
  {
    for (j=0;j<16;j++)
    {
      if (block[i][j])
      {
        xi = i;
      }
    }
  }
  
  //detect up
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
      if (block[j][i])
      {
        yi = i;
      }
    }
  }  
    
  if (blocktype == 0)
  {
    if (blockrotation == 0) 
    {
      
      
      if (!space_left())
      {
        if (space_right3())
        {
          if (!moveright())
            return;
          xi++;
        }
        else return;
      }     
      else if (!space_right())
      {
        if (space_left3())
        {
          if (!moveleft())
            return;
          if (!moveleft())
            return;          
          xi--;
          xi--;        
        }
        else
          return;
      }
      else if (!space_right2())
      {
        if (space_left2())
        {
          if (!moveleft())
            return;          
          xi--;      
        }
        else
          return;
      }   
   
      
   
      
      
      block[xi][yi]=0;
      block[xi][yi+2]=0;
      block[xi][yi+3]=0;      
      
      block[xi-1][yi+1]=1;
      block[xi+1][yi+1]=1;
      block[xi+2][yi+1]=1;      

      blockrotation = 1;
    }
    else
    {
      block[xi][yi]=0;
      block[xi+2][yi]=0;
      block[xi+3][yi]=0;
      
      block[xi+1][yi-1]=1;
      block[xi+1][yi+1]=1;
      block[xi+1][yi+2]=1;

      blockrotation = 0;
    }    
  }
  
  //offset to mid
  xi ++;  
  yi ++;  
  
  if (blocktype == 1)
  {
    if (blockrotation == 0)
    {
      block[xi-1][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] = 1;
      block[xi+1][yi-1] = 1;
      block[xi][yi+1] = 1;      
      
      blockrotation = 1;
    }
    else if (blockrotation == 1)
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }        
      xi--;
      
      block[xi][yi-1] = 0;
      block[xi+1][yi-1] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      block[xi+1][yi+1] = 1;      
      
      blockrotation = 2;      
    }
    else if (blockrotation == 2)
    {
      yi --;
      
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi+1][yi+1] = 0;      
      
      block[xi][yi-1] = 1;
      block[xi][yi+1] = 1;
      block[xi-1][yi+1] = 1;      
      
      blockrotation = 3;            
    }
    else
    {
      if (!space_right())
      {
        if (!moveleft())
          return;
        xi--;
      }
      block[xi][yi-1] = 0;
      block[xi][yi+1] = 0;
      block[xi-1][yi+1] = 0;        

      block[xi-1][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      
      blockrotation = 0;          
    }  
  }



  if (blocktype == 2)
  {
    if (blockrotation == 0)
    {
      block[xi+1][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] = 1;
      block[xi+1][yi+1] = 1;
      block[xi][yi+1] = 1;      
      
      blockrotation = 1;
    }
    else if (blockrotation == 1)
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi][yi-1] = 0;
      block[xi+1][yi+1] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      block[xi-1][yi+1] = 1;      
      
      blockrotation = 2;      
    }
    else if (blockrotation == 2)
    {
      yi --;
      
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi-1][yi+1] = 0;      
      
      block[xi][yi-1] = 1;
      block[xi][yi+1] = 1;
      block[xi-1][yi-1] = 1;      
      
      blockrotation = 3;            
    }
    else
    {
      if (!space_right())
      {
        if (!moveleft())
          return;
        xi--;
      }      
      block[xi][yi-1] = 0;
      block[xi][yi+1] = 0;
      block[xi-1][yi-1] = 0;        

      block[xi+1][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      
      blockrotation = 0;          
    }  
  }
  
  if (blocktype == 4)
  {
    if (blockrotation == 0)
    {
      block[xi+1][yi-1] = 0;
      block[xi-1][yi] = 0;

      block[xi+1][yi] = 1;
      block[xi+1][yi+1] = 1;      
      
      blockrotation = 1;
    }
    else
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi+1][yi] = 0;
      block[xi+1][yi+1] = 0;      
      
      block[xi-1][yi] = 1;
      block[xi+1][yi-1] = 1;
      
      blockrotation = 0;          
    }  
  }  


  if (blocktype == 5)
  {
    if (blockrotation == 0)
    {
      block[xi][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] = 1;
      block[xi+1][yi] = 1;
      block[xi][yi+1] = 1;      
      
      blockrotation = 1;
    }
    else if (blockrotation == 1)
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi][yi-1] = 0;
      block[xi+1][yi] = 0;
      block[xi][yi+1] = 0;
      
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      block[xi][yi+1] = 1;
      
      blockrotation = 2;      
    }
    else if (blockrotation == 2)
    {
      yi --;
      
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi][yi+1] = 0;     
      
      block[xi][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi][yi+1] = 1;      
      
      blockrotation = 3;            
    }
    else
    {
      if (!space_right())
      {
        if (!moveleft())
          return;
        xi--;
      }      
      block[xi][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      
      blockrotation = 0;          
    }  
  }
  
  if (blocktype == 6)
  {
    if (blockrotation == 0)
    {
      block[xi-1][yi-1] = 0;
      block[xi][yi-1] = 0;

      block[xi+1][yi-1] = 1;
      block[xi][yi+1] = 1;      
      
      blockrotation = 1;
    }
    else
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi+1][yi-1] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi-1][yi-1] = 1;
      block[xi][yi-1] = 1;
      
      blockrotation = 0;          
    }  
  }  
  






  //if rotating made block and pile overlap, push rows up
  while (!check_overlap())
  {
    for (i=0;i<18;i++)
    {
      for (j=0;j<8;j++)
      {
         block[j][i] = block[j][i+1];
      }
    }
    delays = millis() + delay_;
  }
  
  
  updateLED();


    
}

void movedown()
{
  if (space_below())
  {
    //move down
    int i;
    for (i=15;i>=0;i--)
    {
      int j;
      for (j=0;j<8;j++)
      {
        block[j][i] = block[j][i-1];
      }
    }
    for (i=0;i<7;i++)
    {
      block[i][0] = 0;
    }
  }
  else
  {
    //merge and new block
    int i;
    int j;    
    for (i=0;i<8;i++)
    {
     for(j=0;j<16;j++)
     {
       if (block[i][j])
       {
         pile[i][j]=1;
         block[i][j]=0;
       }
     }
    }
    newBlock();   
  }
  updateLED();  
}

boolean check_overlap()
{
  int i;
  int j;  
  for (i=0;i<16;i++)
  {
    for (j=0;j<7;j++)
    {
       if (block[j][i])
       {
         if (pile[j][i])
           return false;
       }        
    }
  }
  for (i=16;i<18;i++)
  {
    for (j=0;j<7;j++)
    {
       if (block[j][i])
       {
         return false;
       }        
    }
  }  
  return true;
}

void check_gameover()
{
  int i;
  int j;
  int cnt=0;;
  
  for(i=15;i>=0;i--)
  {
    cnt=0;
    for (j=0;j<8;j++)
    {
      if (pile[j][i])
      {
        cnt ++;
      }
    }    
    if (cnt == 8)
    {
        lines++;
      for (j=0;j<8;j++)
      {
        pile[j][i]=0;
      }        
      updateLED();
      delay(50);
      
      int k;
      for(k=i;k>0;k--)
      {
        for (j=0;j<8;j++)
        {
          pile[j][k] = pile[j][k-1];
        }                
      }
      for (j=0;j<8;j++)
      {
        pile[j][0] = 0;
      }        
      updateLED();      
      delay(50);      
      i++;     
      
      
    
    }
  }  
  
  
  for(i=0;i<8;i++)
  {
    if (pile[i][0])
      gameover();
  }
  return;
}

void gameover()
{
  int i;
  int j;
  
  //close blind
  for (i=0;i<8;i++)
  {
     for (j=0;j<16;j++)
     {
       if (j%2)
       {
         disp[i][j]=1;
       }
       else
       {
         disp[7-i][j]=1;        
       }
     }
     delay(60);
  }
 
  //calculate score board
       
    int num_lines;
    num_lines = 2;
    boolean score[8][17];

        for (i=0;i<8;i++)
        {
            for (j=0;j<16;j++)
            {
                score[i][j] = 0;
            }
        }       
    
    int digit1 = (lines/10) % 10;
    int digit2 = (lines) % 10;
    
    for (i=0;i<5;i++)
        for (j=0;j<8;j++)
        {
            score[7-j][i+3]  = lib[digit1][i][j];
        }
    for (i=0;i<5;i++)
        for (j=0;j<8;j++)
        {
            score[7-j][i+9]  = lib[digit2][i][j];                
        }
        
    for (i=0;i<16;i++)
    {
        score[0][i]=0;
    }
    
    
//open blind with score    
    for (i=0;i<8;i++)
    {
     for (j=0;j<16;j++)
     {
       if (j%2)
       {
         disp[i][j]=score[i][j];
       }
       else
       {
         disp[7-i][j]=score[7-i][j];
       }
     }
     delay(60);
    }       
           
    delay(100);    
    
    while(true)
    {
        for (i=0;i<8;i++)
        {
            for (j=0;j<16;j++)
            {
                disp[i][j] = score[i][j];
            }
        }   
        
        boolean tmpline[8];
        for (i=0;i<8;i++)
        {
            score[i][16]=score[i][0];
        }
        
        for (i=0;i<8;i++)
        {
            for (j=0;j<16;j++)
            {
                score[i][j] = score[i][j+1];
            }
        }   

        
        delay(100);
    }
  
}

void newBlock()
{
  check_gameover();
  
  
  blocktype = random(7);

  
  if (blocktype == 0)
  // 0
  // 0
  // 0
  // 0
  {
    block[3][0]=1;
    block[3][1]=1;
    block[3][2]=1;
    block[3][3]=1;      
  }

  if (blocktype == 1)
  // 0
  // 0 0 0
  {
    block[2][0]=1;
    block[2][1]=1;
    block[3][1]=1;
    block[4][1]=1;        
  }
  
  if (blocktype == 2)
  //     0
  // 0 0 0
  {
    block[4][0]=1;
    block[2][1]=1;
    block[3][1]=1;
    block[4][1]=1;         
  }

  if (blocktype == 3)
  // 0 0
  // 0 0
  {
    block[3][0]=1;
    block[3][1]=1;
    block[4][0]=1;
    block[4][1]=1;          
  }    

  if (blocktype == 4)
  //   0 0
  // 0 0
  {
    block[4][0]=1;
    block[5][0]=1;
    block[3][1]=1;
    block[4][1]=1;         
  }    
  
  if (blocktype == 5)
  //   0
  // 0 0 0
  {
    block[4][0]=1;
    block[3][1]=1;
    block[4][1]=1;
    block[5][1]=1;       
  }        

  if (blocktype == 6)
  // 0 0
  //   0 0
  {
    block[3][0]=1;
    block[4][0]=1;
    block[4][1]=1;
    block[5][1]=1;         
  }    

  blockrotation = 0;
}

boolean space_below()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (i == 15)
           return false;
         if (pile[j][i+1])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_left2()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1)
           return false;
         if (pile[j-1][i] | pile[j-2][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_left3()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1 ||j == 2 )
           return false;
         if (pile[j-1][i] | pile[j-2][i]|pile[j-3][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_left()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0)
           return false;
         if (pile[j-1][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_right()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7)
           return false;
         if (pile[j+1][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_right3()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7||j == 6||j == 5)
           return false;
         if (pile[j+1][i] |pile[j+2][i] | pile[j+3][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_right2()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7 || j == 6)
           return false;
         if (pile[j+1][i] |pile[j+2][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}



ISR(TIMER1_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
    LEDRefresh();
}

void LEDRefresh()
{
    int i;
    int k;
    ////////////////////////////////////////////////
    // I soldered pins wrong. (12345670 instead of 01234567). 
    // so this portion of code is to software correct this issue.
    boolean tmpdisp[8][16];    
    for (k=0;k<16;k++)
    {
      for(i=1;i<8;i++)
      {
        tmpdisp[i][k]=disp[i-1][k];
      }
      tmpdisp[0][k]=disp[7][k];      
    }  
    //////////////////////////////////////////////
  
    for(i=0;i<8;i++)
    {      
      int j;
      
      if (i == 0) 
        j = rowPin+7;      
      else
        j = rowPin+i-1; 
             
       byte upper = 0;
       int b;
       for(b = 0;b<8;b++)
       {
         upper <<= 1;
         if (!tmpdisp[b][i]) upper |= 1;
       }
       
       
       byte lower = 0;
       for(b = 0;b<8;b++)
       {
         lower <<= 1;
         if (!tmpdisp[b][i+8]) lower |= 1;
       }

      
      digitalWrite(j,LOW);      
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, lower);      
      shiftOut(dataPin, clockPin, LSBFIRST, upper);
      digitalWrite(latchPin, HIGH);          
      digitalWrite(rowPin+i,HIGH);         
      delay(1);
    } 
    digitalWrite(rowPin+7,LOW);      
}






