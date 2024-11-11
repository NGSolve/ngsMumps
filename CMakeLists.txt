cmake_minimum_required(VERSION 3.16)

# change this to your desired addon name
# make sure, that the name matches exactly the argument of PYBIND11_MODULE()
set(addon_name ngs_mumps)

project(${addon_name})
include(ngsolve_addon.cmake)
message("NEW INSTALL DIR ${CMAKE_INSTALL_PREFIX}")

# link_directories (AFTER MUMPS_5.7.3/lib)
link_directories (AFTER /usr/local/lib)

# change the source file arguments to your source files
add_ngsolve_addon(${addon_name} src/mumpsinverse.cpp src/ngsMumps.cpp)

include_directories (AFTER MUMPS_5.7.3/include)

# install the compiled python module and __init__.py ( don't change this )
install(TARGETS ${addon_name} DESTINATION ${addon_name})
install(FILES src/__init__.py DESTINATION ${addon_name})

# install additional python files/demos/examples
install(FILES demos/example1.py DESTINATION ${addon_name}/demos)

# generate stub files for autocomplete in IDEs
# this must be done at the very end (such that the stubgen generation happens after the python modules are installed)
# install(CODE ${stubgen_generation_code})
# install(DIRECTORY ${stubgen_directory} DESTINATION ${addon_name})


include(FetchContent)
set(BUILD_COMPLEX16 ON)
FetchContent_Declare(mumps
  GIT_REPOSITORY https://github.com/scivision/mumps.git 
  GIT_TAG main
)

FetchContent_GetProperties(mumps)
if(NOT mumps_POPULATED)
   message(STATUS "Fetching mumps ...")
   FetchContent_MakeAvailable(mumps)
   # Set EXCLUDE_FROM_ALL to avoid installing mumps files
   # add_subdirectory(${mumps_SOURCE_DIR}/src ${mumps_BINARY_DIR} EXCLUDE_FROM_ALL)
   # add_subdirectory(_deps/mumps-src)
endif()

# target_link_libraries(${addon_name} PRIVATE HYPRE)
# set_target_properties(HYPRE PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${addon_name} PUBLIC dmumps zmumps mumps_common)
# pord gfortran)
