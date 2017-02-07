#ifndef PARSING_LANGUAGE_OAKASTTAGS_H
#define PARSING_LANGUAGE_OAKASTTAGS_H

namespace OakASTTags
{
	
	const uint64_t kASTTag_File = 1;
	
	const uint64_t kASTTag_ImportStatement = 2;
	
	const uint64_t kASTTag_StructDefinition = 3;
	const uint64_t kASTTag_TraitDefinition = 4;
	
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
	const uint64_t kASTTag_TraitFunction = 17;
	
	const uint64_t kASTTag_TemplateSpecification = 18;
	
	const uint64_t kASTTag_NamespaceDefinition = 19;
	
	const uint64_t kASTTag_ImplementDefinition = 20;
	
	const uint64_t kASTTag_FunctionDefinition = 21;
	const uint64_t kASTTag_FunctionParameterList = 22;
	const uint64_t kASTTag_FunctionParameter = 23;
	
	const uint64_t kASTTag_StatementBlock = 24;
	
	const uint64_t kASTTag_PointerType = 25;
	const uint64_t kASTTag_ReferenceType = 26;
	
	const uint64_t kASTTag_SelfParameter = 27;
	const uint64_t kASTTag_SelfParameterReference = 28;
	
	const uint64_t kASTTag_MethodDefinition = 29;
	const uint64_t kASTTag_MethodParameterList = 30;
	
	const uint64_t kASTTag_ReturnType = 31;
	
	const uint64_t kASTTag_IgnoreStatement = 32;
	const uint64_t kASTTag_ReturnStatement = 33;
	
	const uint64_t kASTTag_ExpressionStatement = 34;
	
	const uint64_t kASTTag_Expression = 35;
	const uint64_t kASTTag_PrimaryExpression = 36;
	
	const uint64_t kASTTag_LiteralExpression = 37;
	const uint64_t kASTTag_ParenthesizedExpression = 38;
	
	const char * const TagNames [] =
	{
		
		"DEFAULT",
		"FILE",
		"IMPORT_STATEMENT",
		"STRUCT_DEFINITION",
		"TRAIT_DEFINITION",
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
		"TRAIT_FUNCTION",
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
		"IGNORE_STATEMENT",
		"RETURN_STATEMENT",
		"EXPRESSION_STATEMENT",
		"EXPRESSION",
		"PRIMARY_EXPRESSION",
		"LITERAL_EXPRESSION",
		"PARENTHESIZED_EXPRESSION",
		
	};
	
}

#endif
