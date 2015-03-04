EXEC = tetris
SRCS = Tetris.cpp
LIBS = -lallegro -lallegro_image
FLAGS = -g

$(EXEC): $(SRCS) 
	g++ $(FLAGS) -o $(EXEC) $(SRCS) $(LIBS)

clean:
	rm $(EXEC)
