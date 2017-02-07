#include <Parsing/Language/OakReferenceTypeConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakPointerTypeConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

OakReferenceTypeConstructor _OakReferenceTypeConstructor_OakReferenceTypeConstructorInstance;
OakPointerTypeConstructor _OakReferenceTypeConstructor_OakPointerTypeConstructorInstance;

OakBareTypeNameConstructor _OakReferenceTypeConstructor_OakBareTypeNameConstructorInstance;
OakTemplatedTypeNameConstructor _OakReferenceTypeConstructor_OakTemplatedTypeNameConstructorInstance;
OakNamespacedTypeNameConstructor _OakReferenceTypeConstructor_OakNamespacedTypeNameConstructorInstance;
OakNamespacedTemplatedTypeNameConstructor _OakReferenceTypeConstructor_OakNamespacedTemplatedTypeNameConstructorInstance;

OakReferenceTypeConstructor :: OakReferenceTypeConstructor ():
	TypeGroup ()
{
	
	TypeGroup.AddConstructorCantidate ( & _OakReferenceTypeConstructor_OakReferenceTypeConstructorInstance, 0 );
	TypeGroup.AddConstructorCantidate ( & _OakReferenceTypeConstructor_OakPointerTypeConstructorInstance, 0 );
	
	TypeGroup.AddConstructorCantidate ( & _OakReferenceTypeConstructor_OakNamespacedTemplatedTypeNameConstructorInstance, 0 );
	TypeGroup.AddConstructorCantidate ( & _OakReferenceTypeConstructor_OakNamespacedTypeNameConstructorInstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakReferenceTypeConstructor_OakTemplatedTypeNameConstructorInstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakReferenceTypeConstructor_OakBareTypeNameConstructorInstance, 2 );
	
}

OakReferenceTypeConstructor :: ~OakReferenceTypeConstructor ()
{
}

void OakReferenceTypeConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Ampersand )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * ReferenceTypeData = new ElementData ();
	
	ReferenceTypeData -> Templated = false;
	
	ASTElement * ReferenceTypeElement = new ASTElement ();
	
	ReferenceTypeElement -> SetTag ( OakASTTags :: kASTTag_ReferenceType );
	ReferenceTypeElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	ReferenceTypeElement -> SetData ( ReferenceTypeData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( ReferenceTypeElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete ReferenceTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected type name after ampersand in reference type";
		Output.ErrorProvokingToken = Input.Tokens [ 1 ];
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ReferenceTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	ASTElement * SubTypeElement = ReferenceTypeElement -> GetSubElement ( ReferenceTypeElement -> GetSubElementCount () - 1 );
	uint64_t SubTypeTag = SubTypeElement -> GetTag ();
	
	if ( SubTypeTag == OakASTTags :: kASTTag_ReferenceType )
		ReferenceTypeData -> Templated = reinterpret_cast <ElementData *> ( SubTypeElement -> GetData () ) -> Templated;
	
	if ( SubTypeTag == OakASTTags :: kASTTag_PointerType )
		ReferenceTypeData -> Templated = reinterpret_cast <OakPointerTypeConstructor :: ElementData *> ( SubTypeElement -> GetData () ) -> Templated;
	
	if ( SubTypeTag == OakASTTags :: kASTTag_TypeName_Templated )
		ReferenceTypeData -> Templated = true;
	
	if ( SubTypeTag == OakASTTags :: kASTTag_TypeName_NamespacedTemplated )
		ReferenceTypeData -> Templated = true;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = ReferenceTypeElement;
	
}

void OakReferenceTypeConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
