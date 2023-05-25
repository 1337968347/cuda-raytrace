CC = g++
CFLAGS = -Wall -g
LFLAGS =
SRCS = ./src/main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = myprogram

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)