#include <Parsing/Language/OakEnumBranchConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakReferenceTypeConstructor.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakVoidTypeConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakEnumBranchConstructor OakEnumBranchConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakEnumBranchConstructor_TypeGroupEntries [] =
{
	
	{ & OakVoidTypeConstructor :: Instance, 0 },
	{ & OakReferenceTypeConstructor :: Instance, 0 },
	
	{ & OakNamespacedTemplatedTypeNameConstructor :: Instance, 0 },
	{ & OakNamespacedTypeNameConstructor :: Instance, 1 },
	{ & OakTemplatedTypeNameConstructor :: Instance, 1 },
	{ & OakBareTypeNameConstructor :: Instance, 2 },
	
};

OakEnumBranchConstructor :: OakEnumBranchConstructor ():
	TypeGroup ( _OakEnumBranchConstructor_TypeGroupEntries, 6 )
{
}

OakEnumBranchConstructor :: ~OakEnumBranchConstructor ()
{
}

void OakEnumBranchConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	ElementData * EnumBranchData = new ElementData ();
	
	EnumBranchData -> Name = Input.Tokens [ 0 ] -> GetSource ();
	EnumBranchData -> HasData = false;
	
	ASTElement * EnumBranchElement = new ASTElement ();
	
	EnumBranchElement -> SetTag ( OakASTTags :: kASTTag_EnumBranch );
	EnumBranchElement -> SetData ( EnumBranchData, & ElementDataDestructor );
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		EnumBranchElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
		
		Output.Accepted = true;
		Output.TokensConsumed = 1;
		Output.ConstructedElement = EnumBranchElement;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		
		EnumBranchElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
		
		Output.Accepted = true;
		Output.TokensConsumed = 1;
		Output.ConstructedElement = EnumBranchElement;
		
		return;
		
	}
	
	EnumBranchData -> HasData = true;
	
	EnumBranchElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( EnumBranchElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete EnumBranchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected type name after colon in enum branch";
		Output.ErrorProvokingToken = Input.Tokens [ 2 ];
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete EnumBranchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	bool TemplateError = false;
	
	ASTElement * TypeElement = EnumBranchElement -> GetSubElement ( EnumBranchElement -> GetSubElementCount () - 1 );
	
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
		
		delete EnumBranchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Unexpected closing triangle bracket after return type";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = EnumBranchElement;
	
}

void OakEnumBranchConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
