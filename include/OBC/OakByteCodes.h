#ifndef OBC_OAKBYTECODES_H
#define OBC_OAKBYTECODES_H

#include <string>

#include <OIL/OilTypeReference.h>
#include <OIL/OilTypeDefinition.h>

typedef uint32_t OBCInstructionCode;

typedef struct
{
	
	uint32_t LocalCount;
	OilTypeReference ** LocalTypes;
	
} LocalStructureList;

typedef struct
{
	
	LocalStructureList LocalStructure;
	
} StackInstructionInfo;

typedef struct
{
	
	uint32_t SourceRegistration;
	uint32_t DestinationRegistration;
	
	uint32_t LocalOffset;
	
	std :: u32string * AbsoluteName;
	
	uint32_t ParameterNumber;
	
} RegistrationInstructionInfo;

typedef struct
{
	
	OBCInstructionCode InstructionCode;
	
	enum
	{
		
		StackInstructionInfo StackInfo;
		RegistrationInstructionInfo RegistrationInfo;
		
	};
	
} OBCInstruction;

//===============[ Instruction word layout ]===============//

// Instruction Type bitfield = b0-b7
const OBCInstructionCode kInstruction__Mask_Type = 0x000000FF;
const OBCInstructionCode kInstruction__Shift_Type = 0;

// Instruction Index bitfield = b8-b15
const OBCInstructionCode kInstruction__Mask_Index = 0x0000FF00;
const OBCInstructionCode kInstruction__Shift_Index = 8;

// Instruction flags bitfield = b16-b23
const OBCInstructionCode kInstruction__Mask_Flags = 0x00FF0000;
const OBCInstructionCode kInstruction__Shift_Flags = 8;

//----------------[ Instruction word types ]----------------//

// Stack operations
const OBCInstructionCode kInstruction__Type_Stack = 0x00;
// Registration operations
const OBCInstructionCode kInstruction__Type_Registration = 0x01;

//===============[ Instructions ]===============//

//----------------[ Stack instructions ]----------------//

// Pushes a local block specified by the StackInfo.LocalStructure.
const OBCInstructionCode kInstruction_Push_LocalBlock = ( 0x00 << kInstruction__Shift_Index ) | ( kInstruction__Type_Stack );
// Pops the last local block
const OBCInstructionCode kInstruction_Pop_LocalBlock = ( 0x01 << kInstruction__Shift_Index ) | ( kInstruction__Type_Stack );

//----------------[ Registration instructions ]----------------//

// Registers a local <LocalOffset> (negative relative to the top of the local stack) to a registration <DestinationRegistration>.
const OBCInstructionCode kInstruction_Register_FromRelativeLocal = ( 0x00 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );
// Registers a non-local at <AbsoluteName> to a registration <DestinationRegistration>.
const OBCInstructionCode kInstruction_Register_FromNonLocal = ( 0x01 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );
// Registers a parameter at <ParameterNumber> to a registration <DestinationRegistration>.
const OBCInstructionCode kInstruction_Register_FromNonLocal = ( 0x02 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );
// Registers the function return value to registration <DestinationRegistration>.
const OBCInstructionCode kInstruction_Register_FromNonLocal = ( 0x03 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );


// Reference the target of <SourceRegistration>, and register that at <DestinationRegistration>.
const OBCInstructionCode kInstruction_Register_Dereference = ( 0x04 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );
// Dereference the target of <SourceRegistration>, and register that at <DestinationRegistration>.
const OBCInstructionCode kInstruction_Register_Reference = ( 0x05 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );

// Move the contents referenced by <SourceRegistration> to <DestinationRegistration>.
const OBCInstructionCode kInstruction_Register_Move = ( 0x06 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );

// Clears a registration at <DestinationRegistration>.
const OBCInstructionCode kInstruction_UnRegister = ( 0x07 << kInstruction__Shift_Index ) | ( kInstruction__Type_Registration );



#endif
