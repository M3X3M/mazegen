clean:
	rm -rfv build/*

compile: clean
	g++ src/main.cpp src/Maze.cpp src/Tile.cpp -lncurses -o build/test.out

run: compile
	./build/test.out
