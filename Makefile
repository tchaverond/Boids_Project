all : boids.out

boids.out : main.cpp Agent.o Boid.o bwindow.o
	g++ -g -Wall -o boids.out main.cpp Agent.o Boid.o bwindow.o -lX11 -L/usr/X11R6/lib

Agent.o : Agent.cpp Agent.h
	g++ -g -Wall -c -o Agent.o Agent.cpp
	
Boid.o : Boid.cpp Boid.h
	g++ -g -Wall -c -o Boid.o Boid.cpp

bwindow.o : bwindow.cpp bwindow.h
	g++ -g -Wall -c -o bwindow.o bwindow.cpp

clean :
	rm *.o

mrproper : clean
	rm boids.out
