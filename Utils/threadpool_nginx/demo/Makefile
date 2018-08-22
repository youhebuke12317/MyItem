CC = gcc

CFLAGS  = -g  -fPIC  -m64 
LFLAGS  = 
MYFLAGS = -L/usr/local/youhebuke 							\
		  -lthreadpool_nginx

TARGET  = app

SRC = .
OBJ = ./obj
WORK_PATH = .

SOUCE_FILES = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOUCE_FILES))

#%.o : %.c %.h
#	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ)/%.o : $(SRC)/%.c
	$(CC) -c $(CFLAGS) $< -o $@


$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS) $(MYFLAGS) $(PLUGINCFLAGS)

.PHONY:clean
clean:
	$(RM) $(TARGET) $(OBJS)

install:




