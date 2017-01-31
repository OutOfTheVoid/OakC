#ifndef TOKENIZATION_LANGUAGE_OAKSingleLINECOMMENTSPLITRULE_H
#define TOKENIZATION_LANGUAGE_OAKSingleLINECOMMENTSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class OakSingleLineCommentSplitRule : public virtual ITokenSplitRule
{
public:
	
	/// Constructor. (no-op)
	OakSingleLineCommentSplitRule ();
	
	/// Destructor. (no-op)
	~OakSingleLineCommentSplitRule ();
	
	/// Implements ITokenSplitRule :: TrySplit
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
};

#endif
