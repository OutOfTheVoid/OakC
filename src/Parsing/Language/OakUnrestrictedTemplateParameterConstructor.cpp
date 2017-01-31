#include <Parsing/Language/OakUnrestrictedTemplateParameterConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

OakUnrestrictedTemplateParameterConstructor :: OakUnrestrictedTemplateParameterConstructor ()
{
}

OakUnrestrictedTemplateParameterConstructor :: ~OakUnrestrictedTemplateParameterConstructor ()
{
}

void OakUnrestrictedTemplateParameterConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	ElementData * ParameterData = new ElementData ();
	
	ParameterData -> Name = CurrentToken -> GetSource ();
	
	ASTElement * ParameterElement = new ASTElement ();
	ParameterElement -> SetTag ( OakASTTags :: kASTTag_UnrestrictedTemplateParameter );
	ParameterElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	ParameterElement -> SetData ( ParameterData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.TokensConsumed = 1;
	Output.ConstructedElement = ParameterElement;
	
}

void OakUnrestrictedTemplateParameterConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
