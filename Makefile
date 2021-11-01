CFLAGS = -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++ -lm -no-pie

rs: src/*.cpp src/*.h
	g++ $(CFLAGS) -o build/rs src/*.cpp $(LDFLAGS)
	cd build; ./rs

.PHONY: clean debug

debug: src/*.cpp src/*.h
	g++ -O0 -g $(CFLAGS) -o build/rs src/*.cpp $(LDFLAGS) -Wl,--no-as-needed -lprofiler -Wl,--as-needed

clean:
	rm -f build/gmist.exe
