CC = gcc

CFLAGS = -Wall -g -I src/include
TARGET = stock_tracker_app
SRCS = src/main.c src/portfolio.c #src/file_handler.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean