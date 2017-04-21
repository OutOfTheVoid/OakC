#ifndef COMPILATION_COMPILATIONUNIT_H
#define COMPILATION_COMPILATIONUNIT_H

#include <Filesystem/TextFile.h>

#include <Tokenization/Token.h>

#include <string>
#include <vector>

#include <EarlyAnalysis/FileTable.h>

class ASTElement;
class OilNamespaceDefinition;

class CompilationUnit
{
public:
	
	enum CompilationStep
	{
		
		kCompilationStep_FileLoad,
		kCompilationStep_Tokenization,
		kCompilationStep_Lexer,
		kCompilationStep_Parser,
		kCompilationStep_OILTranslation,
		kCompilationStep_TraitResolution,
		
	};
	
	/**
	 * @brief Constructs a compilation unit.
	 * 
	 * @param FilePath Path to the source file
	 */
	CompilationUnit ( const std :: string & FilePath );
	
	//CompilationUnit ( const std :: u32string & SourceText );
	
	// Destructor
	~CompilationUnit ();
	
	/**
	 * @brief Runs the compilation unit through all independant compilation steps.
	 * 
	 * @details Takes the compilation unity through the file loading, tokenization, lexing, and parsing steps.
	 * 
	 * @return Whether or not the compilation succeeded
	 */
	bool RunIndependantCompilationSteps ( FileTable & FTable );
	bool ApplyToOil ( OilNamespaceDefinition & RootObject );
	
	static bool RunSourceAnalysis ( OilNamespaceDefinition & RootNS );
	static bool RunBuiltinAddition ( OilNamespaceDefinition & RootNS );
	
	const std :: string & GetFileName ();
	
	
private:
	
	CompilationStep CompilationState;
	
	// File loading
	TextFile SourceFile;
	std :: u32string SourceString;
	
	// Token list
	std :: vector <const Token *> Tokens;
	std :: vector <const Token *> PostLexTokens;
	
	ASTElement * ASTRoot;
	
};

#endif
