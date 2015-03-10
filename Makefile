EXEC = tetris.out
SRCS = src/main.cpp\
       src/grafico.cpp\
       src/pecas/peca.cpp\
       src/pecas/tpeca.cpp\
       src/pecas/lpeca.cpp\
       src/pecas/jpeca.cpp\
       src/pecas/zpeca.cpp\
       src/pecas/speca.cpp\
       src/pecas/ipeca.cpp\
       src/pecas/opeca.cpp\
       src/jogo_funcoes.cpp
LIBS = -lallegro -lallegro_image
FLAGS = -g -std=c++11

$(EXEC): $(SRCS)
	g++ $(FLAGS) -o $(EXEC) $(SRCS) $(LIBS)

clean:
	rm $(EXEC)
