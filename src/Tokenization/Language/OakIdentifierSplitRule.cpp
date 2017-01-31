#include <Tokenization/Language/OakIdentifierSplitRule.h>

#include <StringUtils/RangeStringCompositor.h>

#include <Tokenization/Language/OakTokenTags.h>

//TODO: Finish unicode definitions

OakIdentifierSplitRule :: OakIdentifierSplitRule ():
	StartSet ( U"", 0, false ),
	ContinueSet ( U"", 0, false )
{
	
	RangeStringCompositor XID_Start_Compositor;
	RangeStringCompositor XID_Continue_Compositor;
	
	// Defined using http://unicode.org/cldr/utility/list-unicodeset.jsp?a=%5B%3AXID_Start%3A%5D&abb=on&g=&i=
	XID_Start_Compositor.AddRange ( U'\u0041', U'\u005A' );
	XID_Start_Compositor.AddRange ( U'\u0061', U'\u007A' );
	XID_Start_Compositor.AddIndividual ( U'\u00AA' );
	XID_Start_Compositor.AddIndividual ( U'\u00B5' );
	XID_Start_Compositor.AddIndividual ( U'\u00BA' );
	XID_Start_Compositor.AddRange ( U'\u00C0', U'\u00D6' );
	XID_Start_Compositor.AddRange ( U'\u00D8', U'\u00F6' );
	XID_Start_Compositor.AddRange ( U'\u00F8', U'\u02C1' );
	XID_Start_Compositor.AddRange ( U'\u02C6', U'\u02D1' );
	XID_Start_Compositor.AddRange ( U'\u02E0', U'\u02E4' );
	XID_Start_Compositor.AddIndividual ( U'\u02EC' );
	XID_Start_Compositor.AddIndividual ( U'\u02EE' );
	XID_Start_Compositor.AddRange ( U'\u0370', U'\u0374' );
	XID_Start_Compositor.AddIndividual ( U'\u0376' );
	XID_Start_Compositor.AddIndividual ( U'\u0377' );
	XID_Start_Compositor.AddRange ( U'\u037B', U'\u037D' );
	XID_Start_Compositor.AddIndividual ( U'\u037F' );
	XID_Start_Compositor.AddIndividual ( U'\u0386' );
	XID_Start_Compositor.AddRange ( U'\u0388', U'\u038A' );
	XID_Start_Compositor.AddIndividual ( U'\u038C' );
	XID_Start_Compositor.AddRange ( U'\u038E', U'\u03A1' );
	XID_Start_Compositor.AddRange ( U'\u03A3', U'\u03F5' );
	XID_Start_Compositor.AddRange ( U'\u03F7', U'\u0481' );
	XID_Start_Compositor.AddRange ( U'\u048A', U'\u052F' );
	XID_Start_Compositor.AddRange ( U'\u0531', U'\u0556' );
	XID_Start_Compositor.AddIndividual ( U'\u0559' );
	XID_Start_Compositor.AddRange ( U'\u0561', U'\u0587' );
	XID_Start_Compositor.AddRange ( U'\u05D0', U'\u05EA' );
	XID_Start_Compositor.AddRange ( U'\u05F0', U'\u05F2' );
	XID_Start_Compositor.AddRange ( U'\u0620', U'\u064A' );
	XID_Start_Compositor.AddIndividual ( U'\u066E' );
	XID_Start_Compositor.AddIndividual ( U'\u066F' );
	XID_Start_Compositor.AddRange ( U'\u0671', U'\u06D3' );
	XID_Start_Compositor.AddIndividual ( U'\u06D5' );
	XID_Start_Compositor.AddIndividual ( U'\u06E5' );
	XID_Start_Compositor.AddIndividual ( U'\u06E6' );
	XID_Start_Compositor.AddIndividual ( U'\u06EE' );
	XID_Start_Compositor.AddIndividual ( U'\u06EF' );
	XID_Start_Compositor.AddRange ( U'\u06FA', U'\u06FC' );
	XID_Start_Compositor.AddIndividual ( U'\u06FF' );
	XID_Start_Compositor.AddIndividual ( U'\u0710' );
	XID_Start_Compositor.AddRange ( U'\u0712', U'\u072F' );
	XID_Start_Compositor.AddRange ( U'\u074D', U'\u07A5' );
	XID_Start_Compositor.AddIndividual ( U'\u07B1' );
	XID_Start_Compositor.AddRange ( U'\u07CA', U'\u07EA' );
	XID_Start_Compositor.AddIndividual ( U'\u07F4' );
	XID_Start_Compositor.AddIndividual ( U'\u07F5' );
	XID_Start_Compositor.AddIndividual ( U'\u07FA' );
	XID_Start_Compositor.AddRange ( U'\u0800', U'\u0815' );
	XID_Start_Compositor.AddIndividual ( U'\u081A' );
	XID_Start_Compositor.AddIndividual ( U'\u0824' );
	XID_Start_Compositor.AddIndividual ( U'\u0828' );
	XID_Start_Compositor.AddRange ( U'\u0840', U'\u0858' );
	XID_Start_Compositor.AddRange ( U'\u08A0', U'\u08B4' );
	XID_Start_Compositor.AddRange ( U'\u08B6', U'\u08BD' );
	XID_Start_Compositor.AddRange ( U'\u0904', U'\u0939' );
	XID_Start_Compositor.AddIndividual ( U'\u093D' );
	XID_Start_Compositor.AddIndividual ( U'\u0950' );
	XID_Start_Compositor.AddRange ( U'\u0958', U'\u0961' );
	XID_Start_Compositor.AddRange ( U'\u0971', U'\u0980' );
	XID_Start_Compositor.AddRange ( U'\u0985', U'\u098C' );
	XID_Start_Compositor.AddIndividual ( U'\u098F' );
	XID_Start_Compositor.AddIndividual ( U'\u0990' );
	XID_Start_Compositor.AddRange ( U'\u0993', U'\u09A8' );
	XID_Start_Compositor.AddRange ( U'\u09AA', U'\u09B0' );
	XID_Start_Compositor.AddIndividual ( U'\u09B2' );
	XID_Start_Compositor.AddRange ( U'\u09B6', U'\u09B9' );
	XID_Start_Compositor.AddIndividual ( U'\u09BD' );
	XID_Start_Compositor.AddIndividual ( U'\u09CE' );
	XID_Start_Compositor.AddIndividual ( U'\u09DC' );
	XID_Start_Compositor.AddIndividual ( U'\u09DD' );
	XID_Start_Compositor.AddRange ( U'\u09DF', U'\u09E1' );
	XID_Start_Compositor.AddIndividual ( U'\u09F0' );
	XID_Start_Compositor.AddIndividual ( U'\u09F1' );
	XID_Start_Compositor.AddRange ( U'\u0A05', U'\u0A0A' );
	XID_Start_Compositor.AddIndividual ( U'\u0A0F' );
	XID_Start_Compositor.AddIndividual ( U'\u0A10' );
	XID_Start_Compositor.AddRange ( U'\u0A13', U'\u0A28' );
	XID_Start_Compositor.AddRange ( U'\u0A2A', U'\u0A30' );
	XID_Start_Compositor.AddIndividual ( U'\u0A32' );
	XID_Start_Compositor.AddIndividual ( U'\u0A33' );
	XID_Start_Compositor.AddIndividual ( U'\u0A35' );
	XID_Start_Compositor.AddIndividual ( U'\u0A36' );
	XID_Start_Compositor.AddIndividual ( U'\u0A38' );
	XID_Start_Compositor.AddIndividual ( U'\u0A39' );
	XID_Start_Compositor.AddRange ( U'\u0A59', U'\u0A5C' );
	XID_Start_Compositor.AddIndividual ( U'\u0A5E' );
	XID_Start_Compositor.AddRange ( U'\u0A72', U'\u0A74' );
	XID_Start_Compositor.AddRange ( U'\u0A85', U'\u0A8D' );
	XID_Start_Compositor.AddRange ( U'\u0A85', U'\u0A91' );
	XID_Start_Compositor.AddRange ( U'\u0A93', U'\u0AA8' );
	XID_Start_Compositor.AddRange ( U'\u0AAA', U'\u0AB0' );
	XID_Start_Compositor.AddRange ( U'\u0AB5', U'\u0AB9' );
	XID_Start_Compositor.AddIndividual ( U'\u0ABD' );
	XID_Start_Compositor.AddIndividual ( U'\u0AD0' );
	XID_Start_Compositor.AddIndividual ( U'\u0AE0' );
	XID_Start_Compositor.AddIndividual ( U'\u0AE1' );
	XID_Start_Compositor.AddIndividual ( U'\u0AF9' );
	XID_Start_Compositor.AddRange ( U'\u0B05', U'\u0B0C' );
	XID_Start_Compositor.AddIndividual ( U'\u0B0F' );
	XID_Start_Compositor.AddIndividual ( U'\u0B10' );
	XID_Start_Compositor.AddRange ( U'\u0B13', U'\u0B28' );
	XID_Start_Compositor.AddRange ( U'\u0B2A', U'\u0B30' );
	XID_Start_Compositor.AddIndividual ( U'\u0B32' );
	XID_Start_Compositor.AddIndividual ( U'\u0B33' );
	XID_Start_Compositor.AddRange ( U'\u0B35', U'\u0B39' );
	XID_Start_Compositor.AddIndividual ( U'\u0B3D' );
	XID_Start_Compositor.AddIndividual ( U'\u0B5C' );
	XID_Start_Compositor.AddIndividual ( U'\u0B5D' );
	XID_Start_Compositor.AddRange ( U'\u0B5F', U'\u0B61' );
	XID_Start_Compositor.AddIndividual ( U'\u0B71' );
	XID_Start_Compositor.AddIndividual ( U'\u0B83' );
	XID_Start_Compositor.AddRange ( U'\u0B85', U'\u0B8A' );
	XID_Start_Compositor.AddRange ( U'\u0B8E', U'\u0B90' );
	XID_Start_Compositor.AddRange ( U'\u0B92', U'\u0B95' );
	XID_Start_Compositor.AddIndividual ( U'\u0B99' );
	XID_Start_Compositor.AddIndividual ( U'\u0B9A' );
	XID_Start_Compositor.AddIndividual ( U'\u0B9C' );
	XID_Start_Compositor.AddIndividual ( U'\u0B9E' );
	XID_Start_Compositor.AddIndividual ( U'\u0B9F' );
	XID_Start_Compositor.AddIndividual ( U'\u0BA4' );
	XID_Start_Compositor.AddRange ( U'\u0BA8', U'\u0BAA' );
	XID_Start_Compositor.AddRange ( U'\u0BAE', U'\u0BB9' );
	XID_Start_Compositor.AddIndividual ( U'\u0BD0' );
	XID_Start_Compositor.AddRange ( U'\u0C05', U'\u0C0C' );
	XID_Start_Compositor.AddRange ( U'\u0C0E', U'\u0C10' );
	XID_Start_Compositor.AddRange ( U'\u0C12', U'\u0C28' );
	XID_Start_Compositor.AddRange ( U'\u0C2A', U'\u0C39' );
	XID_Start_Compositor.AddIndividual ( U'\u0C3D' );
	XID_Start_Compositor.AddRange ( U'\u0C58', U'\u0C5A' );
	XID_Start_Compositor.AddIndividual ( U'\u0C60' );
	XID_Start_Compositor.AddIndividual ( U'\u0C61' );
	XID_Start_Compositor.AddIndividual ( U'\u0C80' );
	XID_Start_Compositor.AddRange ( U'\u0C85', U'\u0C8C' );
	XID_Start_Compositor.AddRange ( U'\u0C8E', U'\u0C90' );
	XID_Start_Compositor.AddRange ( U'\u0C92', U'\u0CA8' );
	XID_Start_Compositor.AddRange ( U'\u0CAA', U'\u0CB3' );
	XID_Start_Compositor.AddRange ( U'\u0CB5', U'\u0CB9' );
	XID_Start_Compositor.AddIndividual ( U'\u0CBD' );
	XID_Start_Compositor.AddIndividual ( U'\u0CDE' );
	XID_Start_Compositor.AddIndividual ( U'\u0CE0' );
	XID_Start_Compositor.AddIndividual ( U'\u0CE1' );
	XID_Start_Compositor.AddIndividual ( U'\u0CF1' );
	XID_Start_Compositor.AddIndividual ( U'\u0CF2' );
	XID_Start_Compositor.AddRange ( U'\u0D05', U'\u0D0C' );
	XID_Start_Compositor.AddRange ( U'\u0D0E', U'\u0D10' );
	XID_Start_Compositor.AddRange ( U'\u0D12', U'\u0D3A' );
	XID_Start_Compositor.AddIndividual ( U'\u0D3D' );
	XID_Start_Compositor.AddIndividual ( U'\u0D3E' );
	XID_Start_Compositor.AddRange ( U'\u0D54', U'\u0D56' );
	XID_Start_Compositor.AddRange ( U'\u0D5F', U'\u0D61' );
	XID_Start_Compositor.AddRange ( U'\u0D7A', U'\u0D7F' );
	XID_Start_Compositor.AddRange ( U'\u0D85', U'\u0D96' );
	XID_Start_Compositor.AddRange ( U'\u0D9A', U'\u0DB1' );
	XID_Start_Compositor.AddRange ( U'\u0DB3', U'\u0DBB' );
	XID_Start_Compositor.AddIndividual ( U'\u0DBD' );
	XID_Start_Compositor.AddRange ( U'\u0DC0', U'\u0DC6' );
	XID_Start_Compositor.AddRange ( U'\u0E01', U'\u0E30' );
	XID_Start_Compositor.AddIndividual ( U'\u0E32' );
	XID_Start_Compositor.AddRange ( U'\u0E40', U'\u0E46' );
	XID_Start_Compositor.AddIndividual ( U'\u0E81' );
	XID_Start_Compositor.AddIndividual ( U'\u0E82' );
	XID_Start_Compositor.AddIndividual ( U'\u0E84' );
	XID_Start_Compositor.AddIndividual ( U'\u0E87' );
	XID_Start_Compositor.AddIndividual ( U'\u0E88' );
	XID_Start_Compositor.AddIndividual ( U'\u0E8A' );
	XID_Start_Compositor.AddIndividual ( U'\u0E8D' );
	XID_Start_Compositor.AddRange ( U'\u0E94', U'\u0E97' );
	XID_Start_Compositor.AddRange ( U'\u0E99', U'\u0E9F' );
	XID_Start_Compositor.AddRange ( U'\u0EA1', U'\u0EA3' );
	XID_Start_Compositor.AddIndividual ( U'\u0EA5' );
	XID_Start_Compositor.AddIndividual ( U'\u0EA7' );
	XID_Start_Compositor.AddIndividual ( U'\u0EAA' );
	XID_Start_Compositor.AddIndividual ( U'\u0EAB' );
	XID_Start_Compositor.AddRange ( U'\u0EAD', U'\u0EB0' );
	XID_Start_Compositor.AddIndividual ( U'\u0EB2' );
	XID_Start_Compositor.AddIndividual ( U'\u0EBD' );
	XID_Start_Compositor.AddRange ( U'\u0EC0', U'\u0EC4' );
	XID_Start_Compositor.AddIndividual ( U'\u0EC6' );
	XID_Start_Compositor.AddRange ( U'\u0EDC', U'\u0EDF' );
	XID_Start_Compositor.AddIndividual ( U'\u0F00' );
	XID_Start_Compositor.AddRange ( U'\u0F40', U'\u0F47' );
	XID_Start_Compositor.AddRange ( U'\u0F49', U'\u0F6C' );
	XID_Start_Compositor.AddRange ( U'\u0F88', U'\u0F8C' );
	XID_Start_Compositor.AddRange ( U'\u1000', U'\u102A' );
	
	/*XID_Start_Compositor.AddRange ( U'\u0000', U'\u0000' );
	XID_Start_Compositor.AddRange ( U'\u0000', U'\u0000' );
	XID_Start_Compositor.AddRange ( U'\u0000', U'\u0000' );*/
	
	/*========================*/
	XID_Continue_Compositor.AddInherited ( XID_Start_Compositor );
	
	XID_Continue_Compositor.AddRange ( U'\u0030', u'\u0039' );
	XID_Continue_Compositor.AddIndividual ( U'\u005F' );
	XID_Continue_Compositor.AddIndividual ( U'\u00B7' );
	XID_Continue_Compositor.AddRange ( U'\u0300', U'\u036F' );
	
	/*XID_Continue_Compositor.AddRange ( U'\u0000', U'\u0000' );
	XID_Continue_Compositor.AddRange ( U'\u0000', U'\u0000' );
	XID_Continue_Compositor.AddRange ( U'\u0000', U'\u0000' );
	XID_Continue_Compositor.AddRange ( U'\u0000', U'\u0000' );
	XID_Continue_Compositor.AddRange ( U'\u0000', U'\u0000' );
	XID_Continue_Compositor.AddRange ( U'\u0000', U'\u0000' );*/
	// Add rest
	
	/*========================*/
	
	StartChars = std :: move ( XID_Start_Compositor.CompositeString () );
	ContinueChars = std :: move ( XID_Continue_Compositor.CompositeString () );
	
	StartSet.SetChars ( & StartChars [ 0 ], StartChars.size (), false );
	ContinueSet.SetChars ( & ContinueChars [ 0 ], ContinueChars.size (), false );
	
}

OakIdentifierSplitRule :: ~OakIdentifierSplitRule ()
{
}

void OakIdentifierSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Offset >= Source.size () )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	char32_t Char = Source.at ( Offset );
	
	if ( ! StartSet.Contains ( Char ) )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	Result.Accepted = true;
	Result.Tag = OakTokenTags :: kTokenTag_Identifier;
	
	uint64_t Length = 1;
	
	while ( ( Offset + Length ) < Source.size () )
	{
		
		Char = Source.at ( Offset + Length );
		
		if ( ! ContinueSet.Contains ( Char ) )
		{
			
			Result.SplitLength = Length;
			
			return;
			
		}
		
		Length ++;
		
	}
	
	Result.SplitLength = Length + 1;
	
}
