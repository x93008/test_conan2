cmake_minimum_required(VERSION 3.15)
project(test_conan2 CXX)

# Direct dependency: nlohmann_json/3.11.2 (header-only library)
# nlohmann_json optionally depends on magic_enum (header-only library)
# We try to use magic_enum directly (transitive dependency)
# This tests if CMakeDeps generates configs for transitive dependencies
# when package uses cpp_info.requires (NOT components)

# Check if magic_enum config was generated
message("magic_enum_FOUND: ${magic_enum_FOUND}")

if(NOT magic_enum_FOUND)
    # Try find_package
    find_package(magic_enum)
    if(magic_enum_FOUND)
        message("magic_enum found")
        if(TARGET magic_enum::magic_enum)
            message("magic_enum::magic_enum target exists")
        else()
            message("magic_enum::magic_enum target does NOT exist")
        endif()
    else()
        message("magic_enum not found - transitive dependency via cpp_info.requires")
    endif()
endif()

add_executable(main main.cpp)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

# Try to use magic_enum directly
if(magic_enum_FOUND)
    message("Linking magic_enum")
    target_link_libraries(main PRIVATE magic_enum::magic_enum)
endif()
