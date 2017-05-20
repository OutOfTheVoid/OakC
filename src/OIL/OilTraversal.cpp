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
	
	OilNamespaceDefinition * Parent = & ImmediateContainer;
	
	if ( ( TypeRef.GetFlags () & OilTypeRef :: kRefFlag_Absolute ) != 0 )
	{
		
		while ( Parent -> GetParent () != NULL )
			Parent = Parent -> GetParent ();
		
		if ( TypeRef.IsNamespaced () )
		{
			
			for ( uint32_t I = 0; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					return NULL;
				
			}
			
		}
		
		if ( Parent != NULL )
			OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
		
	}
	else
	{
			
		if ( TypeRef.IsNamespaced () )
		{
			
			Parent = OilFindParentallyContainedNamespace ( * Parent, TypeRef.GetNamespaceName ( 0 ) );
			
			for ( uint32_t I = 1; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					break;
				
			}
			
			if ( Parent != NULL )
				OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
			
		}
		else
		{
			
			while ( Parent != NULL )
			{
				
				OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
				
				if ( OutDef != NULL )
					break;
				
				Parent = Parent -> GetParent ();
				
			}
			
		}
		
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
	
	const OilNamespaceDefinition * Parent = & ImmediateContainer;
	
	if ( ( TypeRef.GetFlags () & OilTypeRef :: kRefFlag_Absolute ) != 0 )
	{
		
		while ( Parent -> GetParent () != NULL )
			Parent = Parent -> GetParent ();
		
		if ( TypeRef.IsNamespaced () )
		{
			
			for ( uint32_t I = 0; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					return NULL;
				
			}
			
		}
		
		if ( Parent != NULL )
			OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
		
	}
	else
	{
			
		if ( TypeRef.IsNamespaced () )
		{
			
			Parent = OilFindParentallyContainedNamespace ( * Parent, TypeRef.GetNamespaceName ( 0 ) );
			
			for ( uint32_t I = 1; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					break;
				
			}
			
			if ( Parent != NULL )
				OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
			
		}
		else
		{
			
			while ( Parent != NULL )
			{
				
				OutDef = Parent -> FindTypeDefinition ( TypeRef.GetName () );
				
				if ( OutDef != NULL )
					break;
				
				Parent = Parent -> GetParent ();
				
			}
			
		}
		
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

OilTraitDefinition * FindTraitDefinition ( const OilTypeRef & TypeRef, OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch )
{
	
	if ( ! TypeRef.IsDirectType () )
		return NULL;
	
	OilTraitDefinition * OutDef = NULL;
	
	OilNamespaceDefinition * Parent = & ImmediateContainer;
	
	if ( ( TypeRef.GetFlags () & OilTypeRef :: kRefFlag_Absolute ) != 0 )
	{
		
		while ( Parent -> GetParent () != NULL )
			Parent = Parent -> GetParent ();
		
		if ( TypeRef.IsNamespaced () )
		{
			
			for ( uint32_t I = 0; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					return NULL;
				
			}
			
		}
		
		if ( Parent != NULL )
			OutDef = Parent -> FindTraitDefinition ( TypeRef.GetName () );
		
	}
	else
	{
			
		if ( TypeRef.IsNamespaced () )
		{
			
			Parent = OilFindParentallyContainedNamespace ( * Parent, TypeRef.GetNamespaceName ( 0 ) );
			
			for ( uint32_t I = 1; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					break;
				
			}
			
			if ( Parent != NULL )
				OutDef = Parent -> FindTraitDefinition ( TypeRef.GetName () );
			
		}
		else
		{
			
			while ( Parent != NULL )
			{
				
				OutDef = Parent -> FindTraitDefinition ( TypeRef.GetName () );
				
				if ( OutDef != NULL )
					break;
				
				Parent = Parent -> GetParent ();
				
			}
			
		}
		
	}
	
	if ( OutDef == NULL )
		return NULL;
	
	if ( OutDef -> IsTemplated () )
	{
		
		if ( ! TypeRef.IsTemplated () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
		if ( TypeRef.GetTemplateSpecification () -> GetTypeRefCount () != OutDef -> GetTemplateDefinition () -> GetTemplateParameterCount () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
	}
	else
	{
		
		if ( TypeRef.IsTemplated () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
	}
	
	return OutDef;
	
}

const OilTraitDefinition * FindTraitDefinition ( const OilTypeRef & TypeRef, const OilNamespaceDefinition & ImmediateContainer, bool & TemplateMismatch )
{
	
	if ( ! TypeRef.IsDirectType () )
		return NULL;
	
	const OilTraitDefinition * OutDef = NULL;
	
	const OilNamespaceDefinition * Parent = & ImmediateContainer;
	
	if ( ( TypeRef.GetFlags () & OilTypeRef :: kRefFlag_Absolute ) != 0 )
	{
		
		while ( Parent -> GetParent () != NULL )
			Parent = Parent -> GetParent ();
		
		if ( TypeRef.IsNamespaced () )
		{
			
			for ( uint32_t I = 0; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					return NULL;
				
			}
			
		}
		
		if ( Parent != NULL )
			OutDef = Parent -> FindTraitDefinition ( TypeRef.GetName () );
		
	}
	else
	{
			
		if ( TypeRef.IsNamespaced () )
		{
			
			Parent = OilFindParentallyContainedNamespace ( * Parent, TypeRef.GetNamespaceName ( 0 ) );
			
			for ( uint32_t I = 1; I < TypeRef.GetNamespaceNameCount (); I ++ )
			{
				
				Parent = Parent -> FindNamespaceDefinition ( TypeRef.GetNamespaceName ( I ) );
				
				if ( Parent == NULL )
					break;
				
			}
			
			if ( Parent != NULL )
				OutDef = Parent -> FindTraitDefinition ( TypeRef.GetName () );
			
		}
		else
		{
			
			while ( Parent != NULL )
			{
				
				OutDef = Parent -> FindTraitDefinition ( TypeRef.GetName () );
				
				if ( OutDef != NULL )
					break;
				
				Parent = Parent -> GetParent ();
				
			}
			
		}
		
	}
	
	if ( OutDef == NULL )
		return NULL;
	
	if ( OutDef -> IsTemplated () )
	{
		
		if ( ! TypeRef.IsTemplated () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
		if ( TypeRef.GetTemplateSpecification () -> GetTypeRefCount () != OutDef -> GetTemplateDefinition () -> GetTemplateParameterCount () )
		{
			
			TemplateMismatch = true;
			
			return NULL;
			
		}
		
	}
	else
	{
		
		if ( TypeRef.IsTemplated () )
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

void BuildAbsoluteNamePath_Trait ( std :: vector <std :: u32string> & AbsolutePath, const OilTraitDefinition & Trait )
{
	
	const OilNamespaceDefinition * Parent = Trait.GetParent ();
	
	while ( Parent -> GetParent () != NULL )
	{
		
		AbsolutePath.insert ( AbsolutePath.begin (), Parent -> GetID () );
		Parent = Parent -> GetParent ();
		
	}
	
	AbsolutePath.push_back ( Trait.GetName () );
	
}
