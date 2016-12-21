CFLAGS = -std=c++1y -stdlib=libc++ -F /Library/Frameworks -g -O0 -Wall -Wextra -pedantic -c
LFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -F /Library/Frameworks -g -O0 -Wall -Wextra -pedantic
SFMLFLAGS = -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-audio
all: snake
snake: snake.o
	g++ snake.o $(LFLAGS) $(SFMLFLAGS) -o snake
snake.o: snake.cpp snake.h
	g++ $(CFLAGS) -c snake.cpp
clean:
	-rm -f *.o snake
