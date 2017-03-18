#ifndef OIL_OILIMPLEMENTBLOCK_H
#define OIL_OILIMPLEMENTBLOCK_H

class OilImplementBlock
{
public:
	
	OilImplementBlock ( OilTypeRef * ImplementingType );
	~OilImplementBlock ();
	
	const OilTypeRef * GetImplementedTypeRef () const;
	OilTypeRef * GetImplementedTypeRef ();
	
	void AddFunction (  ) const;
	void AddMethod (  ) const;
	
private:
	
	OilTypeRef * ImplementingType;
	
};

#endif
