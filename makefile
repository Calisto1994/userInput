# Makefile for userInput library - to generate shared library and install it

.PHONY: all linux windows clean install
all: linux windows		# Default target to build for Linux and Windows

clean:
	@echo "Cleaning up..."
	@rm -rf ./bin # remove binary directory

install:	# Install the binary to /usr/lib/userInput/
	@echo "Installing library..."
	@sudo cp ./bin/libuserInput.so /usr/lib/libuserInput.so
	@sudo cp ./userInput.h /usr/include/userInput.h
	@sudo ldconfig # Update the dynamic linker run-time bindings
	@make clean # Clean up after installation

uninstall:	# Uninstall the library from /usr/lib/userInput/ (deletes the directory entirely)
	@echo "Uninstalling library..."
	@sudo rm -rf /usr/lib/libuserInput.so
	@sudo rm -rf /usr/include/userInput.h
	@sudo ldconfig # Update the dynamic linker run-time bindings

linux: *.c
	@mkdir -p ./bin/
	@echo "Building for Linux x86_64..."
	@gcc --shared -fpic -o ./bin/libuserInput.so *.c
	@strip --strip-unneeded ./bin/libuserInput.so

windows: *.c
	@mkdir -p ./bin/
	@echo "Building for Windows x86_64..."
	@x86_64-w64-mingw32-gcc -shared -fpic -o ./bin/libuserInput.dll *.c
	@strip --strip-unneeded ./bin/libuserInput.dll
