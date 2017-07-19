#ifndef PARSING_ASTCONSTRUCTIONGROUP_H
#define PARSING_ASTCONSTRUCTIONGROUP_H

#include <Parsing/ASTElement.h>
#include <Parsing/IASTConstructor.h>

#include <Tokenization/Token.h>

#include <initializer_list>

class ASTConstructionGroup
{
public:
	
	typedef struct
	{
		
		const IASTConstructor * Cantidate;
		uint32_t Priority;
		
	} StaticInitEntry;
	
	ASTConstructionGroup ();
	ASTConstructionGroup ( std :: initializer_list <StaticInitEntry> EntryList );
	ASTConstructionGroup ( StaticInitEntry * EntryList, uint32_t EntryCount );
	
	~ASTConstructionGroup ();
	
	void AddConstructorCantidate ( const IASTConstructor * Cantidate, uint32_t Priority );
	
	uint64_t TryConstruction ( ASTElement * RootElement, uint64_t SubElementLimit, bool & Error, std :: string & ErrorSuggestion, const Token * & ErrorProvokingToken, const Token ** TokenList, uint64_t & AvailableTokens ) const;
	ASTElement *  TryConstructSingleNoParent ( uint64_t DummyParentTag, bool & Error, std :: string & ErrorSuggestion, const Token * & ErrorProvokingToken, const Token ** TokenList, uint64_t & AvailableTokens ) const;
	
private:
	
	typedef struct
	{
		
		const IASTConstructor * Cantidate;
		uint32_t Priority;
		
	} ConstructorRecord;
	
	std :: vector <ConstructorRecord> Constructors;
	
};

#endif
