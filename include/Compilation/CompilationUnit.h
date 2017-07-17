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
	
	// Each step of independent compilation.
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
	CompilationUnit ( const std :: string & FilePath, const std :: vector <std :: string> & SearchPaths );
	
	//CompilationUnit ( const std :: u32string & SourceText );
	
	// Destructor
	~CompilationUnit ();
	
	/**
	 * @brief Runs the compilation unit through all independant compilation steps.
	 * 
	 * @details Takes the compilation unity through the file loading, tokenization, lexing, and parsing steps.
	 * 
	 * @return Whether or not the compilation succeeded ( false represents a compilation failure ).
	 */
	bool RunIndependantCompilationSteps ( FileTable & FTable, const std :: vector <std :: string> & SearchPaths, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount );
	
	/**
	 * @brief Runs per-file semantic analysis on the AST previously generated, adding to the global object definition.
	 * 
	 * @details Translates the compilation unit's ast into OIL, using the supplied root namespace definition as the root for the program namespace. This can be used addatively.
	 * 
	 * @return Whether or not the AST was semantically valid ( including name collisions with previously added definitions ) ( false represents a compilation failure ).
	 */
	bool ApplyToOil ( OilNamespaceDefinition & RootObject, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount );
	
	/*
	* @brief Runs global object semantic analysis on non-builtin program definitions.
	* 
	* @details Runs the full semantic analyzer, resolving any inter-dependant information in the source definitions, but should not be run WITH the builtin additions.
	* 
	* @return Whether or not the program is semantically valid ( false represents a compilation failure ).
	*/
	static bool RunSourceAnalysis ( OilNamespaceDefinition & RootNS );
	
	/*
	* @brief Adds builtin definitions to the root namespace
	* 
	* @details Adds all builtin definitions, including architecture specific definitions, native functions, and language builtins.
	* 
	* @return Whether or not the program conflicted semantically with the builtin definitions added ( false represents a compilation failure ).
	*/
	static bool RunBuiltinAddition ( OilNamespaceDefinition & RootNS );
	
	
	/*
	* @brief Gets the file name that this compilation unit is processing.
	* 
	* @return The source file name.
	*/
	const std :: string & GetFileName () const;
	
	
private:
	
	static void TryResolveTypes ( OilNamespaceDefinition & RootNS, bool & Complete, bool & Error );
	
	// Current state of compilation. Used to track failure and represent compilation progress.
	CompilationStep CompilationState;
	
	// File loading
	TextFile SourceFile;
	std :: u32string SourceString;
	
	// Token list for pre and post lexing tokens.
	std :: vector <const Token *> Tokens;
	std :: vector <const Token *> PostLexTokens;
	
	// The local ast root.
	ASTElement * ASTRoot;
	
};

#endif
