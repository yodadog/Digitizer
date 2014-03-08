CC              = g++
CFLAGS          = -g -Wall -I /usr/local/include/opencv
LDFLAGS         = -lpthread -pthread `pkg-config --cflags --libs opencv` 
SOURCES         = ${TARGET:=.cpp} 
INCLUDES        = 
TARGET          = Digitizer NeuralNet

all: $(TARGET)

$(TARGET): $(SOURCES)
	        $(CC) $(CFLAGS) $(OBJECTS) $@.cpp -o $@ $(LDFLAGS)
clean:
	        rm -rf $(OBJECTS) $(TARGET)
