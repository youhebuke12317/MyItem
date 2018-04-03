CC = gcc

CFLAGS = -g 
LFLAGS = -shared -fPIC  

TARGET = libPLog.so

LIBPATH = /usr/lib64
INCPATH = /usr/include


SOUCE_FILES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SOUCE_FILES))


$(TARGET): $(SOUCE_FILES)
	$(CC) $(LFLAGS) $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	$(RM) $(TARGET) $(OBJS)
	# $(RM) $(LIBPATH)/$(TARGET)
	# $(RM) $(INCPATH)/PLog.h 

install:
	cp -rf *.h $(INCPATH)
	cp -rf $(TARGET) $(LIBPATH)
