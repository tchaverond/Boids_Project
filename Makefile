all : boids.out

boids.out : main.cpp Agent.o Prey.o Predator.o Boid.o bwindow.o
	g++ -g -Wall -o boids.out main.cpp Agent.o Prey.o Predator.o Boid.o bwindow.o -lX11 -L/usr/X11R6/lib

Agent.o : Agent.cpp Agent.h
	g++ -g -Wall -c -o Agent.o Agent.cpp

Prey.o : Prey.cpp Prey.h
	g++ -g -Wall -c -o Prey.o Prey.cpp

Predator.o : Predator.cpp Predator.h
	g++ -g -Wall -c -o Predator.o Predator.cpp
	
Boid.o : Boid.h
	g++ -g -Wall -c -o Boid.o Boid.cpp

bwindow.o : bwindow.h
	g++ -g -Wall -c -o bwindow.o bwindow.cpp

clean :
	rm *.o

mrproper : clean
	rm boids.out
