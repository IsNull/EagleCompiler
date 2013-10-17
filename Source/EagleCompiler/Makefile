CC = g++
CFLAGS = -Wall -std=c++11


OBJDIR = obj
OUT_RELEASE = bin/EagleCompiler

all: $(OUT_RELEASE)

$(OUT_RELEASE): $(OBJDIR)/main.o $(OBJDIR)/scanner.o $(OBJDIR)/token.o $(OBJDIR)/tokenlist.o $(OBJDIR)/util.o $(OBJDIR)/scannercontext.o $(OBJDIR)/scannerenums.o
	$(CC) $(CFLAGS) $(OBJDIR)/main.o $(OBJDIR)/scanner.o $(OBJDIR)/token.o $(OBJDIR)/tokenlist.o $(OBJDIR)/util.o $(OBJDIR)/scannercontext.o $(OBJDIR)/scannerenums.o -o $(OUT_RELEASE)

$(OBJDIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/scanner.o: scanner/Scanner.cpp $(OBJDIR)/util.o
	$(CC) $(CFLAGS) -c scanner/Scanner.cpp -o $(OBJDIR)/scanner.o
	
$(OBJDIR)/token.o: Token.cpp
	$(CC) $(CFLAGS) -c Token.cpp -o $(OBJDIR)/token.o

$(OBJDIR)/tokenlist.o: TokenList.cpp
	$(CC) $(CFLAGS) -c TokenList.cpp -o $(OBJDIR)/tokenlist.o

$(OBJDIR)/util.o: Util.cpp
	$(CC) $(CFLAGS) -c Util.cpp -o $(OBJDIR)/util.o
	
$(OBJDIR)/scannercontext.o: scanner/ScannerContext.cpp
	$(CC) $(CFLAGS) -c scanner/ScannerContext.cpp -o $(OBJDIR)/scannercontext.o
	
$(OBJDIR)/scannerenums.o: scanner/ScannerEnums.cpp
	$(CC) $(CFLAGS) -c scanner/ScannerEnums.cpp -o $(OBJDIR)/scannerenums.o


clean:
	rm $(OBJDIR)/*