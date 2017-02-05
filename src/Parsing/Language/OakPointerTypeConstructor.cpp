#include <Parsing/Language/OakPointerTypeConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakSelfParameterConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

OakPointerTypeConstructor _OakPointerTypeConstructor_OakPointerTypeConstructorInstance;

OakBareTypeNameConstructor _OakPointerTypeConstructor_OakBareTypeNameConstructorInstance;
OakTemplatedTypeNameConstructor _OakPointerTypeConstructor_OakTemplatedTypeNameConstructorInstance;
OakNamespacedTypeNameConstructor _OakPointerTypeConstructor_OakNamespacedTypeNameConstructorInstance;
OakNamespacedTemplatedTypeNameConstructor _OakPointerTypeConstructor_OakNamespacedTemplatedTypeNameConstructorInstance;

OakSelfParameterConstructor _OakPointerTypeConstructor_OakSelfParameterConstructorInstance;

OakPointerTypeConstructor :: OakPointerTypeConstructor ():
	TypeGroup ()
{
	
	TypeGroup.AddConstructorCantidate ( & _OakPointerTypeConstructor_OakPointerTypeConstructorInstance, 0 );
	
	TypeGroup.AddConstructorCantidate ( & _OakPointerTypeConstructor_OakNamespacedTemplatedTypeNameConstructorInstance, 0 );
	TypeGroup.AddConstructorCantidate ( & _OakPointerTypeConstructor_OakNamespacedTypeNameConstructorInstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakPointerTypeConstructor_OakTemplatedTypeNameConstructorInstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakPointerTypeConstructor_OakBareTypeNameConstructorInstance, 2 );
	
	TypeGroup.AddConstructorCantidate ( & _OakPointerTypeConstructor_OakSelfParameterConstructorInstance, 3 );
	
}

OakPointerTypeConstructor :: ~OakPointerTypeConstructor ()
{
}

void OakPointerTypeConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Star )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * PointerTypeData = new ElementData ();
	
	PointerTypeData -> Templated = false;
	
	ASTElement * PointerTypeElement = new ASTElement ();
	
	PointerTypeElement -> SetTag ( OakASTTags :: kASTTag_PointerType );
	PointerTypeElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	PointerTypeElement -> SetData ( PointerTypeData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( PointerTypeElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete PointerTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected type name after star in pointer type";
		Output.ErrorProvokingToken = Input.Tokens [ 1 ];
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete PointerTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	ASTElement * SubTypeElement = PointerTypeElement -> GetSubElement ( PointerTypeElement -> GetSubElementCount () - 1 );
	uint64_t SubTypeTag = SubTypeElement -> GetTag ();
	
	if ( SubTypeTag == OakASTTags :: kASTTag_PointerType )
		PointerTypeData -> Templated = reinterpret_cast <ElementData *> ( SubTypeElement -> GetData () ) -> Templated;
	
	if ( SubTypeTag == OakASTTags :: kASTTag_TypeName_Templated )
		PointerTypeData -> Templated = true;
	
	if ( SubTypeTag == OakASTTags :: kASTTag_TypeName_NamespacedTemplated )
		PointerTypeData -> Templated = true;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = PointerTypeElement;
	
}

void OakPointerTypeConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
