#ifndef PARSING_LANGUAGE_OAKASTTAGS_H
#define PARSING_LANGUAGE_OAKASTTAGS_H

namespace OakASTTags
{
	
	const uint64_t kASTTag_File = 1;
	
	const uint64_t kASTTag_ImportStatement = 2;
	const uint64_t kASTTag_FileString = 3;
	
	const uint64_t kASTTag_StructDefinition = 4;
	
	const uint64_t kASTTag_TemplateDefinition = 5;
	const uint64_t kASTTag_UnrestrictedTemplateParameter = 6;
	const uint64_t kASTTag_RestrictedTemplateParameter = 7;
	
	const uint64_t kASTTag_TraitName_Bare = 8;
	const uint64_t kASTTag_TraitName_Templated = 9;
	const uint64_t kASTTag_TraitName_Namespaced = 10;
	const uint64_t kASTTag_TraitName_NamespacedTemplated = 11;
	
	const uint64_t kASTTag_TypeName_Bare = 12;
	const uint64_t kASTTag_TypeName_Templated = 13;
	const uint64_t kASTTag_TypeName_Namespaced = 14;
	const uint64_t kASTTag_TypeName_NamespacedTemplated = 15;
	
	const uint64_t kASTTag_StructBinding = 16;
	
	const uint64_t kASTTag_TemplateSpecification = 17;
	
	const uint64_t kASTTag_NamespaceDefinition = 18;
	
	const char * const TagNames [] =
	{
		
		"DEFAULT",
		"FILE",
		"IMPORT_STATEMENT",
		"FILE_STRING",
		"STRUCT_DEFINITION",
		"TEMPLATE_DEFINITION",
		"TEMPLATE_PARAMETER_UNRESTRICTED",
		"TEMPLATE_PARAMETER_RESTRICTED",
		"TRAIT_NAME_BARE",
		"TRAIT_NAME_TEMPLATED",
		"TRAIT_NAME_NAMESPACED",
		"TRAIT_NAME_NAMESPACED_TEMPLATED",
		"TYPE_NAME_BARE",
		"TYPE_NAME_TEMPLATED",
		"TYPE_NAME_NAMESPACED",
		"TYPE_NAME_NAMESPACED_TEMPLATED",
		"STRUCT_BINDING",
		"TEMPLATE_SPECIFICATION",
		"NAMESPACE_DEFINITION",
		
	};
	
}

#endif
