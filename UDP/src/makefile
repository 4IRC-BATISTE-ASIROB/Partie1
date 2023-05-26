# Définir le compilateur
CC = gcc

# Définir les drapeaux de compilation
CFLAGS = -Wall

# Définir les chemins
BIN_DIR = ../bin
SRC_DIR = .

all: client server

client: $(SRC_DIR)/client.c
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

server: $(SRC_DIR)/server.c
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

clean:
	rm -f $(BIN_DIR)/client $(BIN_DIR)/server
