CC=gcc
CGFLAGS=-Wall -Wfatal-errors -I/opt/homebrew/include/SDL2
LDFLAGS=-Iinclude -lSDL2main -lSDL2 -L/opt/homebrew/lib -lSDL2_ttf -lSDL2_image

all : Chess_Game.x

Chess_Game.x : Chess_Game.o AI.o Board.o Constants.c Download_Log.o Evaluation.o Graphics.o Log.o Move_Generator.o Move_Ordering.o Moves_Treatment.o Pieces_Squares_Tables.o Pre_Computed_Data.o Search.o Settings.o Transposition_Table.o Utility.o
	$(CC) $(CGFLAGS) -o $@ $^ $(LDFLAGS)

%.o : %.c 
	$(CC) $(CGFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	rm -f *.o

realclean: clean
	rm -f *.x