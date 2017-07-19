#include <Parsing/Language/OakBareTraitNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakBareTraitNameConstructor & OakBareTraitNameConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakBareTraitNameConstructor> ();
	
}

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
	
	uint32_t Offset = 0;
	bool Absolute = false;
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_DoubleColon )
	{
		
		Absolute = true;
		
		if ( Input.AvailableTokenCount < 2 )
		{
			
			Output.Accepted = false;
			
			return;
			
		}
		
		Offset ++;
		
		CurrentToken = Input.Tokens [ Offset ];
		
	}
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Offset ++;
	
	ElementData * NameData = new ElementData ();
	
	NameData -> Name = CurrentToken -> GetSource ();
	NameData -> Absolute = Absolute;
	
	ASTElement * ParameterElement = new ASTElement ();
	ParameterElement -> SetTag ( OakASTTags :: kASTTag_TraitName_Bare );
	ParameterElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	ParameterElement -> SetData ( NameData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.TokensConsumed = Offset;
	Output.ConstructedElement = ParameterElement;
	
}

void OakBareTraitNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}

