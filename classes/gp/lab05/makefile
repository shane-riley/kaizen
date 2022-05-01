CC       = gcc 
CFLAGS   = -O3 -Wall 
LIBS      = -lXi -lXmu -lglut -lGLEW -lGLU -lm -lGL
OBJDIR   = ../mylib
OBJS     = $(OBJDIR)/initShader.o $(OBJDIR)/linalg.o

lab05: lab05.c $(OBJS)
	$(CC) -g -o lab05 lab05.c $(OBJS) $(CFLAGS) $(LIBS)

$(OBJDIR)/%.o: %.c %.h
	$(CC) -c @< -o $@ $(CFLAGS)

