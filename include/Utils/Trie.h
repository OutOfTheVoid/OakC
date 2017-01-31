#ifndef UTILS_TRIE_H
#define UTILS_TRIE_H

#include <stdint.h>

#ifndef NULL
	#define NULL 0
#endif

template <typename ElementType>
class UTF8Trie
{
public:
	
	UTF8Trie ( ElementType DefaultValue ):
		DefaultValue ( DefaultValue ),
		Root ()
	{
		
		for ( uint32_t I = 0; I < 0x100; I ++ )
			Root.Children [ I ] = NULL;
		
		Root.Element = DefaultValue;
		
	}
	
	~UTF8Trie ()
	{
		
		for (  uint32_t I = 0; I < 0x100; I ++ )
		{
			
			if ( Root.Children [ I ] != NULL )
			{
				
				_Delete ( * Root.Children [ I ] );
				
				Root.Children [ I ] = NULL;
				
			}
			
		}
		
	}
	
	void Set ( const char * Identifier, uint32_t IdentifierLength, ElementType Value )
	{
		
		if ( IdentifierLength == 0 )
			return;
		
		_Set ( Root, Identifier, IdentifierLength, Value );
		
	}
	
	ElementType Get ( const char * Identifier, uint32_t IdentifierLength )
	{
		
		if ( IdentifierLength == 0 )
			return DefaultValue;
		
		return _Get ( Root, Identifier, IdentifierLength );
		
	}
	
private:
	
	typedef struct TrieElement_Struct
	{
		
		struct TrieElement_Struct * Children [ 0x100 ];
		
		ElementType Element;
		
	} TrieElement;
	
	void _Set ( TrieElement & Root, const char * Identifier, uint32_t Length, ElementType Value )
	{
		
		if ( Length == 0 )
		{
			
			Root.Element = Value;
			
			return;
			
		}
		
		TrieElement ** ChildElement = & Root.Children [ static_cast <uint32_t> ( * Identifier ) ];
		
		if ( * ChildElement == NULL )
		{
			
			* ChildElement = new TrieElement ();
			
			for ( uint32_t I = 0; I < 0x100; I ++ )
				( * ChildElement ) -> Children [ I ] = NULL;
			
			( * ChildElement ) -> Element = DefaultValue;
			
		}
		
		_Set ( ** ChildElement, & Identifier [ 1 ], Length - 1, Value );
		
	}
	
	ElementType _Get ( TrieElement & Root, const char * Identifier, uint32_t Length )
	{
		
		if ( Length == 0 )
			return Root.Element;
		
		TrieElement * ChildElement = Root.Children [ * Identifier ];
		
		if ( ChildElement == NULL )
			return DefaultValue;
		
		return _Get ( * ChildElement, & Identifier [ 1 ], Length - 1 );
		
	}
	
	void _Delete ( TrieElement & Root )
	{
		
		for ( uint32_t I = 0; I < 0x100; I ++ )
		{
			
			if ( Root.Children [ I ] != NULL )
				_Delete ( * ( Root.Children [ I ] ) );
			
		}
		
		delete & Root;
		
	}
	
	ElementType DefaultValue;
	
	TrieElement Root;
	
};

#endif
