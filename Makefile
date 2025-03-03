UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CORES := $(shell nproc)
else
	CORES := 1
endif

BUILD_DIR = ./build
OUTPUT_DIR = .

all: debug

debug:
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(abspath $(OUTPUT_DIR))
	@cmake --build $(BUILD_DIR) -- -j$(CORES)

release:
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(abspath $(OUTPUT_DIR))
	@cmake --build $(BUILD_DIR) -- -j$(CORES)

clean:
	@rm -rf $(BUILD_DIR)

re_debug: clean debug

re_release: clean release

.PHONY: all debug release clean re_debug re_release