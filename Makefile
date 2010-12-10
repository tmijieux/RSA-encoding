ARCH=x86_64
OBJECTS=objects/
BUILD=build/
SOURCES=sources/
INSTALLDIR=/opt/RSAencode/

all: object build main.o rsaCrypter.o rsaDecrypter.o  
	g++ $(OBJECTS)main.o $(OBJECTS)rsaCrypter.o $(OBJECTS)rsaDecrypter.o -o $(BUILD)rsa.$(ARCH)
	
main.o: $(SOURCES)main.cpp $(SOURCES)rsaCrypter.h $(SOURCES)rsaDecrypter.h
	g++ $(SOURCES)main.cpp -c  -o $(OBJECTS)main.o

rsaCrypter.o: $(SOURCES)rsaCrypter.cpp
	g++ $(SOURCES)rsaCrypter.cpp -c -o $(OBJECTS)rsaCrypter.o
	
rsaDecrypter.o: $(SOURCES)rsaDecrypter.cpp 
	g++ $(SOURCES)rsaDecrypter.cpp -c -o $(OBJECTS)rsaDecrypter.o
	
build:
	@mkdir -p $(BUILD)
	
object:
	@mkdir -p $(OBJECTS)
	
clean :
	rm -r $(OBJECTS) $(BUILD)

install: all
	@mkdir -p $(INSTALLDIR)
	cp $(BUILD)rsa.$(ARCH) $(INSTALLDIR)

uninstall:
	rm -r $(INSTALLDIR)

