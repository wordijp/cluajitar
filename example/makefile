TARGET = main.exe

CXX = gcc
CXXFLAGS = -O2 -g -Wall

SRCS = main.c \
	   ../cluajitar_load.c \
	   ../cluajitar_write.c

INCLUDE = -I ./..

OBJS = $(patsubst %, obj/dig/%, $(SRCS:.c=.o))

# -----------------------------------------------

all: obj obj/dig $(TARGET)
	
obj: 
	mkdir obj
obj/dig:
	mkdir obj/dig
	
obj/dig/%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
	
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)
	strip $@

clean:
	rm $(TARGET)
	rm -Rf obj
	
# -----------------------------------------------

.PHONY: clean
