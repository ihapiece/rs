CFLAGS = -std=c++17 -O0 -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++ -lm -no-pie
LDFLAGSWINDOWS = -mwindows

rs: src/*.cpp src/*.h
	g++ $(CFLAGS) -o build/rs src/*.cpp $(LDFLAGS)

.PHONY: clean win

win: src/*.cpp src/*.h
	g++ $(CFLAGS) -o build/rs.exe src/*.cpp $(LDFLAGSWINDOWS)

clean:
	rm -f build/gmist.exe
