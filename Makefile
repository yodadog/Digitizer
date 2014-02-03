CC              = g++
CFLAGS          = -g -c -Wall -I /usr/local/include/opencv
LDFLAGS         = -lpthread -pthread `pkg-config --cflags --libs opencv` 
SOURCES         = Digitizer.cpp
INCLUDES        = 
OBJECTS         = $(SOURCES:.cpp=.o)
TARGET          = Digitizer

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	        $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	        $(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	        rm -rf $(OBJECTS) $(TARGET)
