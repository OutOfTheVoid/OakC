#include <Compilation/CompilationUnit.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

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

#include <Builtins/OakBuiltinTypes.h>

#include <OIL/OilImplementBlock.h>
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

const std :: string & CompilationUnit :: GetFileName ()
{
	
	return SourceFile.GetName ();
	
}

bool CompilationUnit :: RunIndependantCompilationSteps ( FileTable & FTable )
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
			LOG_FATALERROR_NOFILE ( SourceFile.GetName () + ", Line " + std :: to_string ( ErrorToken -> GetLine () ) + ", Char " + std :: to_string ( ErrorToken -> GetChar () ) + ": " + ( ( ErrorSuggestion != "" ) ? ErrorSuggestion : ( "Unexpected token \"" + CodeConversion :: ConvertUTF32ToUTF8 ( ErrorToken -> GetSource () ) ) + "\"" ) );
		else
			LOG_FATALERROR_NOFILE ( ( ErrorSuggestion != "" ) ? ErrorSuggestion : std :: string ( "unkown error" ) );
		
		delete ASTRoot;
		ASTRoot = NULL;
		
		return false;
		
	}
	else if ( AvailableTokens != 0 )
	{
		
		ErrorToken = PostLexTokens [ PostLexTokens.size () - AvailableTokens ];
		
		LOG_FATALERROR_NOFILE ( SourceFile.GetName () + ", Line " + std :: to_string ( ErrorToken -> GetLine () ) + ", Char " + std :: to_string ( ErrorToken -> GetChar () ) + ": " + ( ( ErrorSuggestion != "" ) ? ErrorSuggestion : ( "Unexpected token \"" + CodeConversion :: ConvertUTF32ToUTF8 ( ErrorToken -> GetSource () ) ) + "\"" ) );
		
	}
	else
	{
		
		std :: cout << "AST: " << std :: endl;
		
		_PrintAST ( ASTRoot, 0 );
		
	}
	
	FTable.AddFile ( SourceFile.GetName (), this );
	
	std :: vector <CompilationUnit *> ImportedUnits;
	
	if ( ! OakResolveImports ( ASTRoot, SourceFile.GetName (), FTable, ImportedUnits ) )
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

bool CompilationUnit :: RunSourceAnalysis ( OilNamespaceDefinition & RootNS )
{
	
	LOG_VERBOSE ( "[ ALL ]: compilation step: Implement Resolution." );
	
	OilImplementBlock * FailedBlock = NULL;
	ResolveImplementsStatus TraitResolutionStatus = OilResolveImplements ( RootNS, FailedBlock );
	
	switch ( TraitResolutionStatus )
	{
		
		case kResolveImplementsStatus_Success:
			break;
			
		case kResolveImplementsStatus_Failure_NoResolution:
		{
			
			LOG_FATALERROR_NOFILE ( "Implement resolution error! (No Resolution)" );
			
			LOG_FATALERROR_NOFILE ( std :: string ( "Failed implement of " ) + CodeConversion :: ConvertUTF32ToUTF8 ( FailedBlock -> GetImplementedType () -> GetName () ) );
			
			return false;
			
		}
		
		case kResolveImplementsStatus_Failure_NoResolution_ForTrait:
		{
			
			LOG_FATALERROR_NOFILE ( "Implement resolution error! (No trait Resolution)" );
			
			LOG_FATALERROR_NOFILE ( std :: string ( "Failed implement of " ) + CodeConversion :: ConvertUTF32ToUTF8 ( FailedBlock -> GetImplementedType () -> GetName () ) + " for trait: " + CodeConversion :: ConvertUTF32ToUTF8 ( FailedBlock -> GetForTrait () -> GetName () ) );
			
			return false;
			
		}
		
		case kResolveImplementsStatus_Failure_TemplateMismatch:
		{
			
			LOG_FATALERROR_NOFILE ( "Implement resolution error! (Template Mismatch)" );
			
			return false;
			
		}
		
		case kResolveImplementsStatus_Failure_Conflict:
		{
			
			LOG_FATALERROR_NOFILE ( "Implement resolution error! (Name Conflict)" );
			
			return false;
			
		}
			
		default:
		{
			
			LOG_FATALERROR_NOFILE ( "Implement resolution error! (Unkown)" );
			
			return false;
			
		}
		
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
