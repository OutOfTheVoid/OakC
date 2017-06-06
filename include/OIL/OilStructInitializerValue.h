#ifndef OIL_OILSTRUCTINITIALIZERVALUE_H
#define OIL_OILSTRUCTINITIALIZERVALUE_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilExpression;

class OilStructInitializerValue
{
public:
	
	OilStructInitializerValue ( const SourceRef & Ref, const std :: u32string & MemberName, OilExpression * ValueExpression );
	~OilStructInitializerValue ();
	
	const std :: u32string & GetMemberName () const;
	
	const OilExpression * GetValueExpression () const;
	OilExpression * GetValueExpression ();
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilExpression * ValueExpression;
	
	const std :: u32string MemberName;
	
	const SourceRef Ref;
	
};

#endif
