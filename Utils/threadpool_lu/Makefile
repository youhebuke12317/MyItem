CC = gcc

CFLAGS = -g -shared -fPIC 
LFLAGS = -lpthread

TARGET = libfixedthreadpool.so

LIBPATH = /usr/local/youhebuke
INCPATH = /usr/local/include

SOUCE_FILES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SOUCE_FILES))


$(TARGET): $(SOUCE_FILES)
	$(CC) $(LFLAGS) $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	$(RM) $(TARGET) $(OBJS)
	$(RM) $(LIBPATH)/$(TARGET)
	$(RM) $(INCPATH)/FixedThreadPool.h 

install:
	cp -rf *.h $(INCPATH)
	mv $(TARGET) $(LIBPATH)
