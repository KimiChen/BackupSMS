PROJECT_NAME = bsms
INCLUDE = -I/usr/include/  -I.
LIB_PATH = -L /usr/lib/libsqlite3.dylib /usr/lib/libcurl.4.dylib
LIBS = -lsqlite3
CC = gcc -g -DDEBUG
CFLAGS =

OBJS = base64.o bsms.o

all: $(PROJECT_NAME)

.PHONY:clean
clean:
	rm -f *.o $(PROJECT_NAME)
		
$(PROJECT_NAME):	$(OBJS)
	$(CC) -o $(PROJECT_NAME) $(OBJS) $(LIBS) $(LIB_PATH) $(INCLUDE)

%.o : %.c
	$(CC) -c $< -o $@  $(CFLAGS) $(INCLUDE)