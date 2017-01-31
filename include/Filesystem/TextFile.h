#ifndef FILESYSTEM_TEXTFILE_H
#define FILESYSTEM_TEXTFILE_H

#include <Filesystem/File.h>

class TextFile : public File
{
public:
	
	/// Non existant file
	static const uint32_t kStatus_Failure_NonExistantFile = 10;
	/// File bounds overrun
	static const uint32_t kStatus_Failure_FileBounds = 11;
	/// String bounds overrun
	static const uint32_t kStatus_Failure_StringBounds = 12;
	
	/**
	 * @brief Constructs a TextFile
	 *
	 * @param Name The file path
	 * @param Writable Whether the file is writable
	 */
	TextFile ( const std :: string & Name, bool Writable = false );
	
	/// Copy constructor.
	TextFile ( const TextFile & CopyFrom );
	
	// Destructor.
	~TextFile ();
	
	/**
	 * @brief Reads to string.
	 * @details Reads a portion of the file to a string.
	 *
	 * @param Status A pointer to a variable where the operation status will be written
	 * @param String The string to read into
	 * @param Offset The offset in the file to read from
	 * @param Length The number of chars to read
	 * @param TrimToFileEdge Whether to trim read length to the file's edge
	 */
	void ReadToString ( uint32_t * Status, std :: string & String, uint64_t Offset, uint64_t Length = 0xFFFFFFFFFFFFFFFF, bool TrimToFileEdge = true );
	
	/**
	 * @brief Writes from string.
	 * @details Writes a portion of the file from a string.
	 *
	 * @param Status A pointer to a variable where the operation status will be written
	 * @param String The string to write from
	 * @param StringOffset The offset in the string to read from
	 * @param FileOffset The offset in the file to write to
	 * @param Length The number of chars to write (defaults to the length of the string)
	 * @param FillFileGap Whether to fill a gap in the file between it's length and the intended writing position, if it exists (defaults to false)
	 * @
	 */
	void WriteFromString ( uint32_t * Status, const std :: string & String, uint64_t StringOffset, uint64_t FileOffset, uint64_t Length = 0xFFFFFFFFFFFFFFFF, bool FillFileGap = false, char FillChar = ' ' );	
	
};

#endif
