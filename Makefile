
LUA_INC = /usr/include/lua5.4/

CC = gcc
CFLAGS = -fPIC -pedantic -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-const-variable
LDFLAGS = -shared
DEBUGFLAGS = -g -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG

TARGET = lib/sox.so
SRCS = $(shell echo src/*.c)
OBJS = $(SRCS: .c=.o)
INCS = -I$(LUA_INC)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(LDFLAGS) $(INCS) -o $(TARGET) $(OBJS)
