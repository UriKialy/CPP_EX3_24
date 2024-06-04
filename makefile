CC = g++
CFLAGS = -Wall -Wextra -std=c++11

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
EXEC := myprogram

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)