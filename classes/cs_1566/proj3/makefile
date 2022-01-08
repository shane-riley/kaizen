CC       = gcc 
CFLAGS   = -O0 -Wall -g
LIBS      = -lXi -lXmu -lglut -lGLEW -lGLU -lm -lGL
OBJDIR   = ../mylib
OBJS     = $(OBJDIR)/initShader.o $(OBJDIR)/linalg.o

proj3: proj3.c $(OBJS)
	$(CC) -o proj3 proj3.c $(OBJS) $(CFLAGS) $(LIBS)

$(OBJDIR)/%.o: %.c %.h
	$(CC) -c @< -o $@ $(CFLAGS)

