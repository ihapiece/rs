CFLAGS = -std=c++17 -O0 -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++ -lm
LDFLAGSWINDOWS = -mwindows

GMist: src/*.cpp src/*.h
	g++ $(CFLAGS) -o build/gmist src/*.cpp $(LDFLAGS)

.PHONY: clean win

win: src/*.cpp src/*.h
	g++ $(CFLAGS) -o build/gmist.exe src/*.cpp $(LDFLAGSWINDOWS)

clean:
	rm -f build/gmist.exe
