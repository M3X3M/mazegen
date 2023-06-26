clean:
	rm -rfv build/*

compile: clean
	g++ src/main.cpp src/Maze.cpp src/Tile.cpp -lncurses -o build/mazegen.out

example: compile
	./build/mazegen.out -x 8 -y 8 -a 100
