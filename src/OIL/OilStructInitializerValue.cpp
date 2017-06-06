#include <OIL/OilStructInitializerValue.h>
#include <OIL/OilExpression.h>

OilStructInitializerValue :: OilStructInitializerValue ( const SourceRef & Ref, const std :: u32string & MemberName, OilExpression * ValueExpression ):
	ValueExpression ( ValueExpression ),
	MemberName ( MemberName ),
	Ref ( Ref )
{
}
	
OilStructInitializerValue :: ~OilStructInitializerValue ()
{
	
	delete ValueExpression;
	
}

const std :: u32string & OilStructInitializerValue :: GetMemberName () const
{
	
	return MemberName;
	
}

const OilExpression * OilStructInitializerValue :: GetValueExpression () const
{
	
	return ValueExpression;
	
}

OilExpression * OilStructInitializerValue :: GetValueExpression ()
{
	
	return ValueExpression;
	
}

const SourceRef & OilStructInitializerValue :: GetSourceRef () const
{
	
	return Ref;
	
}
