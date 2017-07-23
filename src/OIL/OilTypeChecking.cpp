#include <OIL/OilTypeChecking.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTrait.h>
#include <OIL/OilTemplateSpecification.h>

OilTypeChecking_CheckResult OilTypeChecking_TypeImplementsTrait ( const OilTypeRef & TraitTypeRef, const OilTypeRef & ImplementorTypeRef )
{
	
	if ( ( ! TraitTypeRef.IsResolved () ) || ( ! ImplementorTypeRef.IsResolved () ) )
		return kOilTypeChecking_CheckResult_Incomplete;
	
	if ( ! ImplementorTypeRef.IsResolvedAsType () )
	
}
