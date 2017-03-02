#include <Parsing/Language/OakStructBindingConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakPointerTypeConstructor.h>
#include <Parsing/Language/OakReferenceTypeConstructor.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakStructBindingConstructor OakStructBindingConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakStructBindingConstructor_TypeGroupEntries [] =
{
	
	{ & OakPointerTypeConstructor :: Instance, 0 },
	{ & OakReferenceTypeConstructor :: Instance, 0 },
	
	{ & OakNamespacedTemplatedTypeNameConstructor :: Instance, 0 },
	{ & OakNamespacedTypeNameConstructor :: Instance, 1 },
	{ & OakTemplatedTypeNameConstructor :: Instance, 1 },
	{ & OakBareTypeNameConstructor :: Instance, 2 },
	
};

OakStructBindingConstructor :: OakStructBindingConstructor ():
	TypeGroup ( _OakStructBindingConstructor_TypeGroupEntries, 6 )
{
}

OakStructBindingConstructor :: ~OakStructBindingConstructor ()
{
}

void OakStructBindingConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Bind ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 2 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * StructBindingData = new ElementData ();
	
	StructBindingData -> Name = Input.Tokens [ 1 ] -> GetSource ();
	
	ASTElement * StructBindingElement = new ASTElement ();
	
	StructBindingElement -> SetTag ( OakASTTags :: kASTTag_StructBinding );
	StructBindingElement -> AddTokenSection ( & Input.Tokens [ 0 ], 3 );
	StructBindingElement -> SetData ( StructBindingData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 3;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( StructBindingElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete StructBindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected type name after colon in struct binding";
		Output.ErrorProvokingToken = Input.Tokens [ 3 ];
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete StructBindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	// TODO: Make sure types aren't double or triple-templated here.
	
	bool TemplateError = false;
	
	ASTElement * TypeElement = StructBindingElement -> GetSubElement ( StructBindingElement -> GetSubElementCount () - 1 );
	
	if ( TypeElement -> GetTag () == OakASTTags :: kASTTag_PointerType )
	{
		
		OakPointerTypeConstructor :: ElementData * Data = reinterpret_cast <OakPointerTypeConstructor :: ElementData *> ( TypeElement -> GetData () );
		
		if ( Data -> DoubleTemplateClose || Data -> TripleTemplateClose )
			TemplateError = true;
		
	}
	
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
		
		delete StructBindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Unexpected closing triangle bracket after return type";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = StructBindingElement;
	
}

void OakStructBindingConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
