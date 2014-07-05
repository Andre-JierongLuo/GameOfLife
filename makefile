# super simple makefile
# call it using 'make run

#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

all:
	@echo "Compiling..."
	g++ -o life src/*.cpp -L/usr/X11R6/lib -lX11 -lstdc++ $(MAC_OPT)

run: all
	@echo "Running..."
	./life

clean:
