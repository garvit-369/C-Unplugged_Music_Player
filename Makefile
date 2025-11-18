CC = gcc
CFLAGS = -Wall -I./include -g
LDFLAGS =
SRCS = src/main.c src/list_func.c src/history_func.c src/song_list_func.c			# To change
OBJS = $(SRCS:.c=.o)
TARGET = assignment

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) # <-- 3. Add $(LDFLAGS) here

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)