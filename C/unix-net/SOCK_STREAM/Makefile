OBJ1:=server
OBJ2:=client

CC:=gcc

all:$(OBJ1) $(OBJ2)
$OBJ1:server.o
	$(CC) -o $^ $@ 
$OBJ2:client.o
	$(CC) -o $^ $@

clean:
	rm -rf $(OBJ1) $(OBJ2) *.o

