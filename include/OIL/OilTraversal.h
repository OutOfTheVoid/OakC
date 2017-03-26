#ifndef OIL_OILTRAVERSAL_H
#define OIL_OILTRAVERSAL_H

class OilNamespaceDefinition;
class OilTypeDefinition;
class OilTraitDefinition;
class OilTypeRef;

#include <string>

OilTypeDefinition * FindTypeDefinition ( const OilTypeRef & TypeRef, OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );
const OilTypeDefinition * FindTypeDefinition ( const OilTypeRef & TypeRef, const OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch );

OilNamespaceDefinition * OilFindParentallyContainedNamespace ( OilNamespaceDefinition & SearchLeaf, const std :: u32string & Name );
const OilNamespaceDefinition * OilFindParentallyContainedNamespace ( const OilNamespaceDefinition & SearchLeaf, const std :: u32string & Name );

bool OilFindAndBuildAbsoluteTraitNamePath ( std :: vector <std :: u32string> & AbsoluteNamePath, OilTypeRef & Type, OilNamespaceDefinition & CurrentNS, OilTraitDefinition *& TraitOut, bool & TemplateMismatch );

#endif
