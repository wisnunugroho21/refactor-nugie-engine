CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Engine: *.cpp */*.cpp */*.hpp */*/*.cpp */*/*.hpp
	g++ $(CFLAGS) -o bin/engine.out *.cpp */*.cpp */*/*.cpp $(LDFLAGS)

.PHONY: test clean

test: Engine
	./bin/engine.out

clean:
	rm -f bin/engine.out