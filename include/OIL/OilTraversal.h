#ifndef OIL_OILTRAVERSAL_H
#define OIL_OILTRAVERSAL_H

class OilNamespaceDefinition;
class OilTypeDefinition;
class OilTraitDefinition;
class OilTypeRef;
class OilTypeAlias;

#include <string>
#include <vector>

OilTypeDefinition * FindTypeDefinition ( const OilTypeRef & TypeRef, OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );
const OilTypeDefinition * FindTypeDefinition ( const OilTypeRef & TypeRef, const OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );

OilTypeAlias * FindTypeAlias ( const OilTypeRef & TypeRef, OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );
const OilTypeAlias * FindTypeAlias ( const OilTypeRef & TypeRef, const OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );

OilTraitDefinition * FindTraitDefinition ( const OilTypeRef & TypeRef, OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );
const OilTraitDefinition * FindTraitDefinition ( const OilTypeRef & TypeRef, const OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );

void BuildAbsoluteNamePath_Trait ( std :: vector <std :: u32string> & AbsolutePath, const OilTraitDefinition & Trait );
void BuildAbsoluteNamePath_TypeDefinition ( std :: vector <std :: u32string> & AbsolutePath, const OilTypeDefinition & Type );

OilNamespaceDefinition * OilFindParentallyContainedNamespace ( OilNamespaceDefinition & SearchLeaf, const std :: u32string & Name );
const OilNamespaceDefinition * OilFindParentallyContainedNamespace ( const OilNamespaceDefinition & SearchLeaf, const std :: u32string & Name );

#endif
