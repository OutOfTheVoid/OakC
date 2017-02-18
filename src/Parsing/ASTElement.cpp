#include <Parsing/ASTElement.h>

#include <Tokenization/ITokenSplitRule.h>

#ifndef NULL
	#define NULL nullptr
#endif

ASTElement :: ASTElement ():
	Tag ( ITokenSplitRule :: kTag_Default ),
	Data ( NULL ),
	DataDestructor ( NULL ),
	SubElements (),
	TokenSections ()
{
}

ASTElement :: ~ASTElement ()
{
	
	for ( uint64_t I = 0; I < SubElements.size (); I ++ )
		delete SubElements [ I ];
	
	SubElements.clear ();
	
	if ( ( Data != NULL ) && ( DataDestructor != NULL ) )
		( * DataDestructor ) ( Data );
	
}

void ASTElement :: AddSubElement ( ASTElement * Element )
{
	
	SubElements.push_back ( Element );
	
}

void ASTElement :: RemoveSubElement ( uint64_t Index )
{
	
	if ( Index >= SubElements.size () )
		return;
	
	SubElements.erase ( SubElements.begin () + Index );
	
}

void ASTElement :: AddTokenSection ( const Token ** Tokens, uint64_t TokenCount )
{
	
	TokenSection Section;
	
	Section.Tokens = Tokens;
	Section.TokenCount = TokenCount;
	
	TokenSections.push_back ( Section );
	
}

void ASTElement :: SetData ( void * Data, void ( * DataDestructor ) ( void * Data ) )
{
	
	if ( ( this -> Data != NULL ) && ( DataDestructor != NULL ) )
		( * DataDestructor ) ( Data );
	
	this -> Data = Data;
	this -> DataDestructor = DataDestructor;
	
}

const void * ASTElement :: GetData () const
{
	
	return Data;
	
}

void * ASTElement :: GetData ()
{
	
	return Data;
	
}

void ASTElement :: SetTag ( uint64_t Tag )
{
	
	this -> Tag = Tag;
	
}

uint64_t ASTElement :: GetTag () const
{
	
	return Tag;
	
}

uint64_t ASTElement :: GetSubElementCount () const
{
	
	return SubElements.size ();
	
}

ASTElement * ASTElement :: GetSubElement ( uint64_t Index )
{
	
	if ( Index >= SubElements.size () )
		return NULL;
	
	return SubElements [ Index ];
	
}

void ASTElement :: ReplaceSubElement ( uint64_t Index, ASTElement * Element )
{
	
	if ( Index >= SubElements.size () )
		return;
	
	ASTElement * Old = SubElements [ Index ];
	SubElements [ Index ] = Element;
	
	delete Old;
	
}

void ASTElement :: ReplaceSubElements ( uint64_t Index, uint64_t Count, ASTElement * Element )
{
	
	Count --;
	
	if ( Index + Count - 1 >= SubElements.size () )
		return;
	
	for ( uint64_t I = Index + 1; I < Index + 1 + Count; I ++ )
		delete SubElements [ I ];
	
	if ( Count != 0 )
		SubElements.erase ( SubElements.begin () + Index + 1, SubElements.begin () + Index + 1 + Count );
	
	ASTElement * Old = SubElements [ Index ];
	SubElements [ Index ] = Element;
	
	delete Old;
	
}

const ASTElement * ASTElement :: GetSubElement ( uint64_t Index ) const
{
	
	if ( Index >= SubElements.size () )
		return NULL;
	
	return SubElements [ Index ];
	
}

uint64_t ASTElement :: GetTokenSectionCount () const
{
	
	return TokenSections.size ();
	
}

uint64_t ASTElement :: GetTokenCount ( uint64_t Section ) const
{
	
	if ( Section >= TokenSections.size () )
		return 0;
	
	return TokenSections [ Section ].TokenCount;
	
}

const Token * ASTElement :: GetToken ( uint64_t Section, uint64_t Index ) const
{
	
	if ( Section >= TokenSections.size () )
		return 0;
	
	if ( Index >= TokenSections [ Section ].TokenCount )
		return NULL;
	
	return TokenSections [ Section ].Tokens [ Index ];
	
}
