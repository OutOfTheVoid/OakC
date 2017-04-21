#include <Parsing/Language/OakDecoratorTagConstructor.h>
#include <Parsing/Language/OakLoopLabelConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakDecoratorTagConstructor OakDecoratorTagConstructor :: Instance;
	
OakDecoratorTagConstructor :: OakDecoratorTagConstructor ()
{
}

OakDecoratorTagConstructor :: ~OakDecoratorTagConstructor ()
{
}

void OakDecoratorTagConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_DecoratorOpen )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * DecoratorData = new ElementData ();
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		delete DecoratorData;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorProvokingToken = CurrentToken;
		Output.ErrorSuggestion = "Expected identifier in decorator tag!";
		
		return;
		
	}
	
	DecoratorData -> ID = CurrentToken -> GetSource ();
	
	CurrentToken = Input.Tokens [ 2 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_SquareBracket_Close )
	{
		
		delete DecoratorData;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorProvokingToken = CurrentToken;
		Output.ErrorSuggestion = "Expected closing bracket for decorator tag!";
		
		return;
		
	}
	
	ASTElement * DecoratorElement = new ASTElement ();
	
	DecoratorElement -> SetTag ( OakASTTags :: kASTTag_DecoratorTag );
	DecoratorElement -> SetData ( DecoratorData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.ConstructedElement = DecoratorElement;
	Output.TokensConsumed = 3;
	
}

void OakDecoratorTagConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
