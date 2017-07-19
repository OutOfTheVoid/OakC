#include <Parsing/Language/OakReturnTypeConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakReferenceTypeConstructor.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakVoidTypeConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakReturnTypeConstructor & OakReturnTypeConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakReturnTypeConstructor> ();
	
}

OakReturnTypeConstructor :: OakReturnTypeConstructor ():
	TypeGroup ( 
	{
		
		{ & ( OakReferenceTypeConstructor :: Instance () ), 0 },
		
		{ & ( OakNamespacedTemplatedTypeNameConstructor :: Instance () ), 0 },
		{ & ( OakNamespacedTypeNameConstructor :: Instance () ), 1 },
		{ & ( OakTemplatedTypeNameConstructor :: Instance () ), 1 },
		{ & ( OakBareTypeNameConstructor :: Instance () ), 2 },
		
		{ & ( OakVoidTypeConstructor :: Instance () ), 2 },
		
	} )
{
}

OakReturnTypeConstructor :: ~OakReturnTypeConstructor ()
{
}

void OakReturnTypeConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( Input.Tokens [ 0 ] -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	bool Mutable = false;
	
	if ( OakParsingUtils :: KeywordCheck ( Input.Tokens [ 1 ], OakKeywordTokenTags :: kKeywordAuxTags_Mut ) )
		Mutable = true;
	
	ElementData * ReturnTypeData = new ElementData ();
	
	ReturnTypeData -> Mutable = Mutable;
	
	ASTElement * ReturnTypeElement = new ASTElement ();
	
	ReturnTypeElement -> SetTag ( OakASTTags :: kASTTag_ReturnType );
	ReturnTypeElement -> AddTokenSection ( & Input.Tokens [ 0 ], Mutable ? 2 : 1 );
	ReturnTypeElement -> SetData ( ReturnTypeData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - ( Mutable ? 2 : 1 );
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( ReturnTypeElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( ConstructionError )
		{
			
			delete ReturnTypeElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		delete ReturnTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "expected type name after colon in return type";
		Output.ErrorProvokingToken = Input.Tokens [ 1 ];
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ReturnTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	bool TemplateError = false;
	
	ASTElement * TypeElement = ReturnTypeElement -> GetSubElement ( ReturnTypeElement -> GetSubElementCount () - 1 );
	
	if ( TypeElement -> GetTag () == OakASTTags :: kASTTag_ReferenceType )
	{
		
		OakReferenceTypeConstructor :: ElementData * Data = reinterpret_cast <OakReferenceTypeConstructor :: ElementData *> ( TypeElement -> GetData () );
		
		if ( Data -> DoubleTemplateClose || Data -> TripleTemplateClose )
			TemplateError = true;
		
	}
	
	if ( TypeElement -> GetTag () == OakASTTags :: kASTTag_TypeName_Templated )
	{
		
		OakTemplatedTypeNameConstructor :: ElementData * Data = reinterpret_cast <OakTemplatedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
		
		if ( Data -> DoubleTemplateClose || Data -> TripleTemplateClose )
			TemplateError = true;
		
	}
	
	if ( TypeElement -> GetTag () == OakASTTags :: kASTTag_TypeName_NamespacedTemplated )
	{
		
		OakNamespacedTemplatedTypeNameConstructor :: ElementData * Data = reinterpret_cast <OakNamespacedTemplatedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
		
		if ( Data -> DoubleTemplateClose || Data -> TripleTemplateClose )
			TemplateError = true;
		
	}
	
	if ( TemplateError )
	{
		
		delete ReturnTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Unexpected closing triangle bracket after return type";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.ConstructedElement = ReturnTypeElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}

void OakReturnTypeConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
