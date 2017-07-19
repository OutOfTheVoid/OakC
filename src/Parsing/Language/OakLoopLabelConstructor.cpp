#include <Parsing/Language/OakLoopLabelConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakLoopLabelConstructor & OakLoopLabelConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakLoopLabelConstructor> ();
	
}

OakLoopLabelConstructor :: OakLoopLabelConstructor ()
{
}

OakLoopLabelConstructor :: ~OakLoopLabelConstructor ()
{
}
	
void OakLoopLabelConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_BackTick )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected valid identifier name for loop label";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ElementData * LabelData = new ElementData ();
	
	LabelData -> Label = CurrentToken -> GetSource ();
	
	ASTElement * LoopLabel = new ASTElement ();
	
	LoopLabel -> SetTag ( OakASTTags :: kASTTag_LoopLabel );
	LoopLabel -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	LoopLabel -> SetData ( LabelData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.ConstructedElement = LoopLabel;
	Output.TokensConsumed = 2;
	
}
	
void OakLoopLabelConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
