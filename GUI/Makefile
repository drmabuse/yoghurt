CC=g++
DEBUG=-g
CFLAGS=-c $(DEBUG) `pkg-config gtkmm-3.0 --cflags --libs`
LFLAGS=$(DEBUG) `pkg-config gtkmm-3.0 --cflags --libs`
OBJECTS=screen.o gui.o example.o
TARGET=example

all: $(TARGET)

$(TARGET) : $(OBJECTS) $(TARGET).o
	$(CC) $(OBJECTS) -o $(TARGET) $(LFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) $<

clean:
	touch $(OBJECTS)
	rm -f $(OBJECTS)
	touch $(TARGET)
	rm -f $(TARGET)
