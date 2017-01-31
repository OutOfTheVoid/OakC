#ifndef UTILS_TESTSET_H
#define UTILS_TESTSET_H

#ifndef NULL
	#define NULL nullptr
#endif

template <typename Element>
class TestSet
{
public:
	
	TestSet ( const Element * Set, uint32_t SetSize, bool DeleteOnDestruct ):
		Set ( Set ),
		SetSize ( SetSize ),
		DeleteOnDestruct ( DeleteOnDestruct ),
		SubSet ( NULL ),
		DeleteSubsetOnDestruct ( false )
	{
	};
	
	TestSet ( const TestSet <Element> * SubSet, bool DeleteSubsetOnDestruct, const Element * Set, uint32_t SetSize, bool DeleteOnDestruct ):
		Set ( Set ),
		SetSize ( SetSize ),
		DeleteOnDestruct ( DeleteOnDestruct ),
		SubSet ( SubSet ),
		DeleteSubsetOnDestruct ( DeleteSubsetOnDestruct )
	{	
	};
	
	~TestSet ()
	{
		
		if ( DeleteOnDestruct )
			delete Set;
		
		if ( DeleteSubsetOnDestruct && ( SubSet != NULL ) )
			delete SubSet;
		
	};
	
	void SetValidationSet ( const Element * Set, uint32_t SetSize, bool DeleteOnDestruct )
	{
		
		if ( DeleteOnDestruct )
			delete this -> Set;
		
		this -> Set = Set;
		this -> SetSize = SetSize;
		this -> DeleteOnDestruct = DeleteOnDestruct;
		
	};
	
	void SetSubSet ( const TestSet <Element> * SubSet, bool DeleteSubsetOnDestruct )
	{
		
		if ( DeleteSubsetOnDestruct && ( this -> SubSet != NULL ) )
			delete this -> SubSet;
		
		this -> SubSet = SubSet;
		this -> DeleteSubsetOnDestruct = DeleteSubsetOnDestruct;
		
	};
	
	const Element * GetValidationSet () const
	{
		
		return Set;
		
	};
	
	uint32_t GetSetSize () const
	{
		
		return SetSize;
		
	};
	
	const TestSet <Element> * GetSubSet () const
	{
		
		return SubSet;
		
	};
	
	bool Contains ( const Element Test ) const
	{
		
		for ( uint32_t I = 0; I < SetSize; I ++ )
		{
			
			if ( Test == Set [ I ] )
				return true;
			
		}
		
		if ( SubSet != NULL )
			return SubSet -> Contains ( Test );
		
		return false;
		
	};
	
private:
	
	const Element * Set;
	uint32_t SetSize;
	
	bool DeleteOnDestruct;
	
	const TestSet <Element> * SubSet;
	
	bool DeleteSubsetOnDestruct;
	
};

#endif
