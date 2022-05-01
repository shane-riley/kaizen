LIBS = -lXi -lXmu -lglut -lGLEW -lGLU -lm -lGL

triangle: linalg_test.c linalg.o
	gcc -o linalg_test linalg_test.c linalg.o $(LIBS)

linalg.o: linalg.c linalg.h
	gcc -c linalg.c
