# Makefile for userInput library - to generate shared library and install it

.PHONY: all linux windows clean install
all: linux windows		# Default target to build for Linux and Windows

clean:
	@echo "Cleaning up..."
	@rm -rf ./*.so # remove the shared library since it was installed to /usr/lib64/userInput/

install:	# Install the binary to /usr/lib/userInput/
	@echo "Installing library..."
	@sudo mkdir -p /usr/lib64/userInput
	@sudo cp ./libuserInput.so /usr/lib/libuserInput.so
	@sudo cp ./userInput.h /usr/include/userInput.h
	@sudo ldconfig # Update the dynamic linker run-time bindings
	@sudo chmod +x /usr/local/bin/rechenspiel
	@make clean # Clean up after installation

uninstall:	# Uninstall the library from /usr/lib/userInput/ (deletes the directory entirely)
	@echo "Uninstalling library..."
	@sudo rm -rf /usr/lib/userInput/

linux: *.c
	@echo "Building for Linux x86_64..."
	@gcc --shared -fpic -o ./libuserInput.so *.c
	@strip --strip-unneeded ./libuserInput.so