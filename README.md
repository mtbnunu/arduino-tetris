# arduino-tetris

https://www.youtube.com/watch?v=OyGsXNQo1mc

Author: Jae Yeong Bae
        UBC ECE

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
        
