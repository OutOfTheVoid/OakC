#ifndef COMPILATION_TARGETS_H
#define COMPILATION_TARGETS_H

#include <stdint.h>

typedef uint32_t TargetArchID;
typedef uint32_t TargetArchFlags;

typedef uint32_t TargetOSID;

#define TARGET_OS_NAME_NONE "none"
#define TARGET_OS_NAME_GNULINUX "gnu_linux"
#define TARGET_OS_NAME_WIN32 "windows"
#define TARGET_OS_NAME_MACOSX "macosx"

const TargetOSID kTargetOS_None = 0;
const TargetOSID kTargetOS_GNULinux = 1;
const TargetOSID kTargetOS_Win32 = 2;
const TargetOSID kTargetOS_MacOSX = 3;

#define TARGET_ARCH_NAME_X86 "x86"
#define TARGET_ARCH_NAME_X86_64 "x86_64"

const TargetArchID kTargetArch_X86_32 = 0;
const TargetArchID kTargetArch_X86_64 = 1;

const TargetArchID kTargetArch_Undefined = 0xFFFFFFFF;

const TargetArchFlags kTargetArchFlag_X86_32_SSE2 = 1;
const TargetArchFlags kTargetArchFlag_X86_32_SSE3 = 2;

/*const TargetArchID kTargetArch_ARM_V6;
const TargetArchID kTargetArch_ARM_V7;
*/

#define TARGET_HOST_ARCH_FLAGS 0

#ifndef TARGET_HOST_ARCH

	#if defined __x86_64 || defined __x86_64__ || defined __amd64 || defined __amd64__ || defined _M_X64 || defined _M_AMD64
		#define TARGET_HOST_ARCH kTargetArch_X86_64
	#endif
	
	#elif defined __i386__ || defined __i386 || defined i386 || defined __IA32__ || defined _M_IX86 || defined __X86__ || defined _X86_ || defined __386
		#define TARGET_HOST_ARCH kTargetArch_X86_32
		
		#ifdef __SSE2__
			#define TARGET_HOST_ARCH_FLAGS ( TARGET_HOST_ARCH_FLAGS | kTargetArchFlag_X86_32_SSE2 )
		#endif
		
		#ifdef __SSE3__
			#define TARGET_HOST_ARCH_FLAGS ( TARGET_HOST_ARCH_FLAGS | kTargetArchFlag_X86_32_SSE3 )
		#endif
		
	#else
		#define TARGET_HOST_ARCH kTargetArch_Undefined
	
	#endif
	
#endif

#ifndef TARGET_HOST_OS
	
	#if defined __gnu_linux__
		#define TARGET_HOST_OS kTargetOS_GNULinux
	
	#elif defined _WIN32 || defined __WIN32__
		#define TARGET_HOST_OS kTargetOS_Win32
	
	#elif defined __APPLE__ && defined __MACH__
		#define TARGET_HOST_OS kTargetOS_MacOSX

	#ifndef TARGET_HOST_OS
		#define TARGET_HOST_OS kTargetOS_None

	#endif
	
#endif

extern TargetOSID TargetOS;
extern TargetArchID TargetArch;
extern TargetArchFlags TargetFlags;

#endif
