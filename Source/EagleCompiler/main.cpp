#include <iostream>
#include "Token.h"
#include "TokenList.h"
#include "scanner/Scanner.h"

//#include "scanner/Scanner.cpp"
//#include "parser/Parser.h"
//#include "parser/Parser.cpp"

using namespace std;

int main()
{
    
    
    // ---- Simple Test cases
    
    string basicStatement = "var bool = (x| == 12);";
    string number = "var 456 789";
    string operators = "*+-=+==*";
    
    string brackets = "()";
    
    string numIdent = "12&abc";

    string testStatement = basicStatement;
    
    //Parser p;
    
    
    // ----
    
    
    // tokenize it:
    cout << testStatement + "\n\n";
    Scanner scanner;
    const TokenList* list = scanner.scan(testStatement);
    cout << "\n\nTokens: " << *list;


    return 0;
}
