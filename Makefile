all:

	g++ -c scumil.cpp
	ar crs libscumil.a scumil.o
	ranlib libscumil.a

	@echo now copy this shit to /usr/local/lib and the header to /usr/local/include dont forget sudo




clean:
	@echo good idea enough is enough
	rm -f libscumil.a
	rm -f scumil.o

