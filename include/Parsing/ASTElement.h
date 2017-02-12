#ifndef PARSING_ASTELEMENT_H
#define PARSING_ASTELEMENT_H

#include <Tokenization/Token.h>

#include <vector>
#include <stdint.h>

class ASTElement
{
public:
	
	ASTElement ();
	~ASTElement ();
	
	void AddSubElement ( ASTElement * Element );
	void AddTokenSection ( const Token ** Tokens, uint64_t TokenCount );
	
	void ReplaceSubElement ( uint64_t Index, ASTElement * Element );
	void ReplaceSubElements ( uint64_t Index, uint64_t Count, ASTElement * Element );
	
	void RemoveSubElement ( uint64_t Index );
	
	void SetData ( void * Data, void ( * DataDestructor ) ( void * Data ) );
	const void * GetData () const;
	void * GetData ();
	
	void SetTag ( uint64_t Tag );
	uint64_t GetTag () const;
	
	uint64_t GetSubElementCount () const;
	const ASTElement * GetSubElement ( uint64_t Index ) const;
	ASTElement * GetSubElement ( uint64_t Index );
	
	uint64_t GetTokenSectionCount () const;
	uint64_t GetTokenCount ( uint64_t Section ) const;
	const Token * GetToken ( uint64_t Section, uint64_t Index ) const;
	
private:
	
	typedef struct
	{
		
		const Token ** Tokens;
		
		uint64_t TokenCount;
		
	} TokenSection;
	
	uint64_t Tag;
	
	void * Data;
	void ( * DataDestructor ) ( void * Data );
	
	std :: vector <ASTElement *> SubElements;
	std :: vector <TokenSection> TokenSections;
	
};

#endif
