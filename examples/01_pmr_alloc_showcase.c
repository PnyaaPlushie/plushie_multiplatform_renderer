#include "plushie/plushie_multiplatform_renderer.h"
#include "plushie_multiplatform_renderer_example_helper.h"

#include <stdio.h>

int main(void)
{
	void* ptr = g_pmr_exhelper_allocator_cpu.cpu_alloc(NULL, 600, "Test Alloc");
	void* name_clash_ptr = g_pmr_exhelper_allocator_cpu.cpu_alloc(NULL, 600, "Test Alloc");
	printf("We got back from allocator %p with name clashing\n", name_clash_ptr);
	void* unreleased_ptr= g_pmr_exhelper_allocator_cpu.cpu_alloc(NULL, 600, "Test Alloc(2)");

	g_pmr_exhelper_allocator_cpu.cpu_free(NULL, ptr);
	uint32_t count_unreleased = pmr_exhelper_check_for_unreleased();
	printf("We had %d unreleased memory allocations\n", count_unreleased);
}