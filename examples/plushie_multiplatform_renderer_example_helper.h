#ifndef __PLUSHIE_MULTIPLATFORM_RENDERER_EXAMPLE_HELPER_H__
#define __PLUSHIE_MULTIPLATFORM_RENDERER_EXAMPLE_HELPER_H__
#include "plushie/plushie_multiplatform_renderer.h"

#ifdef __cplusplus
extern "C" {
#endif



/**
* @brief Default allocator which the examples all use
*/
extern PmrAllocatorCpu g_pmr_exhelper_allocator_cpu;

/**
* @brief Checks that we didn't leave any unallocated memory
* @returns the number of unreleased memory allocations, so 0 for success
*/
uint32_t pmr_exhelper_check_for_unreleased();


#ifdef __cplusplus
}
#endif
#endif // __PLUSHIE_MULTIPLATFORM_RENDERER_EXAMPLE_HELPER_H__