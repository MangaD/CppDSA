cmake_minimum_required(VERSION 3.16)

# Option to control building primary libraries and executables.
option(BUILD_SOURCE "Build primary libraries and executables." ON)

# Set project languages based on BUILD_SOURCE
set(PROJECT_LANGUAGES NONE)
if(BUILD_SOURCE)
    set(PROJECT_LANGUAGES CXX)
endif()

project(CppDSA LANGUAGES ${PROJECT_LANGUAGES})

# Enable C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not defined
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()

if(BUILD_SOURCE)

	# Optionally enable warnings
	if(MSVC)
		add_compile_options(/W4 /permissive-)
	else()
		add_compile_options(-Wall -Wextra -pedantic)
	endif()

	# Find packages from Conan (CMakeDeps generators will provide these config files)
	find_package(GTest REQUIRED)
	find_package(benchmark REQUIRED)

	# Benchmark targets
	add_executable(vector_benchmark src/vector_benchmark.cpp)
	target_link_libraries(vector_benchmark PRIVATE benchmark::benchmark_main)

	add_executable(list_benchmark src/list_benchmark.cpp)
	target_link_libraries(list_benchmark PRIVATE benchmark::benchmark_main)

	add_executable(sort_benchmark src/sort_benchmark.cpp)
	target_link_libraries(sort_benchmark PRIVATE benchmark::benchmark_main)

	add_executable(map_benchmark src/map_benchmark.cpp)
	target_link_libraries(map_benchmark PRIVATE benchmark::benchmark_main)

	add_executable(unordered_map_benchmark src/unordered_map_benchmark.cpp)
	target_link_libraries(unordered_map_benchmark PRIVATE benchmark::benchmark_main)

	add_executable(deque_benchmark src/deque_benchmark.cpp)
	target_link_libraries(deque_benchmark PRIVATE benchmark::benchmark_main)

	# Unit tests
	enable_testing()
	add_subdirectory(tests)
    
endif()

# Optionally generate Doxygen documentation
find_package(Doxygen)
include(cmake/doxygen.cmake)
