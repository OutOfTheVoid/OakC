#include <Parsing/Language/OakTemplateSpecificationConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

OakTemplateSpecificationConstructor OakTemplateSpecificationConstructor :: Instance;

OakTemplateSpecificationConstructor :: OakTemplateSpecificationConstructor ():
	ParameterGroup ()
{
	
	ParameterGroup.AddConstructorCantidate ( & OakTemplatedTypeNameConstructor :: Instance, 1 );
	ParameterGroup.AddConstructorCantidate ( & OakBareTypeNameConstructor :: Instance, 2 );
	
}

OakTemplateSpecificationConstructor :: ~OakTemplateSpecificationConstructor ()
{
}

void OakTemplateSpecificationConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	ASTElement * TemplateSpecificationElement = new ASTElement ();
	TemplateSpecificationElement -> SetTag ( OakASTTags :: kASTTag_TemplateSpecification );
	TemplateSpecificationElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	TemplateSpecificationElement -> SetData ( TemplateData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	while ( ParameterGroup.TryConstruction ( TemplateSpecificationElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		ASTElement * ParameterElement = TemplateSpecificationElement -> GetSubElement ( TemplateSpecificationElement -> GetSubElementCount () - 1 );
		
		
		// Any template specification element which may be double-closed
		if ( ParameterElement -> GetTag () == OakASTTags :: kASTTag_TypeName_Templated )
		{
			
			OakTemplatedTypeNameConstructor :: ElementData * Data = reinterpret_cast <OakTemplatedTypeNameConstructor :: ElementData *> ( ParameterElement -> GetData () );
			
			if ( Data -> DoubleTemplateClose )
			{
				
				Output.Accepted = true;
				Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
				Output.ConstructedElement = TemplateSpecificationElement;
				
				return;
				
			}
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete TemplateSpecificationElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected end of template specification";
			Output.ErrorProvokingToken = Input.Tokens [ 0 ];
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_TriangleBracket_Close )
		{
			
			TemplateSpecificationElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			
			TokenCount --;
			
			Output.Accepted = true;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			Output.ConstructedElement = TemplateSpecificationElement;
			
			return;
			
		}
		else if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close )
		{
			
			TemplateData -> DoubleTemplateClose  = true;
			
			TemplateSpecificationElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			
			TokenCount --;
			
			Output.Accepted = true;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			Output.ConstructedElement = TemplateSpecificationElement;
			
			return;
			
		}
		else if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
		{
			
			delete TemplateSpecificationElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected comma or right triangle bracket after parameter template definition";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			return;
			
		}
		
		TemplateSpecificationElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
	}
	
	if ( ConstructionError )
	{
		
		delete TemplateSpecificationElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_TriangleBracket_Close )
	{
		
		TemplateSpecificationElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
		Output.Accepted = true;
		Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
		Output.ConstructedElement = TemplateSpecificationElement;
		
		return;
		
	}
	else if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close )
	{
		
		TemplateData -> DoubleTemplateClose  = true;
		
		TemplateSpecificationElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
		Output.Accepted = true;
		Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
		Output.ConstructedElement = TemplateSpecificationElement;
		
		return;
		
	}
	
	delete TemplateSpecificationElement;
	
	Output.Accepted = false;
	Output.Error = true;
	Output.ErrorSuggestion = "Expected closing triangle bracket at end of template definition";
	Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
}

void OakTemplateSpecificationConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
