CC = gcc

CFLAGS = -g 
LFLAGS = -shared -fPIC  

TARGET = libFixedPool.so
INCFILE = FixedPool.h

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
	$(RM) $(INCPATH)/FixedPool.h

install:
	cp -rf *.h $(INCPATH)
	cp -rf $(TARGET) $(LIBPATH)
