PROGRAM = menu_v1 menu_v2
CC = $(CROSS_COMPILE)gcc
SRCS = menu_v1.c menu_v2.c
OBJS = $(SRCS:.c=.o)

all: $(PROGRAM)
	@echo "make done!"

menu_v1: menu_v1.o
	$(CC) $< -o $@

menu_v2: menu_v2.o
	$(CC) $< -o $@

clean:
	@rm -rf *.o $(PROGRAM)
	@echo "clean done!"

.PHONY:all clean
