#ifndef COMPILATION_TARGETS_H
#define COMPILATION_TARGETS_H

typedef uint32_t TargetArchID;
typedef uint32_t TargetArchFlags;

typedef uint32_t TargetOSID;

const TargetOSID kTargetOS_Linux = 0;
const TargetOSID kTargetOS_Win32 = 1;
const TargetOSID kTargetOS_MacOS = 2;
const TargetOSID kTargetOS_NoOS = 3;

const TargetArchID kTargetArch_X86_32 = 0;
const TargetArchID kTargetArch_X86_64 = 1;

const TargetArchFlags kTargetArchFlag_X86_32_SSE2 = 1;

/*const TargetArchID kTargetArch_ARM_V6;
const TargetArchID kTargetArch_ARM_V7;
*/

#endif
