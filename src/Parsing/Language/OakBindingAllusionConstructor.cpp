#include <Parsing/Language/OakBindingAllusionConstructor.h>
#include <Parsing/Language/OakTemplateSpecificationConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <vector>

#ifndef NULL
	#define NULL nullptr
#endif

OakBindingAllusionConstructor OakBindingAllusionConstructor :: Instance;

OakBindingAllusionConstructor :: OakBindingAllusionConstructor ():
	TemplateSpecificationGroup ()
{
	
	TemplateSpecificationGroup.AddConstructorCantidate ( & OakTemplateSpecificationConstructor :: Instance, 0 );
	
}

OakBindingAllusionConstructor :: ~OakBindingAllusionConstructor ()
{
}

void OakBindingAllusionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	uint64_t Offset = 0;
	
	std :: vector <std :: u32string> NamespaceChain;
	std :: vector <ASTElement *> NamespaceChainTemplates;
	
	bool DirectGlobalReference = false;
	
	if ( Input.AvailableTokenCount < 1 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_DoubleColon )
	{
		
		DirectGlobalReference = true;
		
		Offset ++;
		
		CurrentToken = Input.Tokens [ Offset ];
		
	}
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	NamespaceChain.push_back ( CurrentToken -> GetSource () );
	
	Offset ++;
	
	ASTElement * AllusionElement = new ASTElement ();
	AllusionElement -> SetTag ( OakASTTags :: kASTTag_BindingAllusion );
	AllusionElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	
	bool Error = false;
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	ASTElement * TemplateElement = TemplateSpecificationGroup.TryConstructSingleNoParent ( OakASTTags :: kASTTag_BindingAllusion, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
	
	if ( Error )
	{
		
		for ( uint32_t I = 0; I < NamespaceChainTemplates.size (); I ++ )
			if ( NamespaceChainTemplates [ I ] != NULL )
				delete NamespaceChainTemplates [ I ];
		
		delete AllusionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TemplateElement != NULL )
	{
		
		const OakTemplateSpecificationConstructor :: ElementData * TemplateData = reinterpret_cast <const OakTemplateSpecificationConstructor :: ElementData *> ( TemplateElement -> GetData () );
		
		if ( TemplateData -> TripleTemplateClose || TemplateData -> DoubleTemplateClose )
		{
			
			delete TemplateElement;
			
			for ( uint32_t I = 0; I < NamespaceChainTemplates.size (); I ++ )
				if ( NamespaceChainTemplates [ I ] != NULL )
					delete NamespaceChainTemplates [ I ];
				
			delete AllusionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Unexpected closing triangle bracket at end of template specification";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ];
			
			return;
			
		}
		
	}
	
	NamespaceChainTemplates.push_back ( TemplateElement );
	
	while ( TokenCount > 1 )
	{
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_DoubleColon )
			break;
		
		TokenCount --;
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		TokenCount --;
		
		if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
		{
			
			for ( uint32_t I = 0; I < NamespaceChainTemplates.size (); I ++ )
				if ( NamespaceChainTemplates [ I ] != NULL )
					delete NamespaceChainTemplates [ I ];
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected identifier after namespace access operator";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		AllusionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount - 2 ], 2 );
		
		NamespaceChain.push_back ( CurrentToken -> GetSource () );
		
		TemplateElement = TemplateSpecificationGroup.TryConstructSingleNoParent ( OakASTTags :: kASTTag_BindingAllusion, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
		
		if ( Error )
		{
			
			for ( uint32_t I = 0; I < NamespaceChainTemplates.size (); I ++ )
				if ( NamespaceChainTemplates [ I ] != NULL )
					delete NamespaceChainTemplates [ I ];
				
			delete AllusionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TemplateElement != NULL )
		{
			
			const OakTemplateSpecificationConstructor :: ElementData * TemplateData = reinterpret_cast <const OakTemplateSpecificationConstructor :: ElementData *> ( TemplateElement -> GetData () );
			
			if ( TemplateData -> TripleTemplateClose || TemplateData -> DoubleTemplateClose )
			{
				
				delete TemplateElement;
				
				for ( uint32_t I = 0; I < NamespaceChainTemplates.size (); I ++ )
					if ( NamespaceChainTemplates [ I ] != NULL )
						delete NamespaceChainTemplates [ I ];
					
				delete AllusionElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = "Unexpected closing triangle bracket at end of template specification";
				Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ];
				
				return;
				
			}
			
		}
		
		NamespaceChainTemplates.push_back ( TemplateElement );
		
	}
	
	ElementData * AllusionData = new ElementData ();
	
	AllusionElement -> SetData ( AllusionData, & ElementDataDestructor );
	
	AllusionData -> DirectGlobalReference = DirectGlobalReference;
	
	AllusionData -> IdentListLength = NamespaceChain.size ();
	AllusionData -> IdentList = new AllusionName [ NamespaceChain.size () ];
	
	for ( uint32_t I = 0; I < NamespaceChain.size (); I ++ )
	{
		
		AllusionData -> IdentList [ I ].Name = NamespaceChain [ I ];
		AllusionData -> IdentList [ I ].Templated = NamespaceChainTemplates [ I ] != NULL;
		AllusionData -> IdentList [ I ].TemplateSpecificationElement = NamespaceChainTemplates [ I ];
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = AllusionElement;
	
}

void OakBindingAllusionConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * EData = reinterpret_cast <ElementData *> ( Data );
	
	if ( EData -> IdentList != NULL )
		delete [] EData -> IdentList;
	
	delete EData;
	
}

