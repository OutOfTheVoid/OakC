#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Parsing/Language/OakUnrestrictedTemplateParameterConstructor.h>
#include <Parsing/Language/OakRestrictedTemplateParameterConstructor.h>

#include <Logging/Logging.h>

//TODO: Finish

OakRestrictedTemplateParameterConstructor _OakTemplateDefinitionConstructor_OakRestrictedTemplateParameterConstructorInstance;
OakUnrestrictedTemplateParameterConstructor _OakTemplateDefinitionConstructor_OakUnrestrictedTemplateParameterConstructorInstance;

OakTemplateDefinitionConstructor :: OakTemplateDefinitionConstructor ():
	ParameterGroup ()
{
	
	// TODO: Add template parameter constructors
	ParameterGroup.AddConstructorCantidate ( & _OakTemplateDefinitionConstructor_OakRestrictedTemplateParameterConstructorInstance, 0 );
	ParameterGroup.AddConstructorCantidate ( & _OakTemplateDefinitionConstructor_OakUnrestrictedTemplateParameterConstructorInstance, 1 );
	
}

OakTemplateDefinitionConstructor :: ~OakTemplateDefinitionConstructor ()
{
}

void OakTemplateDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_TriangleBracket_Open )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * TemplateData = new ElementData ();
	
	TemplateData -> DoubleTemplateClose = false;
	
	ASTElement * TemplateDefinitionElement = new ASTElement ();
	TemplateDefinitionElement -> SetTag ( OakASTTags :: kASTTag_TemplateDefinition );
	TemplateDefinitionElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	TemplateDefinitionElement -> SetData ( TemplateData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	while ( ParameterGroup.TryConstruction ( TemplateDefinitionElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		ASTElement * ParameterElement = TemplateDefinitionElement -> GetSubElement ( TemplateDefinitionElement -> GetSubElementCount () - 1 );
		
		if ( ParameterElement -> GetTag () == OakASTTags :: kASTTag_RestrictedTemplateParameter )
		{
			
			OakRestrictedTemplateParameterConstructor :: ElementData * Data = reinterpret_cast <OakRestrictedTemplateParameterConstructor :: ElementData *> ( ParameterElement -> GetData () );
			
			if ( Data -> DoubleTemplateClose )
			{
				
				Output.Accepted = true;
				Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
				Output.ConstructedElement = TemplateDefinitionElement;
				
				return;
				
			}
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete TemplateDefinitionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected end of template definition";
			Output.ErrorProvokingToken = Input.Tokens [ 0 ];
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_TriangleBracket_Close )
		{
			
			TemplateDefinitionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			
			TokenCount --;
			
			Output.Accepted = true;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			Output.ConstructedElement = TemplateDefinitionElement;
			
			return;
			
		}
		else if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_TriangleBracket_Close )
		{
			
			TemplateData -> DoubleTemplateClose  = true;
			
			TemplateDefinitionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			
			TokenCount --;
			
			Output.Accepted = true;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			Output.ConstructedElement = TemplateDefinitionElement;
			
			return;
			
		}
		else if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
		{
			
			delete TemplateDefinitionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected comma or right triangle bracket after parameter template definition";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			return;
			
		}
		
		TemplateDefinitionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
	}
	
	if ( ConstructionError )
	{
		
		delete TemplateDefinitionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_TriangleBracket_Close )
	{
		
		TemplateDefinitionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
		Output.Accepted = true;
		Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
		Output.ConstructedElement = TemplateDefinitionElement;
		
		return;
		
	}
	else if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close )
	{
		
		TemplateData -> DoubleTemplateClose  = true;
		
		TemplateDefinitionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
		Output.Accepted = true;
		Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
		Output.ConstructedElement = TemplateDefinitionElement;
		
		return;
		
	}
	
	delete TemplateDefinitionElement;
	
	Output.Accepted = false;
	Output.Error = true;
	Output.ErrorSuggestion = "Expected closing triangle bracket at end of template definition";
	Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
}

void OakTemplateDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
