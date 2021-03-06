#ifndef PARSING_LANGUAGE_OAKASTTAGS_H
#define PARSING_LANGUAGE_OAKASTTAGS_H

namespace OakASTTags
{
	
	const uint64_t kASTTag_Default = 0;
	
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
	
	const uint64_t kASTTag_TypeAlias = 25;
	
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
	
	const uint64_t kASTTag_Allusion = 39;
	
	const uint64_t kASTTag_Operator_PostfixIncrement = 40;
	const uint64_t kASTTag_Operator_PostfixDecrement = 41;
	
	const uint64_t kASTTag_Operator_PrefixIncrement = 42;
	const uint64_t kASTTag_Operator_PrefixDecrement = 43;
	const uint64_t kASTTag_Operator_BitwiseNot = 44;
	const uint64_t kASTTag_Operator_LogicalNot = 45;
	const uint64_t kASTTag_Operator_UnaryNegate = 46;
	const uint64_t kASTTag_Operator_UnaryPositive = 47;
	const uint64_t kASTTag_Operator_Reference = 48;
	
	const uint64_t kASTTag_Operator_Multiply = 50;
	const uint64_t kASTTag_Operator_Divide = 51;
	const uint64_t kASTTag_Operator_Modulo = 52;
	const uint64_t kASTTag_Operator_Add = 53;
	const uint64_t kASTTag_Operator_Subtract = 54;
	
	const uint64_t kASTTag_Operator_LeftShift = 55;
	const uint64_t kASTTag_Operator_RightShift = 56;
	const uint64_t kASTTag_Operator_LogicalRightShift = 57;
	
	const uint64_t kASTTag_Operator_GreaterThan = 58;
	const uint64_t kASTTag_Operator_LessThan = 59;
	const uint64_t kASTTag_Operator_GreaterThanOrEqual = 60;
	const uint64_t kASTTag_Operator_LessThanOrEqual = 61;
	
	const uint64_t kASTTag_Operator_NotEqual = 62;
	const uint64_t kASTTag_Operator_Equal = 63;
	
	const uint64_t kASTTag_Operator_BitwiseAnd = 64;
	const uint64_t kASTTag_Operator_BitwiseXor = 65;
	const uint64_t kASTTag_Operator_BitwiseOr = 66;
	
	const uint64_t kASTTag_Operator_LogicalAnd = 67;
	const uint64_t kASTTag_Operator_LogicalOr = 68;
	
	const uint64_t kASTTag_Operator_Ternary = 69;
	
	const uint64_t kASTTag_Operator_Assignment = 70;
	
	const uint64_t kASTTag_Operator_CompoundMultiply = 71;
	const uint64_t kASTTag_Operator_CompoundDivide = 72;
	const uint64_t kASTTag_Operator_CompoundModulo = 73;
	const uint64_t kASTTag_Operator_CompoundAdd = 74;
	const uint64_t kASTTag_Operator_CompoundSubtract = 75;
	const uint64_t kASTTag_Operator_CompoundLeftShift = 76;
	const uint64_t kASTTag_Operator_CompoundRightShift = 77;
	const uint64_t kASTTag_Operator_CompoundBitwiseAnd = 78;
	const uint64_t kASTTag_Operator_CompoundBitwiseOr = 79;
	const uint64_t kASTTag_Operator_CompoundBitwiseXor = 80;
	const uint64_t kASTTag_Operator_CompoundLogicalRightShift = 81;
	const uint64_t kASTTag_Operator_CompoundLogicalAnd = 82;
	const uint64_t kASTTag_Operator_CompoundLogicalOr = 83;
	
	const uint64_t kASTTag_Operator_MemberAccess = 84;
	const uint64_t kASTTag_MemberAccessName = 85;
	const uint64_t kASTTag_Operator_ArrayAccess = 86;
	const uint64_t kASTTag_Operator_FunctionCall = 87;
	
	const uint64_t kASTTag_OperatorExpressionContainer = 88;
	
	const uint64_t kASTTag_FunctionCall_ParameterList = 89;
	
	const uint64_t kASTTag_SelfAllusion = 90;
	
	const uint64_t kASTTag_IfElseStatement = 91;
	const uint64_t kASTTag_WhileStatement = 92;
	const uint64_t kASTTag_DoWhileStatement = 93;
	const uint64_t kASTTag_LoopStatement = 94;
	
	const uint64_t kASTTag_LoopLabel = 95;
	
	const uint64_t kASTTag_BreakStatement = 96;
	
	const uint64_t kASTTag_ArrayLiteral = 97;
	
	const uint64_t kASTTag_BindingStatement = 98;
	const uint64_t kASTTag_ConstStatement = 99;
	const uint64_t kASTTag_TraitMethod = 100;
	
	const uint64_t kASTTag_VoidType = 101;
	
	const uint64_t kASTTag_TraitRequirement = 102;
	
	const uint64_t kASTTag_DecoratorTag = 103;
	
	const uint64_t kASTTag_WhereClause = 104;
	
	const uint64_t kASTTag_StructLiteral = 105;
	const uint64_t kASTTag_StructLiteralMemberValue = 106;
	
	const uint64_t kASTTag_Enum = 107;
	const uint64_t kASTTag_EnumBranch = 108;
	
	const uint64_t kASTTag_Match = 109;
	const uint64_t kASTTag_MatchBranch = 110;
	
	const uint64_t kASTTag_StructDestructure = 111;
	const uint64_t kASTTag_MemberDestructure = 112;
	
	const uint64_t kASTTag_Operator_TraitCast = 113;
	
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
		"ALIAS_DECLARATION",
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
		"ALLUSION",
		"OPERATOR_POSTFIX_INCREMENT",
		"OPERATOR_POSTFIX_DECREMENT",
		"OPERATOR_PREFIX_INCREMENT",
		"OPERATOR_PREFIX_DECREMENT",
		"OPERATOR_BITWISE_NOT",
		"OPERATOR_LOGICAL_NOT",
		"OPERATOR_UNARY_NEGATE",
		"OPERATOR_UNARY_POSITIVE",
		"OPERATOR_REFERENCE_ADDRESS_OF",
		"OPERATOR_POINTER_DEREFERENCE",
		"OPERATOR_MULTIPLY",
		"OPERATOR_DIVIDE",
		"OPERATOR_MODULO",
		"OPERATOR_ADD",
		"OPERATOR_SUBTRACT",
		"OPERATOR_SHIFT_LEFT",
		"OPERATOR_SHIFT_RIGHT",
		"OPERATOR_LOGICAL_SHIFT_RIGHT",
		"OPERATOR_GREATER_THAN",
		"OPERATOR_LESS_THAN",
		"OPERATOR_GREATER_THAN_OR_EQUAL",
		"OPERATOR_LESS_THAN_OR_EQUAL",
		"OPERATOR_NOT_EQUAL",
		"OPERATOR_EQUAL",
		"OPERATOR_BITWISE_AND",
		"OPERATOR_BITWISE_XOR",
		"OPERATOR_BITWISE_OR",
		"OPERATOR_LOGICAL_AND",
		"OPERATOR_LOGICAL_OR",
		"OPERATOR_TERNARY",
		"OPERATOR_ASSIGN",
		"OPERATOR_COMPOUND_MULTIPLY",
		"OPERATOR_COMPOUND_DIVIDE",
		"OPERATOR_COMPOUND_MODULO",
		"OPERATOR_COMPOUND_ADD",
		"OPERATOR_COMPOUND_SUBTRACT",
		"OPERATOR_COMPOUND_SHIFT_LEFT",
		"OPERATOR_COMPOUND_SHIFT_RIGHT",
		"OPERATOR_COMPOUND_BITWISE_AND",
		"OPERATOR_COMPOUND_BITWISE_OR",
		"OPERATOR_COMPOUND_BITWISE_XOR",
		"OPERATOR_COMPOUND_LOGICAL_SHIFT_RIGHT",
		"OPERATOR_COMPOUND_LOGICAL_AND",
		"OPERATOR_COMPOUND_LOGICAL_OR",
		"MEMBER_ACCESS",
		"MEMBER_ACCESS_NAME",
		"ARRAY_ACCESS",
		"FUNCTION_CALL",
		"OPERATOR_EXPRESSION_CONTAINER",
		"FUNCTION_CALL_PARAM_LIST",
		"SELF_ALLUSION",
		"IF_ELSE_STATEMENT",
		"WHILE_STATEMENT",
		"DO_WHILE_STATEMENT",
		"LOOP_STATEMENT",
		"LOOP_LABEL",
		"BREAK_STATEMENT",
		"ARRAY_LITERAL",
		"BINDING_STATEMENT",
		"CONST_STATEMENT",
		"TRAIT_METHOD",
		"VOID_TYPE",
		"TRAIT_REQUIREMENT",
		"DECORATOR_TAG",
		"WHERE_CLAUSE",
		"STRUCT_LITERAL",
		"STRUCT_LITERAL_MEMBER_VALUE",
		"ENUM",
		"ENUM_BRANCH",
		"MATCH",
		"MATCH_BRANCH",
		"DESTRUCTURE_STRUCT",
		"DESTRUCTURE_MEMBER",
		"OPERATOR_TRAIT_CAST"
		
	};
	
}

#endif
