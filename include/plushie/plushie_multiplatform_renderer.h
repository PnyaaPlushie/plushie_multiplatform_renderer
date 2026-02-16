#ifndef __PLUSHIE_MULTIPLATFORM_RENDERER_H__
#define __PLUSHIE_MULTIPLATFORM_RENDERER_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Forward declarations for structs
* acts as an atlas for structs we use 
*******************************************************************************/

struct PmrAllocatorCpu;


/******************************************************************************
* Allocator
*******************************************************************************/

typedef void* (*PmrAllocatorCpuUnalignedAlloc)(
	void* user_data, 
	size_t size, 
	const char* debug_name
	);

typedef void (*PmrAllocatorCpuFree)(
	void* user_data,
	void* ptr
	);

typedef struct PmrAllocatorCpu
{
	void* user_data;
	PmrAllocatorCpuUnalignedAlloc cpu_alloc;
	PmrAllocatorCpuFree cpu_free;
}
PmrAllocatorCpu;

/******************************************************************************
* End of API
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // __PLUSHIE_MULTIPLATFORM_RENDERER_H__