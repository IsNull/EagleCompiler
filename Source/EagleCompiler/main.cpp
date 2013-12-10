
#define IS_DEBUG

#include <iostream>
#include "Token.h"
#include "TokenList.h"
#include "scanner/Scanner.h"
#include "assemblizer/Assemblizer.h"
#include "assemblizer/NumericVariable.h"
#include "assemblizer/AssemblerInstruction.h"
#include "assemblizer/StringVariable.h"

#include "user.local"

using namespace std;

void testPascal() {
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
    Scanner scanner;
    const TokenList* list = scanner.scan(testStatement);
    cout << "\n\nTokens: " << *list;
}

void testSam() {
	Assemblizer::Assemblizer a;
	//Print text "foo" on standard output, use \\n for newline, to avoid escape string
	a.addVariableDeclaration(new Assemblizer::StringVariable("myText", "foo\\n"));
	a.addInstruction(new WriteToStandardOutputInstruction("myText"));
	
	cout << a.getFinalAssemblerCode() << endl;
}

int main()
{
#ifdef PASCAL
	testPascal();
#endif
#ifdef SAM
	testSam();
#endif
    return 0;
}
