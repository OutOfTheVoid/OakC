#ifndef LOGGING_ERRORUTILS_H
#define LOGGING_ERRORUTILS_H

#include <Tokenization/SourceRef.h>

#include <Compilation/CompilationUnit.h>

#include <string>

inline std :: string SourceRefToPositionString ( const SourceRef & Ref )
{
	
	const CompilationUnit * CompUnit = Ref.GetUnit ();
	
	if ( CompUnit == NULL )
		return "";
	
	return CompUnit -> GetFileName () + ":" + std :: to_string ( Ref.GetLine () ) + ":" + std :: to_string ( Ref.GetChar () ) + ": ";
	
}

#endif
