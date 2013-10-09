CC = g++
CFLAGS = -Wall -std=c++11


OBJDIR = obj/Release
OUT_RELEASE = bin/Release/EagleCompiler

all: $(OUT_RELEASE)

$(OUT_RELEASE): $(OBJDIR)/main.o $(OBJDIR)/scanner.o $(OBJDIR)/token.o $(OBJDIR)/tokenlist.o $(OBJDIR)/util.o
	$(CC) $(CFLAGS) $(OBJDIR)/main.o $(OBJDIR)/scanner.o $(OBJDIR)/token.o $(OBJDIR)/tokenlist.o $(OBJDIR)/util.o -o $(OUT_RELEASE)

$(OBJDIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/scanner.o: Scanner.cpp $(OBJDIR)/util.o
	$(CC) $(CFLAGS) -c Scanner.cpp -o $(OBJDIR)/scanner.o
	
$(OBJDIR)/token.o: Token.cpp
	$(CC) $(CFLAGS) -c Token.cpp -o $(OBJDIR)/token.o

$(OBJDIR)/tokenlist.o: TokenList.cpp
	$(CC) $(CFLAGS) -c TokenList.cpp -o $(OBJDIR)/tokenlist.o

$(OBJDIR)/util.o: Util.cpp
	$(CC) $(CFLAGS) -c Util.cpp -o $(OBJDIR)/util.o
