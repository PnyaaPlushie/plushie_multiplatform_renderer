# Plushie Multiplatform Renderer 🧸🌈

*Attempting to create a cross-platform allocator agnostic renderer, eventually I plan to  support cross language api bindings, but for now we're focusing on vulkan*

The interface for the project is written in C, and the library itself is written in C. However, you might see the examples borrowing some features from C++ just to get things going quicker

## Build instructions

This project is cmake driven 

```bash
mkdir build

# Configure using cmake, options are listed below 
# but all derive a usable defuale
cmake -S . -B build <... Options ...>

# Build all targets
cmake --build build

# Optional install process
cmake --install build --prefix <Install location>
```

CMake configuration options (When configuring on the command line put a -D infront of the option name to define it)

| CMake Option         | Description                                                                                      | Default            |
| -------------------- | ------------------------------------------------------------------------------------------------ | ------------------ |
| PMR_BUILD_EXAMPLES   | Should examples be included in the build tree                                                    | ON                 |
| PRM_INSTALL_EXAMPLES | Should examples also be added to the install target, so that they copied to the install location | PMR_BUILD_EXAMPLES |

If you are building the examples, there are additional options you can configure 

| CMake Option          | Description                                                                                                                                                              | Default |
| --------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------- |
| PRMEX_ALLOC_REPORTING | Should the default allocator in the examples report on each allocation and free? Effects performance                                                                     | ON      |
| PRMEX_ALLOC_TRACKING  | Should the default allocator in the examples track the names used for each allocation? Effects performance but is useful for ensuring we don't leave anything unreleased | ON      |

## Current process

Right now, I'm doing example driven development focusing on just bringing up the vulkan on windows backend, then we'll see if we can make it cross platform and extend beyond simple examples.
