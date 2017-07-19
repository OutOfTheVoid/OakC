#include <Parsing/Language/OakStructLiteralMemberValueConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakExpressionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakStructLiteralMemberValueConstructor & OakStructLiteralMemberValueConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakStructLiteralMemberValueConstructor> ();
	
}

OakStructLiteralMemberValueConstructor :: OakStructLiteralMemberValueConstructor ():
	ExpressionGroup ( { { & ( OakExpressionConstructor :: Instance () ), 0 } } )
{
}

OakStructLiteralMemberValueConstructor :: ~OakStructLiteralMemberValueConstructor ()
{
}


void OakStructLiteralMemberValueConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * MemberValueData = new ElementData ();
	
	MemberValueData -> MemberName = CurrentToken -> GetSource ();
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		delete MemberValueData;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier for struct name";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ASTElement * MemberValueElement = new ASTElement ();
	
	MemberValueElement -> SetTag ( OakASTTags :: kASTTag_StructLiteralMemberValue );
	MemberValueElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	MemberValueElement -> SetData ( MemberValueData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( ExpressionGroup.TryConstruction ( MemberValueElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 2 ], TokenCount ) == 0 )
	{
		
		delete MemberValueElement;
		
		if ( Error )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected value expression for struct member initialization";
		Output.ErrorProvokingToken = Input.Tokens [ 2 ];
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete MemberValueElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = MemberValueElement;
	
}

void OakStructLiteralMemberValueConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
