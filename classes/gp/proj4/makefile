CC       = gcc 
CFLAGS   = -O0 -g -Wall 
LIBS      = -lXi -lXmu -lglut -lGLEW -lGLU -lm -lGL
OBJDIR   = ../mylib
OBJS     = $(OBJDIR)/initShader.o $(OBJDIR)/linalg.o

proj4: proj4.c $(OBJS)
	$(CC) -o proj4 proj4.c $(OBJS) $(CFLAGS) $(LIBS)

$(OBJDIR)/%.o: %.c %.h
	$(CC) -c @< -o $@ $(CFLAGS)

