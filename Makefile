CFLAGS = -std=c++17
LDFLAGS = -lSDL2 -lSDL2_image -static-libgcc -static-libstdc++ -lm
LDFLAGSWINDOWS = -mwindows

GMist: src/*.cpp src/*.h
	g++ $(CFLAGS) -o build/gmist src/*.cpp $(LDFLAGS)

.PHONY: clean win

win: src/*.cpp src/*.h
	g++ $(CFLAGS) -o build/gmist.exe src/*.cpp $(LDFLAGSWINDOWS)

clean:
	rm -f build/gmist.exe