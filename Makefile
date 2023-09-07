#Makefile
TARGET = destest
LIB1 = libdes.a

all : $(TARGET)

$(TARGET) : main.cpp $(LIB1)
	gcc -o $@ main.cpp -L./ -ldes

$(LIB1) : des.o
	ar -ruv $(LIB1) des.o

des.o : des.cpp des.h
	gcc -c des.cpp

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f $(LIB1)
