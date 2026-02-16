/******************************************************************************
* @brief Example helper for allocating memory 
* We're not doing anything fancy, but we are going to borrow C++ to track the 
* allocations by name. This way when developing examples, I can track 
* allocation lifetimes
* 
* Actual allocations are just made with malloc and free
*******************************************************************************/
#include "plushie_multiplatform_renderer_example_helper.h"
#include <stdlib.h>

// Should examples keep a map of allocations for debugging
#ifndef PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP
#  define PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP 1
#endif 

// should examples report when they alloc and when they free
#ifndef PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
#  define PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT 1
#endif


#if PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP
#  include <unordered_map>
#  include <string>
#  include <mutex>
static std::mutex m_mutex;
static std::unordered_map<void*, std::string> s_ptr_name_lookup;
static std::unordered_map<std::string, void*> s_name_ptr_lookup;
#endif 

#if PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
#  include <stdio.h>
#endif


static void* s_example_alloc(
	void* user_data,
	size_t size,
	const char* debug_name
)
{
	(void)user_data;
	
	// Early escape for a failed alloc
	void* ptr = malloc(size);
	if (ptr == nullptr) return nullptr;

	// Early escape to return pointer if no debug name
	if (debug_name == nullptr) return ptr;

	// Tell user we allocated?
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
	printf("[PlushieExample::Alloc] \"%s\" as %p for %zu bytes\n", debug_name, ptr, size);
#endif 

	// Keep record of the alloc?
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP
	
	// Check that we didn't already have this name, as a drastic messure to ensure naming well
	// I make the examples return a nullptr if the name already exists
	m_mutex.lock();
	auto lookup_name = s_name_ptr_lookup.find(debug_name);
	if (lookup_name != s_name_ptr_lookup.end())
	{
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
		printf("[PlushieExample::Alloc] \"%s\" as %p released due to a naming collision\n", debug_name, ptr);
#endif 
		free(ptr);
		m_mutex.unlock();
		return nullptr;
	}

	// Add name
	s_name_ptr_lookup[debug_name] = ptr;
	s_ptr_name_lookup[ptr] = debug_name;

	// unlock 
	m_mutex.unlock();
#endif 

	// Return to caller 
	return ptr;
}

void s_example_free(
	void* user_data,
	void* ptr
)
{
	(void)user_data;
	free(ptr);

	// Did we keep record of alloc?
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP

	// Lookup the ptr, escape if we didn't have it
	m_mutex.lock();
	auto lookup_ptr = s_ptr_name_lookup.find(ptr);
	if (lookup_ptr == s_ptr_name_lookup.end())
	{
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
		printf("[PlushieExample::Alloc] Ptr %p didn't have a name in the list, suspect double free\n", ptr);
#endif
		m_mutex.unlock();
		return;
	}

	// Remove from the ptr lookup and inform to the user 
	auto str = lookup_ptr->second;
	s_ptr_name_lookup.erase(lookup_ptr);
	const char* debug_name = str.c_str();
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
	printf("[PlushieExample::Alloc] \"%s\" released was %p\n",debug_name , ptr);
#endif 

	// We should also remove from name to ptr 
	s_name_ptr_lookup.erase(debug_name);

	// release lock
	m_mutex.unlock();
#else 
	// Should we report even without name lookup?
#  if PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
	printf("[PlushieExample::Alloc] released memory %p\n", ptr);
#  endif

#endif
}


extern "C" uint32_t pmr_exhelper_check_for_unreleased()
{
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP

	m_mutex.lock();
#if PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT
	for (const auto& unreleased : s_name_ptr_lookup)
	{
		printf("[PlushieExample::Alloc] unreleased ptr \"%s\"\n", unreleased.first.c_str());
	}
#endif 

	uint32_t unreleased_count = s_name_ptr_lookup.size();
	m_mutex.unlock();
	return unreleased_count;
#else
	// No name tracking, don't report anything
	return 0;
#endif


}


extern "C" PmrAllocatorCpu g_pmr_exhelper_allocator_cpu =
{
	NULL,
	s_example_alloc,
	s_example_free,
};