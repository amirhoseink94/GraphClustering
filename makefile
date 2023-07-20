CC = g++
CFLAGS = -Wall -g
OPGLFLAGS = -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
ARMAFLAG = -larmadillo
extFLAG = -I ~/Desktop/ThreeDEnvironment/ext/
HEADERS = Particle.h

res: main.o Particle.o Segment.o Face.o Graph.o Engin.o
	$(CC) $(CFLAGS) -o res main.o Particle.o Segment.o Face.o Graph.o Engin.o $(OPGLFLAGS) $(ARMAFLAG)
main.o: main.cpp
	$(CC) $(extFLAG) $(CFLAGS) -c main.cpp
Engin.o: src/Engin.cpp
	$(CC) $(CFLAGS) -c src/Engin.cpp
Graph.o: src/Graph.cpp
	$(CC) $(CFLAGS) -c src/Graph.cpp
Face.o: src/Face.cpp
	$(CC) $(CFLAGS) -c src/Face.cpp
Segment.o: src/Segment.cpp
	$(CC) $(CFLAGS) -c src/Segment.cpp
Particle.o: src/Particle.cpp
	$(CC) $(CFLAGS) -c src/Particle.cpp
clean:
	rm -f main.o Particle.o

#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
