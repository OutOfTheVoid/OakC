#ifndef PARSING_LANGUAGE_OAKASTTAGS_H
#define PARSING_LANGUAGE_OAKASTTAGS_H

namespace OakASTTags
{
	
	const uint64_t kASTTag_File = 1;
	
	const uint64_t kASTTag_ImportStatement = 2;
	
	const uint64_t kASTTag_StructDefinition = 3;
	
	const uint64_t kASTTag_TemplateDefinition = 4;
	const uint64_t kASTTag_UnrestrictedTemplateParameter = 5;
	const uint64_t kASTTag_RestrictedTemplateParameter = 6;
	
	const uint64_t kASTTag_TraitName_Bare = 7;
	const uint64_t kASTTag_TraitName_Templated = 8;
	const uint64_t kASTTag_TraitName_Namespaced = 9;
	const uint64_t kASTTag_TraitName_NamespacedTemplated = 10;
	
	const uint64_t kASTTag_TypeName_Bare = 11;
	const uint64_t kASTTag_TypeName_Templated = 12;
	const uint64_t kASTTag_TypeName_Namespaced = 13;
	const uint64_t kASTTag_TypeName_NamespacedTemplated = 14;
	
	const uint64_t kASTTag_StructBinding = 15;
	
	const uint64_t kASTTag_TemplateSpecification = 16;
	
	const uint64_t kASTTag_NamespaceDefinition = 17;
	
	const uint64_t kASTTag_ImplementDefinition = 18;
	
	const uint64_t kASTTag_FunctionDefinition = 19;
	const uint64_t kASTTag_FunctionParameterList = 20;
	const uint64_t kASTTag_FunctionParameter = 21;
	
	const uint64_t kASTTag_StatementBlock = 22;
	
	const uint64_t kASTTag_PointerType = 23;
	const uint64_t kASTTag_ReferenceType = 24;
	
	const uint64_t kASTTag_SelfParameter = 25;
	const uint64_t kASTTag_SelfParameterReference = 26;
	
	const uint64_t kASTTag_MethodDefinition = 27;
	const uint64_t kASTTag_MethodParameterList = 28;
	
	const uint64_t kASTTag_ReturnType = 29;
	
	const uint64_t kASTTag_IgnoreStatement = 30;
	
	const char * const TagNames [] =
	{
		
		"DEFAULT",
		"FILE",
		"IMPORT_STATEMENT",
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
		"IMPLEMENT_DEFINITION",
		"FUNCTION_DEFINITION",
		"FUNCTION_PARAMETER_LIST",
		"FUNCTION_PARAMETER",
		"STATEMENT_BLOCK",
		"POINTER_TYPE",
		"REFERENCE_TYPE",
		"SELF_PARAMETER",
		"SELF_PARAMETER_REFERENCE",
		"METHOD_DEFINITION",
		"METHOD_PARAMETER_LIST",
		"RETURN_TYPE",
		"IGNORE_STATEMENT"
		
	};
	
}

#endif
