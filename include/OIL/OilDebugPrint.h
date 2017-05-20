#ifndef OIL_OILDEBUGPRINT_H
#define OIL_OILDEBUGPRINT_H

class OilNamespaceDefinition;

typedef struct
{
	
	bool PrintBuiltins;
	bool HighlightBuiltins;
	bool ShowResolution;
	
} OilPrintOptions;

void OilPrint ( const OilNamespaceDefinition & Root, const OilPrintOptions & PrintOptions );

#endif
