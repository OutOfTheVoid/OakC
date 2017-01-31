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
	
	const uint64_t kASTTag_BareTraitName = 8;
	
	const uint64_t kASTTag_BareTypeName = 9;
	
	const uint64_t kASTTag_StructBinding = 10;
	
	const uint64_t kASTTag_TemplateSpecification = 11;
	
	const char * const TagNames [] =
	{
		
		"FILE",
		"IMPORT_STATEMENT",
		"FILE_STRING",
		"STRUCT_DEFINITION",
		"TEMPLATE_DEFINITION",
		"TEMPLATE_PARAMETER_UNRESTRICTED",
		"TEMPLATE_PARAMETER_RESTRICTED",
		"TRAIT_NAME_BARE",
		"TYPE_NAME_BARE",
		"STRUCT_BINDING",
		"TEMPLATE_SPECIFICATION",
		
	};
	
}

#endif
