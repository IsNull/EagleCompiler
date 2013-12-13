
#define IS_DEBUG

#include <iostream>
#include <algorithm>
#include <fstream>
#include "Token.h"
#include "TokenList.h"
#include "scanner/Scanner.h"
#include "assemblizer/Assemblizer.h"
#include "assemblizer/NumericVariable.h"
#include "assemblizer/AssemblerInstruction.h"
#include "assemblizer/StringVariable.h"

#include "user.local"

using namespace std;

string sourceCode;


void scan() {

    // tokenize it:
    cout << "\nListing Source code:\n\n"<< sourceCode << "\n\n";
    
    Scanner scanner;
    const TokenList* list = scanner.scan(sourceCode);
    cout << "\n\nTokens: " << *list;
}

void testSam() {
	Assemblizer::Assemblizer a;
	//Print text "foo" on standard output, use \\n for newline, to avoid escape string
	a.addVariableDeclaration(new Assemblizer::StringVariable("myText", "foo\\n"));
	a.addInstruction(new WriteToStandardOutputInstruction("myText"));
	
	cout << a.getFinalAssemblerCode() << endl;
}




char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int main(int argc, char* argv[])
{
    
    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        cout << "EagleCompiler Help;"<< "\n";
        cout << "Available Options:"<< "\n";
        cout << "-s <path to source>"<< "\n";
        cout << "-t <path to parsetable>"<< "\n";
    }
    
    char * sourceFile = getCmdOption(argv, argv + argc, "-s");
    
    if (sourceFile)
    {
        cout << "Reading source from " << sourceFile << "\n";
        // read source from given file
        ifstream ifs(sourceFile);
        if(ifs){
            sourceCode.assign( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>())
                       );
        }else{
            cout << "File does not exist!" << "\n";
            return -1;
        }
    }else{
        cout << "Missing mandatory param -s <Path to IML source>" << "\n";
        return -1;
    }
    
    
    
#ifdef PASCAL
	scan();
#endif
#ifdef SAM
	testSam();
#endif
    return 0;
}
