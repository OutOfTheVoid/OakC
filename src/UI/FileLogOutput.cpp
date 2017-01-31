#include <UI/FileLogOutput.h>

FileLogOutput :: FileLogOutput ( const std :: string & File ):
	OutputFile ( File, true )
{
	
	uint32_t DummyStatus;
	OutputFile.Open ( & DummyStatus, true );
	
}

FileLogOutput :: ~FileLogOutput ()
{
	
	uint32_t DummyStatus;
	
	OutputFile.Flush ( & DummyStatus );
	OutputFile.Close ( & DummyStatus );
	
}

void FileLogOutput :: Write ( const std :: string & Output )
{
	
	uint32_t DummyStatus;
	
	OutputFile.WriteSequential ( reinterpret_cast <const void *> ( Output.c_str () ), Output.size (), & DummyStatus );
	
}

void FileLogOutput :: WriteError ( const std :: string & Output )
{
	
	uint32_t DummyStatus;
	
	OutputFile.WriteSequential ( reinterpret_cast <const void *> ( Output.c_str () ), Output.size (), & DummyStatus );
	
}
