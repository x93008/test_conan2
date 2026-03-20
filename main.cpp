#include <iostream>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

enum class Color { RED, GREEN, BLUE };

int main() {
  // Test direct dependency: nlohmann_json
  std::cout << "nlohmann_json test" << std::endl;

  // Test transitive dependency: magic_enum (via nlohmann_json)
  // magic_enum is header-only library,    // Note: nlohmann_json uses
  // cpp_info.requires (NOT components) to depend on magic_enum
  std::cout << "magic_enum: " << magic_enum::enum_name(Color::RED) << std::endl;

  return 0;
}
