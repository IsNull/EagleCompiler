#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "TokenList.h"
#include "parser/Parser.h"

using namespace std;

int main()
{
    Scanner* scanner = new Scanner();
    
    // ---- Simple Test cases
    
    string basicStatement = "var bool = (x| == 12);";
    string number = "var 456 789";
    string operators = "*+-=+==*";
    
    string brackets = "()";
    
    string numIdent = "12&abc";

    string testStatement = basicStatement;
    
    Parser p;
    
    
    // ----
    
    
    // tokenize it:
    cout << testStatement + "\n\n";
    const TokenList* list = scanner->scan(testStatement);
    cout << "\n\nTokens: " << *list;
    
    
    return 0;
}
