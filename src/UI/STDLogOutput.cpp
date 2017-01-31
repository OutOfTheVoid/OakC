#include <UI/STDLogOutput.h>

#include <iostream>

void STDLogOutput :: Write ( const std :: string & Output )
{
	
	std :: cout << Output;
	
}

void STDLogOutput :: WriteError ( const std :: string & Output )
{
	
	std :: cerr << Output;
	
}
