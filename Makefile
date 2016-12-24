FLAGS = -std=c++1y

all: snake
snake: snake.o
	g++ snake.o $(FLAGS) -o snake -lsfml-graphics -lsfml-window -lsfml-system
snake.o: snake.cpp snake.h
	g++ $(FLAGS) -c snake.cpp
clean:
	-rm -f *.o snake
