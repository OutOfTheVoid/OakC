#ifndef OIL_OILTYPECHECKING_H
#define OIL_OILTYPECHECKING_H

class OilTypeDefinition;
class OilTrait;
class OilTemplateSpecification;

enum OilTypeChecking_CheckResult
{
	
	kOilTypeChecking_CheckResult_True,
	kOilTypeChecking_CheckResult_False,
	kOilTypeChecking_CheckResult_Incomplete,
	kOilTypeChecking_CheckResult_Error
	
}

OilTypeChecking_CheckResult OilTypeChecking_TypeImplementsTrait ( const OilTypeRef & TraitTypeRef, const OilTypeRef & ImplementorTypeRef );

#endif
