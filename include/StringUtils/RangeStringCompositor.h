#ifndef STRINGUTILS_RANGESTRINGCOMPOSITOR_H
#define STRINGUTILS_RANGESTRINGCOMPOSITOR_H

#include <string>
#include <stdint.h>

#include <vector>

class RangeStringCompositor
{
public:
	
	/// Constructor
	RangeStringCompositor ();
	/// Destructor
	~RangeStringCompositor ();
	
	/// Add a character range. (Includes all charachters from LowChar to HighChar inclusive)
	void AddRange ( char32_t LowChar, char32_t HighChar );
	/// Adds an individual charachter to the string
	void AddIndividual ( char32_t Char );
	
	/// Adds all the charachters in Inherited
	void AddInherited ( RangeStringCompositor & Parent );
	
	/// Clears the list of individual and rage elements.
	void Clear ();
	
	/// Creates the string containing every added range and individual charachter.
	std :: u32string CompositeString ();
	
private:
	
	typedef struct
	{
		
		char32_t Low;
		char32_t High;
		
	} CharRange;
	
	std :: vector <CharRange> Ranges;
	std :: vector <char32_t> Individuals;
	
};

#endif
