all:
	g++ -I src/include -L src/lib -o main main.cpp RenderWindow.cpp text.cpp TrafficLight.cpp Timer.cpp Road.cpp Lane.cpp Vehicle.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf