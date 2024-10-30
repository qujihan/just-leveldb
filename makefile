build_type := DEBUG
build_tool := Ninja
# build_tool := Unix Makefiles
database_dir := data

.PHONY: all clean cmake build

all: cmake build

dir:
	mkdir -p $(database_dir)

cmake: dir
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$(build_type) -G $(build_tool) -DLEVELDB_DATA_DIR=$(database_dir)
	

build:
	cmake --build build -j

clean:
	/bin/rm -rf build/ bin/ .cache/ $(database_dir)/ src/include/config.h