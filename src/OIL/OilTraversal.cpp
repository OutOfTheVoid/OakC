#include <OIL/OilTraversal.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTemplateSpecification.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilTraitDefinition.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTypeDefinition * FindTypeDefinition ( const OilTypeRef & TypeRef, OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch )
{
	
	if ( ! TypeRef.IsDirectType () )
		return NULL;
	
	OilTypeDefinition * OutDef = NULL;
	
	if ( ( TypeRef.GetFlags () & OilTypeRef :: kRefFlag_Absolute ) != 0 )
	{
		
		OilNamespaceDefinition * Parent = & ImmediateContainer;
		
		while ( Parent -> GetParent () != NULL )
			Parent = Parent -> GetParent ();
		
		for ( uint32_t I = 0; I < TypeRef.GetNamespaceNameCount (); I ++ )
		{
			
			Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
			
			if ( Parent == NULL )
				return NULL;
			
		}
		
		OilTypeDefinition * OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
		
		if ( OutDef == NULL )
			return NULL;
		
		if ( OutDef -> GetStructDefinition () -> IsTemplated () )
		{
			
			if ( ! TypeRef.IsTemplated () )
			{
				
				TemplateMismatch = true;
				
				return NULL;
				
			}
			
			if ( TypeRef.GetTemplateSpecification () -> GetTypeRefCount () != OutDef -> GetStructDefinition () -> GetTemplateDefinition () -> GetTemplateParameterCount () )
			{
				
				TemplateMismatch = true;
				
				return NULL;
				
			}
			
		}
		
		return OutDef;
		
	}
	else
	{
		
		OilNamespaceDefinition * Parent = & ImmediateContainer;
		
		if ( TypeRef.IsNamespaced () )
		{
			
			Parent = OilFindParentallyContainedNamespace ( * Parent, TypeRef.GetNamespaceName ( 0 ) );
			
			for ( uint32_t I = 1; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					return NULL;
				
			}
			
		}
		
		OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
		
	}
	
	if ( OutDef == NULL )
		return NULL;
	
	if ( OutDef -> GetStructDefinition () -> IsTemplated () )
	{
		
		if ( ! TypeRef.IsTemplated () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
		if ( TypeRef.GetTemplateSpecification () -> GetTypeRefCount () != OutDef -> GetStructDefinition () -> GetTemplateDefinition () -> GetTemplateParameterCount () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
	}
	
	return OutDef;
	
}

const OilTypeDefinition * FindTypeDefinition ( const OilTypeRef & TypeRef, const OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch )
{
	
	if ( ! TypeRef.IsDirectType () )
		return NULL;
	
	const OilTypeDefinition * OutDef = NULL;
	
	if ( ( TypeRef.GetFlags () & OilTypeRef :: kRefFlag_Absolute ) != 0 )
	{
		
		const OilNamespaceDefinition * Parent = & ImmediateContainer;
		
		while ( Parent -> GetParent () != NULL )
			Parent = Parent -> GetParent ();
		
		for ( uint32_t I = 0; I < TypeRef.GetNamespaceNameCount (); I ++ )
		{
			
			Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
			
			if ( Parent == NULL )
				return NULL;
			
		}
		
		const OilTypeDefinition * OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
		
		if ( OutDef == NULL )
			return NULL;
		
		if ( OutDef -> GetStructDefinition () -> IsTemplated () )
		{
			
			if ( ! TypeRef.IsTemplated () )
			{
				
				TemplateMismatch = true;
				
				return NULL;
				
			}
			
			if ( TypeRef.GetTemplateSpecification () -> GetTypeRefCount () != OutDef -> GetStructDefinition () -> GetTemplateDefinition () -> GetTemplateParameterCount () )
			{
				
				TemplateMismatch = true;
				
				return NULL;
				
			}
			
		}
		
		return OutDef;
		
	}
	else
	{
		
		const OilNamespaceDefinition * Parent = & ImmediateContainer;
		
		if ( TypeRef.IsNamespaced () )
		{
			
			Parent = OilFindParentallyContainedNamespace ( * Parent, TypeRef.GetNamespaceName ( 0 ) );
			
			for ( uint32_t I = 1; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					return NULL;
				
			}
			
		}
		
		OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
		
	}
	
	if ( OutDef == NULL )
		return NULL;
	
	if ( OutDef -> GetStructDefinition () -> IsTemplated () )
	{
		
		if ( ! TypeRef.IsTemplated () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
		if ( TypeRef.GetTemplateSpecification () -> GetTypeRefCount () != OutDef -> GetStructDefinition () -> GetTemplateDefinition () -> GetTemplateParameterCount () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
	}
	
	return OutDef;
	
}

OilNamespaceDefinition * OilFindParentallyContainedNamespace ( OilNamespaceDefinition & SearchLeaf, const std :: u32string & Name )
{
	
	OilNamespaceDefinition * SearchTarget = & SearchLeaf;
	
	do
	{
		
		OilNamespaceDefinition * FindResult = SearchTarget -> FindNamespaceDefinition ( Name );
		
		if ( FindResult != NULL )
			return FindResult;
		
		SearchTarget = SearchTarget -> GetParent ();
		
	}
	while ( SearchTarget != NULL );
	
	return NULL;
	
}

const OilNamespaceDefinition * OilFindParentallyContainedNamespace ( const OilNamespaceDefinition & SearchLeaf, const std :: u32string & Name )
{
	
	const OilNamespaceDefinition * SearchTarget = & SearchLeaf;
	
	do
	{
		
		const OilNamespaceDefinition * FindResult = SearchTarget -> FindNamespaceDefinition ( Name );
		
		if ( FindResult != NULL )
			return FindResult;
		
		SearchTarget = SearchTarget -> GetParent ();
		
	}
	while ( SearchTarget != NULL );
	
	return NULL;
	
}

bool OilFindAndBuildAbsoluteTraitNamePath ( std :: vector <std :: u32string> & AbsoluteNamePath, OilTypeRef & Type, OilNamespaceDefinition & CurrentNS, OilTraitDefinition *& TraitOut, bool & TemplateMismatch )
{
	
	TraitOut = NULL;
	
	OilNamespaceDefinition * LocalNS = & CurrentNS;
	
	if ( Type.IsNamespaced () )
	{
		
		LocalNS = OilFindParentallyContainedNamespace ( * LocalNS, Type.GetNamespaceName ( 0 ) );
		
		if ( LocalNS == NULL )
			return false;
		
		AbsoluteNamePath.push_back ( Type.GetNamespaceName ( 0 ) );
		
		uint32_t Index = 1;
		
		while ( Index < Type.GetNamespaceNameCount () )
		{
			
			LocalNS = LocalNS -> FindNamespaceDefinition ( Type.GetNamespaceName ( Index ) );
			
			if ( LocalNS == NULL )
			{
				
				AbsoluteNamePath.clear ();
				
				return false;
				
			}
			
			AbsoluteNamePath.push_back ( Type.GetNamespaceName ( Index ) );
			
			Index ++;
			
		}
		
	}
	
	TraitOut = LocalNS -> FindTraitDefinition ( Type.GetName () );
	
	if ( TraitOut == NULL )
	{
		
		AbsoluteNamePath.clear ();
		
		return false;
		
	}
	
	if ( Type.IsTemplated () != TraitOut -> IsTemplated () )
	{
		
		AbsoluteNamePath.clear ();
		TemplateMismatch = true;
		
		return false;
		
	}
	
	if ( TraitOut -> IsTemplated () )
	{
		
		if ( TraitOut -> GetTemplateDefinition () -> GetTemplateParameterCount () != Type.GetTemplateSpecification () -> GetTypeRefCount () )	
		{
			
			AbsoluteNamePath.clear ();
			TemplateMismatch = true;
			
			return false;
			
		}
	
	}
	
	AbsoluteNamePath.push_back ( Type.GetName () );
	
	return true;
	
}

