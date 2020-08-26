CC=g++
SOURCES=clean_videos.cpp 
OUT=clean_videos_vk
SHELL=/bin/bash

all: $(OUT)

$(OUT):
	@echo "Entering to the directory: /cpr"
	cd cpr; mkdir build
	@echo "Created cpr/build/ directory"
	cmake -S cpr/ -B cpr/build
	cd cpr/build/; make; sudo make install
	@echo "Builded cpr library"
	@echo "Set reference to /usr/local/lib/"
	sudo ln -s /usr/local/lib64/libcpr.so.1 /usr/local/lib/libcpr.so.1 || true
	LD_LIBRARY_PATH=/usr/local/lib/; export LD_LIBRARY_PATH
	$(CC) $(SOURCES) -o $(OUT) -l cpr
	@echo "Installed."

clean:
	cd cpr/build; make clean
	rm -rf cpr/build
	@echo "Remove cpr"
	rm $(OUT)
	@echo "Remove program"
