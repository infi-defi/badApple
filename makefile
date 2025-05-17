CC = g++
FLAGS = `pkg-config --cflags --libs opencv4`

TARGET = badApple
VIDEO_SRC = bad_apple.mp4
VIDEO_DIR = $(HOME)/Videos/.badApple
INSTALL_DIR = /usr/local/bin

all: $(TARGET)

$(TARGET): badApple.o toAscii.o
	${CC} $^ -o $@ ${FLAGS}

toAscii.o: toAscii.cpp
	${CC} -c $^ -o $@ ${FLAGS}

badApple.o: badApple.cpp
	${CC} -c $^ -o $@ ${FLAGS}

install: all
	@echo "Creating video directory if it doesn't exist..."
	mkdir -p $(VIDEO_DIR)
	@echo "Moving video file to $(VIDEO_DIR)..."
	cp -f $(VIDEO_SRC) $(VIDEO_DIR)/
	@echo "Installing binary to $(INSTALL_DIR)..."
	sudo mv -f $(TARGET) $(INSTALL_DIR)/

.PHONY: all install clean

clean:
	rm -f *.o $(TARGET)
