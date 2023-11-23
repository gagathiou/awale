# Nom du programme
TARGET = awale

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -g -lm

# Fichiers source
SRCS = List.c player.c main.c history.c game.c List_P.c friends.c
OBJS = $(SRCS:.c=.o)

# Inclusion du fichier en-tête
INC = -I.

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Règle générique pour les fichiers objet
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Nettoyer les fichiers intermédiaires et l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)
