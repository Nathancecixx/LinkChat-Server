CFLAGS = -Wall -Wextra -pedantic

all: final

final: main.o stack.o client_socket.o networkhandler.o
	@echo "Linking and building final project"
	gcc $(flags) main.o stack.o client_socket.o networkhandler.o -o final
	chmod +x final

main.o: main.c
	@echo "Building main.o"
	gcc $(CFLAGS) -c main.c

stack.o: stack.c
	@echo "Building stack.o"
	gcc $(CFLAGS) -c stack.c

client_socket.o: client_socket.c
	@echo "Building client_socket.o"
	gcc $(CFLAGS) -c client_socket.c

networkhandler.o: networkhandler.c
	@echo "Building networkhandler.o"
	gcc $(CFLAGS) -c networkhandler.c


clean:
	@echo "recoving everything but source files"
	rm main.o stack.o client_socket.o networkhandler.o final
