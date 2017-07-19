#ifndef UTILS_GLOBALSINGLETON_H
#define UTILS_GLOBALSINGLETON_H

#include <type_traits>
#include <cstdlib>
#include <atomic>

template <class T>
inline T & GetGlobalSingleton ()
{
	
	class ObjectDeleter
	{
	public:
		
		inline ObjectDeleter ():
			Alloc ( false ),
			Storage ()
		{
		}
		
		inline ~ObjectDeleter ()
		{
			
			if ( Alloc )
				reinterpret_cast <volatile T *> ( & Storage ) -> ~T ();
			
		}
		
		inline bool ExchangeAllocated () volatile
		{
			
			return Alloc.exchange ( true );
			
		}
		
		inline void * GetAddress () volatile
		{
			
			return reinterpret_cast <void *> ( const_cast <typename std :: aligned_storage <sizeof ( T ), alignof ( T )> :: type *> ( & Storage ) );
			
		}
		
	private:
		
		std :: atomic_bool Alloc;
		typename std :: aligned_storage <sizeof ( T ), alignof ( T )> :: type Storage;
		
	};
	
	static volatile ObjectDeleter InstanceDeleter;
	
	void * Address = InstanceDeleter.GetAddress ();
	
	
	if ( ! InstanceDeleter.ExchangeAllocated () )
		new ( Address ) T ();
	
	if ( Address == nullptr )
	{
		
		throw "lldb catch";
		
	}
	
	return * reinterpret_cast <T *> ( Address );
	
}

#endif
