# Test Conan 2 CMakeDeps Transitive Dependency Bug

This project demonstrates a bug in Conan 2.x CMakeDeps where transitive dependencies (via `cpp_info.requires`, NOT `components.requires`) are NOT accessible.

## Problem Statement

When:
1. Project A directly depends on `nlohmann_json/3.11.2` (header-only library)
2. `nlohmann_json` transitively depends on `magic_enum` via `cpp_info.requires`
3. Project A tries to use `magic_enum` directly (`find_package(magic_enum)`)

**Result**: CMakeDeps does NOT generate `magic_enum-config.cmake`, causing `find_package(magic_enum)` to FAIL.

## Key Difference

### This Test (FAILS)
- **nlohmann_json** uses: `cpp_info.requires = ["magic_enum::magic_enum"]`
- Package-level dependency (NO components)
- **CMakeDeps does NOT generate config for magic_enum**

### libzip Test (WORKS)
- **libzip** uses: `cpp_info.components["zip"].requires = ["zlib::zlib"]`
- Component-level dependency
- **CMakeDeps DOES generate config for zlib**

## Root Cause

Conan 2.x CMakeDeps only generates CMake config files for transitive dependencies when they are declared via **component-level** `requires` (`cpp_info.components["xxx"].requires`), NOT package-level `requires` (`cpp_info.requires`).

## Demonstration

```bash
conan create . --build missing
```

Output:
```
magic_enum_FOUND: 
magic_enum not found - transitive dependency via cpp_info.requires
```

## Workaround

If you need to use a transitive dependency directly, declare it as a **direct** dependency in your `conanfile.py`:

```python
def requirements(self):
    self.requires("nlohmann_json/3.11.2")
    self.requires("magic_enum/0.9.6")  # Add direct dependency
```

## Related Conan Issues

- https://github.com/conan-io/conan2/issues/19783
- https://github.com/conan-io/conan2/issues/19358

## Files

- `conanfile.py` - Conan recipe with `nlohmann_json` dependency
- `CMakeLists.txt` - CMake configuration attempting to `find_package(magic_enum)`
- `main.cpp` - Test code using both libraries
