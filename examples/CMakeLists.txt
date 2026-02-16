cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
project(PlushieMultiplatformRendererExample VERSION 0.1.0 LANGUAGES CXX C)

# Options for the examples, these will be applied at the end of the file 
# because decoding the command line args for these ends up looking tedious
option(PRMEX_ALLOC_REPORTING "Enable printf on allocation and frees" ON)
option(PRMEX_ALLOC_TRACKING "Track the names of allocations to report unreleased" ON)

# List of examples 
set(pmr_example_list
	libPlushieMultiplatformRenderer_ExampleHelper     # Shared helper lib
	libPlushieMultiplatformRenderer_Example_01_Alloc  # Shows how the example allocator behaves
	)

# Example helper library
add_library(libPlushieMultiplatformRenderer_ExampleHelper
	plushie_multiplatform_renderer_example_helper.h
	pmr_exhelper_allocator.cpp
	)

target_include_directories(libPlushieMultiplatformRenderer_ExampleHelper
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})


# Numbered examples 
add_executable(libPlushieMultiplatformRenderer_Example_01_Alloc
	01_pmr_alloc_showcase.c)


# Apply properties per example 
foreach(example_target ${pmr_example_list} )
	set_target_properties(${example_target} PROPERTIES 
		FOLDER "Plushie/MultiplatformRenderer/Example")

	if("${example_target}" STREQUAL "libPlushieMultiplatformRenderer_ExampleHelper")
		target_link_libraries(${example_target} PUBLIC 
			libPlushieMultiplatformRenderer)
	else()
		target_link_libraries(${example_target} PUBLIC 
			libPlushieMultiplatformRenderer_ExampleHelper)
	endif()

endforeach()


# Applying options to example lib 
if(${PRMEX_ALLOC_REPORTING})
	target_compile_definitions(libPlushieMultiplatformRenderer_ExampleHelper
		PUBLIC PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT=1)
else()
	target_compile_definitions(libPlushieMultiplatformRenderer_ExampleHelper
		PUBLIC PLUSHIE_EXAMPLE_HELPER_ALLOC_REPORT=0)
endif()

if(${PRMEX_ALLOC_TRACKING})
	target_compile_definitions(libPlushieMultiplatformRenderer_ExampleHelper
		PUBLIC PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP=1)
else()
	target_compile_definitions(libPlushieMultiplatformRenderer_ExampleHelper
		PUBLIC PLUSHIE_EXAMPLE_HELPER_ALLOC_NAME_LOOKUP=0)
endif()