#define _LARGEFILE64_SOURCE
#define _CRT_SECURE_NO_WARNINGS

#include <Filesystem/File.h>

#include <sys/stat.h>
#include <sys/types.h>

#ifndef _WIN32
	#include <unistd.h>
#endif

#include <stdio.h>
#include <errno.h>

File :: File ( const std :: string & Name, bool Writable ):
	Name ( Name ),
	Writable ( Writable ),
	Opened ( false ),
	Handle ( NULL )
{	
}

File :: File ( const File & CopyFrom ):
	Name ( CopyFrom.Name ),
	Writable ( CopyFrom.Writable ),
	Opened ( false ),
	Handle ( NULL )
{
}

File :: ~File ()
{
	
	uint32_t DummyStatus;
	
	Close ( & DummyStatus );
	
}

bool File :: IsOpen () const
{
	
	return Opened;
	
}
		
bool File :: IsWritable () const
{
	
	return Writable;
	
}

bool File :: Exists () const
{
	
#if defined ( __APPLE__ )
	
	struct stat FStatData;
	
#elif defined ( _WIN32 )
	
	struct __stat64 FStatData;
	
#else
	
	struct stat64 FStatData;
	
#endif
	
	int ReturnCode;
	
	if ( Opened )
	{
		
#ifdef _WIN32
		
		int FD = _fileno ( Handle );
		
#else
		
		int FD = fileno ( Handle );
		
#endif
		
		if ( FD == - 1 )
			return false;
		
#if defined ( __APPLE__ )
		
		ReturnCode = fstat ( FD, & FStatData );

#elif defined ( _WIN32 )
		
		ReturnCode = _fstat64 ( FD, & FStatData );

#else
		
		ReturnCode = fstat64 ( FD, & FStatData );
		
#endif
		
	}
	else
	{
		
#if defined ( __APPLE__ )
		
		ReturnCode = stat ( Name.c_str (), & FStatData );
		
#elif defined ( _WIN32 )
		
		ReturnCode = _stat64 ( Name.c_str (), & FStatData );
		
#else
		
		ReturnCode = stat64 ( Name.c_str (), & FStatData );
		
#endif
		
	}
	
	if ( ReturnCode == - 1 )
		return false;
	
	return true;
	
}


void File :: Open ( uint32_t * Status, bool Overwrite )
{
	
	if ( Opened )
	{
		
		* Status = kStatus_Failure_FileAlreadyOpen;
		
		return;
		
	}
	
#if defined ( __APPLE__ )
	
	Handle = fopen ( Name.c_str (), Writable ? ( Overwrite ? "w+b" : "a+b" ) : "rb" );
	
#elif defined ( _WIN32 )
	
	Handle = fopen ( Name.c_str (), Writable ? ( Overwrite ? "w+b" : "a+b" ) : "rb" );
	
#else
	
	Handle = fopen64 ( Name.c_str (), Writable ? ( Overwrite ? "w+b" : "a+b" ) : "rb" );
	
#endif
	
	if ( Handle != NULL )
	{
		
		Opened = true;
		
		* Status = kStatus_Success;
		
	}
	else
	{
		
		switch ( errno )
		{
			
		case EINVAL:
			* Status = kStatus_Failure_FileModeIncompatible;
			break;
			
		case ENOMEM:
			* Status = kStatus_Failure_OutOfMemory;
			break;
			
		case EACCES:
			* Status = kStatus_Failure_Permissions;
			break;
			
		case EFAULT:
			* Status = kStatus_Failure_InvalidParam;
			break;
			
		case EISDIR:
			* Status = kStatis_Failure_FileIsDirectory;
			break;
			
		default:
			* Status = kStatus_Failure_Unknown;
			break;
			
		}
		
	}
	
}

void File :: SetWritable ( uint32_t * Status, bool Writable, bool Overwrite )
{
	
	if ( ( this -> Writable == Writable ) && ( ! Overwrite ) )
	{
		
		* Status = kStatus_Success;
		
		return;
		
	}
	
	if ( Opened )
	{
		
		Close ( Status );
	
		if ( * Status != kStatus_Success )
			return;
		
		this -> Writable = Writable;
		
		Open ( Status, Overwrite );
		
		return;
		
	}
	
	this -> Writable = Writable;
	
}

void File :: Close ( uint32_t * Status )
{
	
	* Status = kStatus_Success;
	
	if ( ! Opened )
	{
		
		* Status = kStatus_Failure_FileNotOpen;
		
		return;
		
	}
	
#if defined ( __APPLE__ )
	
	fclose ( Handle );
	
#elif defined ( _WIN32 )
	
	fclose ( Handle );
	
#else
	
	fclose ( Handle );
	
#endif
	
	Opened = false;
	Handle = NULL;
	
}

void File :: Seek ( uint32_t * Status, int64_t Position, SeekMode Mode )
{
	
	if ( ! Opened )
	{
		
		* Status = kStatus_Failure_FileNotOpen;
		
		return;
		
	}
	
#if defined ( __APPLE__ )
	
	if ( fseek ( Handle, Position, Mode ) == 0 )
		* Status = kStatus_Success;
	else
		* Status = kStatus_Failure_IOError;
	
#elif defined ( _WIN32 )
	
	if ( _fseeki64 ( Handle, Position, Mode ) == 0 )
		* Status = kStatus_Success;
	else
		* Status = kStatus_Failure_IOError;
	
#else
	
	int FD = fileno ( Handle );
	
	if ( FD == - 1 )
	{

		* Status = kStatus_Failure_FileNotOpen;

		return;

	}
	
	if ( lseek64 ( FD, Position, Mode ) == 0 )
		* Status = kStatus_Success;
	else
		* Status = kStatus_Failure_IOError;
	
#endif
	
}

int64_t File :: ReadSequential ( void * Buffer, uint64_t Length, uint32_t * Status )
{
	
	if ( ! Opened )
	{
		
		* Status = kStatus_Failure_FileNotOpen;
		
		return - 1;
		
	}
	
	int64_t ReadSize = fread ( Buffer, 1, Length, Handle );
	
	if ( ReadSize > 0 )
		* Status = kStatus_Success;
	else
		* Status = kStatus_Failure_IOError;
	
	return ReadSize;
	
}

int64_t File :: WriteSequential ( const void * Buffer, uint64_t Length, uint32_t * Status )
{
	
	if ( ! Opened )
	{
		
		* Status = kStatus_Failure_FileNotOpen;
		
		return - 1;
		
	}
	
	if ( ! Writable )
		* Status = kStatus_Failure_Permissions;
	
	int64_t ReadSize = fwrite ( Buffer, 1, Length, Handle );
	
	if ( ReadSize > 0 )
		* Status = kStatus_Success;
	else
		* Status = kStatus_Failure_IOError;
	
	return ReadSize;
	
}

int64_t File :: Read ( void * Buffer, uint64_t Length, int64_t Offset, uint32_t * Status )
{
	
	* Status = kStatus_Success;
	
	Seek ( Status, Offset, kSeekMode_Absolute );
	
	if ( * Status != kStatus_Success )
		return - 1;
	
	int64_t ReadSize = fread ( Buffer, Length, 1, Handle );
	
	if ( ReadSize != 1 )
		* Status = kStatus_Failure_IOError;
	
	return ReadSize;
	
}

int64_t File :: Write ( const void * Buffer, uint64_t Length, int64_t Offset, uint32_t * Status )
{
	
	* Status = kStatus_Success;
	
	Seek ( Status, Offset, kSeekMode_Absolute );
	
	if ( * Status != kStatus_Success )
		return - 1;
	
	int64_t ReadSize = fwrite ( Buffer, Length, 1, Handle );
	
	if ( ReadSize != 1 )
		* Status = kStatus_Failure_IOError;
	
	return ReadSize;
	
}

void File :: Flush ( uint32_t * Status )
{
	
	if ( ! Opened )
	{
		
		* Status = kStatus_Failure_FileNotOpen;
		
		return;
		
	}
	
	if ( fflush ( Handle ) == 0 )
		* Status = kStatus_Success;
	else
		* Status = kStatus_Failure_IOError;
	
}

int64_t File :: GetLength ( uint32_t * Status ) const
{
	
	* Status = kStatus_Success;
	
#if defined ( __APPLE__ )
	
	struct stat FStatData;
	
#elif defined ( _WIN32 )
	
	struct __stat64 FStatData;
	
#else
	
	struct stat64 FStatData;
	
#endif
	
	int ReturnCode;
	
	if ( Opened )
	{
		
#ifdef _WIN32
		
		int FD = _fileno ( Handle );
		
#else
		
		int FD = fileno ( Handle );
		
#endif
		
		if ( FD == - 1 )
		{
			
			* Status = kStatus_Failure_FileNotOpen;
			
			return - 1;
			
		}
		
#if defined ( __APPLE__ )
		
		ReturnCode = fstat ( FD, & FStatData );

#elif defined ( _WIN32 )
		
		ReturnCode = _fstat64 ( FD, & FStatData );

#else
		
		ReturnCode = fstat64 ( FD, & FStatData );
		
#endif
		
	}
	else
	{
		
#if defined ( __APPLE__ )
		
		ReturnCode = stat ( Name.c_str (), & FStatData );
		
#elif defined ( _WIN32 )
		
		ReturnCode = _stat64 ( Name.c_str (), & FStatData );
		
#else
		
		ReturnCode = stat64 ( Name.c_str (), & FStatData );
		
#endif
		
	}
	
	if ( ReturnCode == - 1 )
		* Status = kStatus_Failure_Unknown;
	
	return FStatData.st_size;
	
}

FILE * File :: GetFilePointer () const
{
	
	return Handle;
	
}

const std :: string & File :: GetName () const
{
	
	return Name;
	
}
