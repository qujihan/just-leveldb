database_dir := data

.PHONY: all dir cmake build clean

all: cmake build

dir:
	mkdir -p $(database_dir)

cmake: dir
	cmake -S . -B build

build:
	cmake --build build -j

clean:
	rm -rf build/ bin/ .cache/ $(database_dir)/ src/include/config.h