# Test Conan 2 CMakeDeps Transitive Dependency Behavior

This project tests how Conan 2.x CMakeDeps generates configuration files for transitive dependencies on Linux.

## Purpose

Investigate whether CMakeDeps generates `-config.cmake` files for transitive dependencies (dependencies of dependencies).

## Dependencies

- **Direct dependency**: libzip/1.11.4
- **Transitive dependencies** (via libzip):
  - BZip2
  - LibLZMA
  - OpenSSL
  - ZLIB
  - zstd

## Expected Behavior

Conan 2.x CMakeDeps should generate `-config.cmake` files for all dependencies in the dependency tree, including transitive dependencies.

## Build

```bash
# Clean previous builds
conan remove "test_conan2/*" -c

# Create package (rebuild test_conan2 and missing dependencies)
conan create . -b missing
```

## Verify Generated Configs

```bash
ls build/Debug/generators/*config.cmake
```

Expected output should include configs for both direct and transitive dependencies.
