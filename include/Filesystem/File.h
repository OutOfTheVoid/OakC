#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

#include <stdint.h>
#include <stdio.h>

#include <string>

class File
{
public:
	
	typedef int SeekMode;
	
	/// Absolute seek: Seek from position 0 forward
	static const SeekMode kSeekMode_Absolute = SEEK_SET;
	/// Relative seek: Seek from current position forward
	static const SeekMode kSeekMode_Relative = SEEK_CUR;
	/// From End seek: Seek from the end backward
	static const SeekMode kSeekMode_FromEnd = SEEK_END;
	
	/// Operation successful
	static const uint32_t kStatus_Success = 0;
	/// Unknown failure
	static const uint32_t kStatus_Failure_Unknown = 1;
	
	/// Incompatible file mode
	static const uint32_t kStatus_Failure_FileModeIncompatible = 2;
	/// System out of memory
	static const uint32_t kStatus_Failure_OutOfMemory = 3;
	/// Permission mismatch
	static const uint32_t kStatus_Failure_Permissions = 4;
	/// Invalid parameter
	static const uint32_t kStatus_Failure_InvalidParam = 5;
	/// File is a directory
	static const uint32_t kStatis_Failure_FileIsDirectory = 6;
	/// File is not open
	static const uint32_t kStatus_Failure_FileNotOpen = 7;
	/// File is already open
	static const uint32_t kStatus_Failure_FileAlreadyOpen = 8;
	/// IO Error
	static const uint32_t kStatus_Failure_IOError = 9;
	
	/**
	 * @brief Constructs a File object.
	 * 
	 * @param Name The path to the file handled
	 * @param Writable Whether the file is to be opened in writable mode
	 */
	File ( const std :: string & Name, bool Writable = false );
	
	/**
	 * @brief Copy constructor.
	 * 
	 * @param Name The File instance to copy
	 */
	File ( const File & CopyFrom );
	
	/// Destructor.
	~File ();
	
	/// Sets the path.
	void SetName ( const std :: string & Name );
	
	/// Whether the file exists.
	bool Exists () const;
	
	/**
	 * @brief Opens the file.
	 * @details Opens the file, optionally for overwriting.
	 * 
	 * @param Status A pointer to a varibale to store the operation status
	 * @param Overwrite Whether or not to open the file in overwrite mode
	 */
	void Open ( uint32_t * Status, bool Overwrite = false );
	
	/// Closes the file.
	void Close ( uint32_t * Status );
	
	/// Whether the file is open.
	bool IsOpen () const;
	
	/**
	 * @brief Seeks the file
	 * @details Sets the position for sequential reading/writing.
	 * 
	 * @param Status A pointer to a varibale to store the operation status
	 * @param Position The posision offset, relative to the seek mode base
	 * @param Mode Where to seek from. ( Absolute means from 0, Relative means relative to the current posisiotn, and FromEnd means backwards form the end.)
	 */
	void Seek ( uint32_t * Status, int64_t Position, SeekMode Mode = kSeekMode_Absolute );
	
	/// Whether the file is writable.
	bool IsWritable () const;
	
	/**
	 * @brief Sets the file writability.
	 * @details Reopens the file with specified writability and overwrite mode.
	 * 
	 * @param Status A pointer to a varibale to store the operation status
	 * @param Writable Whether to open the file in writable mode
	 * @param Overwrite Whether the file should be overwritten
	 */
	void SetWritable ( uint32_t * Status, bool Writable = true, bool Overwrite = true );
	
	/**
	 * @brief Reads data to the file sequentially.
	 * @details Reads the file from the offset specified by the seek position, and increments it by the read length.
	 * 
	 * @param Buffer A pointer to the buffer to read data to
	 * @param Length The amount of data to read (at most)
	 * @param Status A pointer to a varibale to store the operation status
	 * @return The number of bytes that were read
	 */
	int64_t ReadSequential ( void * Buffer, uint64_t Length, uint32_t * Status );
	
	/**
	 * @brief Writes data to the file sequentially.
	 * @details Writes the file from the offset specified by the seek position, and increments it by the read length.
	 * 
	 * @param Buffer A pointer to the buffer to write data from
	 * @param Length The number of bytes to write
	 * @param Status A pointer to a varibale to store the operation status
	 * @return The number of bytes that were written
	 */
	int64_t WriteSequential ( const void * Buffer, uint64_t Length, uint32_t * Status );
	
	/**
	 * @brief Writes data to the file.
	 * @details Writes data to the file from the specified offset.
	 * 
	 * @param Buffer A pointer to the buffer to write data from
	 * @param Length The number of bytes to write
	 * @param Offset The position in the file from which to write
	 * @param Status A pointer to a varibale to store the operation status
	 * @return The number of bytes that were written
	 */
	int64_t Write ( const void * Buffer, uint64_t Length, int64_t Offset, uint32_t * Status );
	
	/**
	 * @brief Reads data from the file.
	 * @details Reads the file from the offset specified by the seek position, and increments it by the read length.
	 * 
	 * @param Buffer A pointer to the buffer to read data to
	 * @param Length The amount of data to read (at most)
	 * @param Offset The position to read from in the file
	 * @param Status A pointer to a varibale to store the operation status
	 * @return The number of bytes that were read
	 */
	int64_t Read ( void * Buffer, uint64_t Length, int64_t Offset, uint32_t * Status );
	
	/**
	 * @brief Flush the file.
	 * @details Ensures all IO operations on the file are finished.
	 * 
	 * @param Status A pointer to a varibale to store the operation status
	 */
	void Flush ( uint32_t * Status );
	
	/**
	 * @brief Gets the length of the file.
	 * @details Gets the length of the file.
	 * 
	 * @param Status A pointer to a varibale to store the operation status
	 * @return The length of the file
	 */
	int64_t GetLength ( uint32_t * Status ) const;
	
	/// Get the native file pointer.
	FILE * GetFilePointer () const;
	
	/// Gets the path of the file.
	const std :: string & GetName () const;
	
private:
	
	std :: string Name;
	
	bool Writable;
	bool Opened;
	
	FILE * Handle;
	
};

#endif
