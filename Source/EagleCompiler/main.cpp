#include <iostream>
#include "Token.h"
#include "TokenList.h"
#include "scanner/Scanner.h"

#include"assemblizer/Assemblizer.h"

using namespace std;

void testMyAssemblizer() {
	Assemblizer a;
	
	cout << endl << endl;
	
	cout << a.getFinalAssemblerCode() << endl;
}

int main()
{
    
    
    // ---- Simple Test cases
    
    string basicComment = "// Comment haha";
    string basicStatement = "var bool = (x| == 12); //Comment haha\ntest();";
    string number = "var 456 789";
    string operators = "*+-=+==*";
    
    string brackets = "()";
    
    string numIdent = "12&abc";

    string testStatement = basicStatement;
    
    //Parser p;
    
    
    // ----
    
    
    // tokenize it:
    cout << testStatement + "\n\n";
//     Scanner scanner;
//     const TokenList* list = scanner.scan(testStatement);
//     cout << "\n\nTokens: " << *list;

	testMyAssemblizer();

    return 0;
}
