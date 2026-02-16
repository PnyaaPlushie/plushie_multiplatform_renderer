cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
project(PlushieMultiplatformRenderer VERSION 0.1.0 LANGUAGES CXX C)
include(CMakeDependentOption)

option(PMR_BUILD_EXAMPLES "Should we include examples in the build tree" ON)
cmake_dependent_option(PRM_INSTALL_EXAMPLES "Should examples be added to install targets"
                            ON PMR_BUILD_EXAMPLES OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(libPlushieMultiplatformRenderer
	include/plushie/plushie_multiplatform_renderer.h
	include/plushie/internal/plushie_multiplatform_renderer_internal.h
	source/pmr_alloc_calliing.c
	)

target_include_directories(libPlushieMultiplatformRenderer
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

set_target_properties(libPlushieMultiplatformRenderer PROPERTIES 
	FOLDER "Plushie/MultiplatformRenderer")

if(${PMR_BUILD_EXAMPLES})
	add_subdirectory(examples)
endif()