#include <Parsing/Language/OakImplementDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakFunctionDefinitionConstructor.h>
#include <Parsing/Language/OakMethodDefinitionConstructor.h>

#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakBareTypeNameConstructor.h>

#include <Parsing/Language/OakVoidTypeConstructor.h>

#include <Parsing/Language/OakNamespacedTemplatedTraitNameConstructor.h>
#include <Parsing/Language/OakNamespacedTraitNameConstructor.h>
#include <Parsing/Language/OakTemplatedTraitNameConstructor.h>
#include <Parsing/Language/OakBareTraitNameConstructor.h>
#include <Parsing/Language/OakWhereClauseConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakImplementDefinitionConstructor OakImplementDefinitionConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakImplementDefinitionConstructor_ImplementChildrenConstructionGroupEntries [] =
{
	
	{ & OakMethodDefinitionConstructor :: Instance, 1 },
	{ & OakFunctionDefinitionConstructor :: Instance, 0 },
	
};

ASTConstructionGroup :: StaticInitEntry _OakImplementDefinitionConstructor_ImplementedTypeConstructionGroupEntries [] =
{
	
	{ & OakNamespacedTemplatedTypeNameConstructor :: Instance, 0 },
	{ & OakNamespacedTypeNameConstructor :: Instance, 1 },
	{ & OakTemplatedTypeNameConstructor :: Instance, 1 },
	{ & OakBareTypeNameConstructor :: Instance, 2 },
	
	{ & OakVoidTypeConstructor :: Instance, 2 },
	
};

ASTConstructionGroup :: StaticInitEntry _OakImplementDefinitionConstructor_ImplementedTraitConstructionGroupEntries [] =
{
	
	{ & OakNamespacedTemplatedTraitNameConstructor :: Instance, 0 },
	{ & OakNamespacedTraitNameConstructor :: Instance, 1 },
	{ & OakTemplatedTraitNameConstructor :: Instance, 1 },
	{ & OakBareTraitNameConstructor :: Instance, 2 },
	
};

ASTConstructionGroup :: StaticInitEntry _OakImplementDefinitionConstructor_WhereClauseGroupEntries [] =
{
	
	{ & OakWhereClauseConstructor :: Instance, 0 },
	
};

OakImplementDefinitionConstructor :: OakImplementDefinitionConstructor ():
	ImplementChildrenConstructionGroup ( _OakImplementDefinitionConstructor_ImplementChildrenConstructionGroupEntries, 2 ),
	TypeNameGroup ( _OakImplementDefinitionConstructor_ImplementedTypeConstructionGroupEntries, 4 ),
	TraitNameGroup ( _OakImplementDefinitionConstructor_ImplementedTraitConstructionGroupEntries, 4 ),
	WhereClauseGroup ( _OakImplementDefinitionConstructor_WhereClauseGroupEntries, 1 )
{
}

OakImplementDefinitionConstructor :: ~OakImplementDefinitionConstructor ()
{
}

void OakImplementDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Implement ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * ImplementData = new ElementData ();
	ImplementData -> ImplementsTrait = false;
	ImplementData -> HasWhereClause = false;
	
	ASTElement * ImplementElement = new ASTElement ();
	ImplementElement -> SetTag ( OakASTTags :: kASTTag_ImplementDefinition );
	ImplementElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	ImplementElement -> SetData ( ImplementData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( TypeNameGroup.TryConstruction ( ImplementElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( Error )
		{
			
			delete ImplementElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		delete ImplementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected type to implement";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	if ( Error )
	{
			
		delete ImplementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_For ) )
	{
		
		TokenCount --;
		
		ImplementData -> ImplementsTrait = true;
		
		if ( TraitNameGroup.TryConstruction ( ImplementElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
		{
			
			delete ImplementElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected trait name after for keyword in implement definition";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ];
			
			return;
			
		}
		
		if ( Error )
		{
			
			delete ImplementElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete ImplementElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected opening curly bracket in implement definition";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
	}
	
	if ( WhereClauseGroup.TryConstruction ( ImplementElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		if ( Error )
		{
			
			delete ImplementElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete ImplementElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected opening curly bracket in implement definition";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
			
			return;
			
		}
		
		ImplementData -> HasWhereClause = true;
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
	}
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		delete ImplementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected opening curly bracket in implement definition";
		Output.ErrorProvokingToken = CurrentToken;
		
	}
	
	TokenCount --;
	
	ImplementChildrenConstructionGroup.TryConstruction ( ImplementElement, 0xFFFFFFFFFFFFFFFF, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
	
	if ( Error )
	{
		
		delete ImplementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete ImplementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly brace at end of implement definition";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete ImplementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly brace at end of implement definition";
		Output.ErrorProvokingToken = CurrentToken;
		
	}
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = ImplementElement;
	
}

void OakImplementDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * ImplementDefinitionInstance = reinterpret_cast <ElementData *> ( Data );
	
	delete ImplementDefinitionInstance;
	
}