all: build-all

build-all: build-server build-client

build-client:
	gcc client.c -o client.exe -lws2_32

build-server:
	gcc server.c -o server.exe -lws2_32