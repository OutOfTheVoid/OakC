#include <Filesystem/TextFile.h>

#include <cstdlib>
#include <cstring>

#define STACKBUFFER_SIZE 0x1000

TextFile :: TextFile ( const std :: string & Name, bool Writable ):
	File ( Name, Writable )
{
}

TextFile :: TextFile ( const TextFile & CopyFrom ):
	File ( CopyFrom )
{
}

TextFile :: ~TextFile ()
{
}

void TextFile :: ReadToString ( uint32_t * Status, std :: string & String, uint64_t Offset, uint64_t Length, bool TrimToFileEdge )
{
	
	if ( ! Exists () )
	{
		
		* Status = kStatus_Failure_NonExistantFile;
		
		return;
		
	}
	
	if ( ! IsOpen () )
	{
		
		Open ( Status );
		
		if ( * Status != File :: kStatus_Success )
			return;
		
	}
	else
		Flush ( Status );
	
	uint64_t FileLength = GetLength ( Status );
	
	if ( * Status != File :: kStatus_Success )
		return;
	
	if ( Offset + Length > FileLength )
	{
		
		if ( ( Offset > FileLength ) || ( ! TrimToFileEdge ) )
		{
			
			* Status = kStatus_Failure_FileBounds;
			
			return;
			
		}
		
		Length = FileLength - Offset;
		
	}
	
	if ( Length > STACKBUFFER_SIZE )
	{
		
		void * ReadBuffer = malloc ( static_cast <size_t> ( Length ) );
		
		if ( ReadBuffer == NULL )
		{
			
			* Status = kStatus_Failure_OutOfMemory;
			
			return;
			
		}
		
		Read ( ReadBuffer, Length, Offset, Status );
		
		if ( * Status != kStatus_Success )
		{
			
			free ( ReadBuffer );
			
			return;
			
		}
		
		String.assign ( reinterpret_cast <char *> ( ReadBuffer ), Length );
		
		free ( ReadBuffer );
		
		* Status = kStatus_Success;
		
		return;
		
	}
	
	char ReadBuffer [ STACKBUFFER_SIZE ];
	
	Read ( reinterpret_cast <void *> ( ReadBuffer ), Length, Offset, Status );
	
	if ( * Status != kStatus_Success )
		return;
	
	String.assign ( reinterpret_cast <char *> ( ReadBuffer ), Length );
	
	* Status = kStatus_Success;
	
}

void TextFile :: WriteFromString ( uint32_t * Status, const std :: string & String, uint64_t StringOffset, uint64_t FileOffset, uint64_t Length, bool FillFileGap, char FillChar )
{
	
	if ( StringOffset >= String.size () )
	{
		 
		* Status = kStatus_Failure_StringBounds;
		
		return;
		
	}
	
	if ( StringOffset + Length >= String.size () )
		Length = String.size () - StringOffset;
	
	if ( ! Exists () )
	{
		
		* Status = kStatus_Failure_NonExistantFile;
		
		return;
		
	}
	
	if ( ! IsOpen () )
	{
		
		Open ( Status );
		
		if ( * Status != File :: kStatus_Success )
			return;
		
	}
	
	uint64_t FileLength = GetLength ( Status );
	
	if ( * Status != File :: kStatus_Success )
		return;
	
	if ( FillFileGap )
	{
		
		if ( FileLength < FileOffset )
		{
			
			uint64_t GapSize = FileOffset - FileLength;
			
			uint64_t FillOffset = FileLength;
			uint64_t FillSize = ( GapSize >= 0x1000 ) ? 0x1000 : GapSize;
			
			void * FillBuffer = malloc ( static_cast <size_t> ( 0x1000 ) );
			
			if ( FillBuffer == NULL )
			{
				
				* Status = kStatus_Failure_OutOfMemory;
				
				return;
				
			}
			
			memset ( FillBuffer, FillChar, static_cast <size_t> ( FillSize ) );
			
			while ( FillOffset < FileOffset )
			{
				
				if ( FillOffset + FillSize > FileOffset )
					FillSize = FileOffset - FillOffset;
				
				Write ( FillBuffer, FillSize, FillOffset, Status );
				
				if ( * Status != File :: kStatus_Success )
					return;
				
				FillOffset += FillSize;
				
			}
			
			FileLength = FileOffset;
			
			free ( FillBuffer );
			
		}
		
	}
	else
	{
		
		if ( FileOffset > FileLength )
			FileOffset = FileLength;
		
	}
	
	Write ( reinterpret_cast <const void *> ( & String.c_str () [ StringOffset ] ), Length, FileOffset, Status );
	
	if ( * Status != File :: kStatus_Success )
		return;
	
}
