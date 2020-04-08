# Connect4
A connect4 AI on a 12x6 board.
I used bitboard, but 6x12 = 72 and a long is 64bits so I had to make my own 72 bitboard.  
I used two int : on of 16 bits which contains the 16 highest bit of my integer and a 64 bits which contains the 64 least significant bits. It makes 80 bits, I needed at least 6 bits in addition of the 72 bits to be perfect so 80 is enough.

# Party exemple : 

![](readmeImages/connect4.gif)
