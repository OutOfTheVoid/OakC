#include <Compilation/CompilationUnit.h>
#include <Compilation/Targets.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>
#include <Logging/ErrorUtils.h>

#include <Tokenization/Tokenizer.h>

#include <Tokenization/Language/OakTokenizer.h>
#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Lexer.h>

#include <Lexing/Language/OakLexer.h>
#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Parsing/ASTConstructionGroup.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakParser.h>
#include <Parsing/Language/OakASTTags.h>

#include <EarlyAnalysis/OakImportResolution.h>
#include <EarlyAnalysis/OakOilTranslation.h>
#include <EarlyAnalysis/OilImplementResolution.h>
#include <EarlyAnalysis/OilTypeResolution.h>

#include <Builtins/OakBuiltinTypes.h>

#include <OIL/OilImplementBlock.h>
#include <OIL/OilConstStatement.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilTypeRef.h>

#include <iostream>

CompilationUnit :: CompilationUnit ( const std :: string & FilePath ):
	CompilationState ( kCompilationStep_FileLoad ),
	SourceFile ( FilePath, false ),
	SourceString (),
	Tokens (),
	PostLexTokens (),
	ASTRoot ( NULL )
{
	
	OakTokenizer :: GetOakTokenizer (); // Ensure initialization pre-run
	OakLexer :: GetOakLexer ();
	OakParser :: GetOakParser ();
	
}

CompilationUnit :: ~CompilationUnit ()
{
	
	if ( ASTRoot != NULL )
		delete ASTRoot;
	
}

void _PrintAST ( const ASTElement * Root, uint32_t Indent )
{
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		std :: cout << "|   ";
		
	if ( Root != NULL )
	{
		
		std :: cout << "[ " << OakASTTags :: TagNames [ Root -> GetTag () ] << " ]" << std :: endl;
		
		for ( uint32_t I = 0; I < Root -> GetSubElementCount (); I ++ )
			_PrintAST ( Root -> GetSubElement ( I ), Indent + 1 );
		
	}
	else
		std :: cout << "[ NULL ]" << std :: endl;
	
}

const std :: string & CompilationUnit :: GetFileName () const
{
	
	return SourceFile.GetName ();
	
}

void PrintTokens ( const std :: vector <const Token *> & Tokens )
{
	
	std :: string PrintString;
	
	for ( uint64_t I = 0; I < Tokens.size (); I ++ )
	{
		
		PrintString += "[ ";
		
		if ( Tokens [ I ] -> GetTag () == OakTokenTags :: kTokenTag_Identifier )
			PrintString += OakKeywordTokenTags :: KeywordAuxTagNames [ Tokens [ I ] -> GetAuxTag () ];
		else
			PrintString += OakTokenTags :: TagNames [ Tokens [ I ] -> GetTag () ];
		
		PrintString += " ]";
		
	}
	
	LOG_VERBOSE ( PrintString );
	
}

bool CompilationUnit :: RunIndependantCompilationSteps ( FileTable & FTable, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount )
{
	
	if ( CompilationState != kCompilationStep_FileLoad )
		return false;
	
	LOG_VERBOSE ( "[" + SourceFile.GetName () + "]: compilation step: FileLoad." );
	
	if ( ! SourceFile.Exists () )
	{
		
		LOG_FATALERROR_NOFILE ( SourceFile.GetName () + " does not exist!" );
		
		return false;
		
	}
	
	uint32_t FileStatus;
	
	SourceFile.Open ( & FileStatus, false );
	
	if ( FileStatus != File :: kStatus_Success )
	{
		
		LOG_FATALERROR_NOFILE ( "Failed to open " + SourceFile.GetName () );
		
		return false;
	}
	
	std :: string SourceStringUTF8;
	
	SourceFile.ReadToString ( & FileStatus, SourceStringUTF8, 0 );
	
	if ( FileStatus != File :: kStatus_Success )
	{
		
		LOG_FATALERROR_NOFILE ( "Failed to read " + SourceFile.GetName () );
		
		SourceFile.Close ( & FileStatus );
		
		return false;
		
	}
	
	SourceFile.Close ( & FileStatus );
	
	SourceString.assign ( CodeConversion :: ConvertUTF8ToUTF32 ( SourceStringUTF8 ) );
	SourceStringUTF8.clear ();
	
	LOG_VERBOSE ( "[" + SourceFile.GetName () + "]: compilation step: Tokenization." );
	
	CompilationState = kCompilationStep_Tokenization;
	
	const Tokenizer & TokenizerInstance = OakTokenizer :: GetOakTokenizer ();
	
	if ( ! TokenizerInstance.TokenizeString ( SourceString, Tokens, SourceFile.GetName (), this ) )
		return false;
	
	LOG_VERBOSE ( "[" + SourceFile.GetName () + "]: compilation step: Lexing." );
	
	CompilationState = kCompilationStep_Lexer;
	
	const Lexer & LexerInstance = OakLexer :: GetOakLexer ();
	
	if ( ! LexerInstance.LexTokens ( Tokens, PostLexTokens ) )
		return false;
	
	// Now that we have the lexed tokens, we can get rid of the original list.
	for ( uint64_t I = 0; I < Tokens.size (); I ++ )
		delete Tokens [ I ];
	
	Tokens.clear ();
	
	PrintTokens ( PostLexTokens );
	
	LOG_VERBOSE ( "[" + SourceFile.GetName () + "]: compilation step: Parsing." );
	
	CompilationState = kCompilationStep_Parser;
	
	const ASTConstructionGroup & ParserInstance = OakParser :: GetOakParser ();
	
	ASTRoot = new ASTElement ();
	
	ASTRoot -> SetTag ( OakASTTags :: kASTTag_File );
	
	bool ConstructionError = false;
	const Token * ErrorToken = NULL;
	std :: string ErrorSuggestion;
	uint64_t AvailableTokens = PostLexTokens.size ();
	
	ParserInstance.TryConstruction ( ASTRoot, 0xFFFFFFFFFFFFFFFUL, ConstructionError, ErrorSuggestion, ErrorToken, & PostLexTokens [ 0 ], AvailableTokens );
	
	if ( ConstructionError )
	{
		
		if ( ErrorToken != NULL )
			LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( ErrorToken -> GetSourceRef () ) + ( ( ErrorSuggestion != "" ) ? ErrorSuggestion : ( "Unexpected token \"" + CodeConversion :: ConvertUTF32ToUTF8 ( ErrorToken -> GetSource () ) ) + "\"" ) );
		else
			LOG_FATALERROR_NOFILE ( ( ErrorSuggestion != "" ) ? ErrorSuggestion : std :: string ( "unkown error" ) );
		
		delete ASTRoot;
		ASTRoot = NULL;
		
		return false;
		
	}
	else if ( AvailableTokens != 0 )
	{
		
		ErrorToken = PostLexTokens [ PostLexTokens.size () - AvailableTokens ];
		
		LOG_FATALERROR_NOFILE ( SourceFile.GetName () + ", Line " + std :: to_string ( ErrorToken -> GetSourceRef ().GetLine () ) + ", Char " + std :: to_string ( ErrorToken -> GetSourceRef ().GetChar () ) + ": " + ( ( ErrorSuggestion != "" ) ? ErrorSuggestion : ( "Unexpected token \"" + CodeConversion :: ConvertUTF32ToUTF8 ( ErrorToken -> GetSource () ) ) + "\"" ) );
		
	}
	else
	{
		
		std :: cout << "AST: " << std :: endl;
		
		_PrintAST ( ASTRoot, 0 );
		
	}
	
	FTable.AddFile ( SourceFile.GetName (), this );
	
	std :: vector <CompilationUnit *> ImportedUnits;
	
	if ( ! OakResolveImports ( ASTRoot, SourceFile.GetName (), FTable, ImportedUnits, CompilationConditions, CompilationConditionCount ) )
		return false;
	
	CompilationState = kCompilationStep_OILTranslation;
	
	return true;
	
}

bool CompilationUnit :: ApplyToOil ( OilNamespaceDefinition & RootNS )
{
	
	LOG_VERBOSE ( "[" + SourceFile.GetName () + "]: compilation step: OIL Translation." );
	
	if ( CompilationState != kCompilationStep_OILTranslation )
		return false;
	
	if ( ! OakTranslateFileTreeToOil ( ASTRoot, RootNS ) )
		return false;
	
	return true;
	
}

void CompilationUnit :: TryResolveTypes ( OilNamespaceDefinition & RootNS, bool & Complete, bool & Error )
{
	
	Error = false;
	Complete = false;
	
	bool Unresolved = false;
	bool Progress = false;
	
	ResolveImplementsStatus ResolveResult_Implement = OilResolveImplements ( RootNS );
	
	if ( ResolveResult_Implement == kResolveImplementsStatus_Success_Complete )
		Progress = true;
	else if ( ResolveResult_Implement == kResolveImplementsStatus_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_Implement == kResolveImplementsStatus_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	TypeResolutionResult ResolveResult_Constants = OilTypeResolution_Constants ( RootNS );
	
	if ( ResolveResult_Constants == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( ResolveResult_Constants == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_Constants == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	TypeResolutionResult ResolveResult_Bindings = OilTypeResolution_Bindings ( RootNS );
	
	if ( ResolveResult_Bindings == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( ResolveResult_Bindings == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_Bindings == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	TypeResolutionResult ResolveResult_Structs = OilTypeResolution_StructDefinitions ( RootNS );
	
	if ( ResolveResult_Structs == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( ResolveResult_Structs == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_Structs == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	TypeResolutionResult ResolveResult_Functions = OilTypeResolution_Functions ( RootNS );
	
	if ( ResolveResult_Functions == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( ResolveResult_Functions == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_Functions == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	TypeResolutionResult ResolveResult_ImplementMembers = OilTypeResolution_ImplementMembers ( RootNS );
	
	if ( ResolveResult_ImplementMembers == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( ResolveResult_ImplementMembers == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_ImplementMembers == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	TypeResolutionResult ResolveResult_TypeAliases = OilTypeResolution_TypeAliases ( RootNS );
	
	if ( ResolveResult_TypeAliases == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( ResolveResult_TypeAliases == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_TypeAliases == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	TypeResolutionResult ResolveResult_Traits = OilTypeResolution_Traits ( RootNS );
	
	if ( ResolveResult_Traits == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( ResolveResult_Traits == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ResolveResult_Traits == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
	{
		
		Error = true;
		
		return;
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return;
		else
		{
			
			Error = true;
			
			return;
			
		}
		
	}
	
	Complete = true;
	
}

bool CompilationUnit :: RunSourceAnalysis ( OilNamespaceDefinition & RootNS )
{
	
	LOG_VERBOSE ( "[ ALL ]: compilation step: Semantic analysis." );
	
	bool Stop = false;
	
	while ( ! Stop )
	{
		
		bool Error;
		bool Complete;
		
		TryResolveTypes ( RootNS, Complete, Error );
		
		if ( Error )
			return false;
		
		if ( Complete )
			break;
		
	}
	
	return true;
	
}

bool CompilationUnit :: RunBuiltinAddition ( OilNamespaceDefinition & RootNS )
{
	
	LOG_VERBOSE ( "[ ALL ]: compilation step: Builtin Addition" );
	
	if ( ! OakAddBuiltinTypes ( RootNS ) )
		return false;
	
	return true;
	
}
