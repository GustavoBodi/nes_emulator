CONAN_TOOLCHAIN:= Release/generators/conan_toolchain.cmake

.PHONY: clean test run

all: build/$(CONAN_TOOLCHAIN)
	@cd build && \
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$(CONAN_TOOLCHAIN) .. && \
	cmake --build . && \
	make && \
	./Nes

build/$(CONAN_TOOLCHAIN): | build venv
		. ./venv/bin/activate && \
		pip install conan && \
		pip install cmake && \
		pip install --upgrade conan && \
		conan remote update conancenter --url https://center2.conan.io && \
		conan install . --build=missing -of=. -g CMakeDeps -g CMakeToolchain

venv:
	python3 -m venv venv

build:
	mkdir -p build

run: | build
	cd build && \
	make && \
	./Nes

test: | build
	cd build && \
	cmake ../ && \
	make && \
	./UnitTests

clean: 
	rm -rf build/
