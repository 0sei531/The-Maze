build:
	gcc -Wall -Werror -Wextra -pedantic -I/usr/include/SDL2 -L/path/to/custom/lib ./src/*.c -lm -o maze -lSDL2

run:
	./maze

clean:
	rm maze
