#include <Parsing/Language/OakBareTraitNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakBareTraitNameConstructor OakBareTraitNameConstructor :: Instance;

OakBareTraitNameConstructor :: OakBareTraitNameConstructor ()
{	
}

OakBareTraitNameConstructor :: ~OakBareTraitNameConstructor ()
{	
}

void OakBareTraitNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 1 )
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
	
	ElementData * NameData = new ElementData ();
	
	NameData -> Name = CurrentToken -> GetSource ();
	
	ASTElement * ParameterElement = new ASTElement ();
	ParameterElement -> SetTag ( OakASTTags :: kASTTag_TraitName_Bare );
	ParameterElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	ParameterElement -> SetData ( NameData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.TokensConsumed = 1;
	Output.ConstructedElement = ParameterElement;
	
}

void OakBareTraitNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}

