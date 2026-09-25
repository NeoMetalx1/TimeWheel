all:
	g++ -std=c++20 -Isrc src/main.cpp src/timewheel.cpp src/taskexecutor.cpp -o wheeltest
