#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "TokenList.h"

using namespace std;

int main()
{
    cout << "Hello world! Woot " << TokenType::Identifier << endl;
    
    Scanner* scanner = new Scanner();
    
    
    string basicStatement = "var bool = (x == 12);";
    string number = "123 456 789";
    string ident = "abc";
    
    const TokenList* list = scanner->scan(number);
    
    cout << "Tokens: " << list->toString();
    
    
    return 0;
}
