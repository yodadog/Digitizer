CC              = g++
CFLAGS          = -g -c -Wall -I /usr/local/include/opencv
LDFLAGS         = -lpthread -pthread `pkg-config --cflags --libs opencv` 
SOURCES         = ${TARGET:=.cpp} 
OBJECTS		= ${TARGET:=.o}
INCLUDES        = 
TARGET          = Digitizer NeuralNet

all: $(TARGET)

$(TARGET): $(SOURCES)
	        $(CC) $(CFLAGS) $@.cpp -o $@.o 
		$(CC) $(LDFLAGS) $@.o -o $@
clean:
	        rm -rf $(OBJECTS) $(TARGET)
