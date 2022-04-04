app:
	g++ image2ascii.cpp -o image2ascii `pkg-config --cflags --libs opencv4`
	g++ cam2ascii.cpp -o cam2ascii `pkg-config --cflags --libs opencv4`
