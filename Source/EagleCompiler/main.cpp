#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "TokenList.h"

using namespace std;

int main()
{
    cout << "Hello world! Woot " << TokenType::Identifier << endl;
    
    Scanner* scanner = new Scanner();
    const TokenList* list = scanner->scan("var test = 12;");
    
    cout << "Tokens: " << list->toString();
    
    
    return 0;
}
