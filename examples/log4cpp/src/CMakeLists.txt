include(maven.cmake)

# Usage of FILE_SET requires cmake version 3.23
cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(log4cpp VERSION ${VERSION} DESCRIPTION "A logger that may wreak havoc in the future" LANGUAGES CXX)

# Collect all cpp source files
file(GLOB_RECURSE Sources LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS *.cpp)

add_library(log4cpp ${Sources})

# Note that each public header file is added individually, 
# if you want a header to be visible to dependent projects, you must add it below
target_sources(log4cpp PUBLIC FILE_SET HEADERS FILES log.h)

# To create correct namelinks of the library on installation directory, we need to set version attributes
set_target_properties(
  log4cpp PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

# Generate Config and Version cmake files
include(CMakePackageConfigHelpers)
configure_package_config_file(log4cppConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/log4cppConfig.cmake
  INSTALL_DESTINATION lib/cmake/log4cpp
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/log4cppConfigVersion.cmake
  COMPATIBILITY SameMajorVersion)

# Install built files and headers
include(GNUInstallDirs)
install(TARGETS log4cpp EXPORT log4cppTargets # This somehow makes these directories visible as targer properties on downstream project
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT log4cpp_Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT log4cpp_Runtime
    NAMELINK_COMPONENT log4cpp_Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT log4cpp_Development
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/log4cpp
    COMPONENT log4cpp_Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

# Install libConfig.cmake file which will be used by downstream project
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/log4cppConfig.cmake DESTINATION lib/cmake/log4cpp)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/log4cppConfigVersion.cmake DESTINATION lib/cmake/log4cpp)

# Install libTarget.cmake file which will include target properties. (Include dirs etc.)
install(EXPORT log4cppTargets
  FILE
    log4cppTargets.cmake
  NAMESPACE
    log4cpp::
  DESTINATION
    lib/cmake/log4cpp
)
target_compile_definitions(log4cpp PRIVATE BUILD_INFO="$<CONFIG>")
target_compile_definitions(log4cpp PRIVATE VERSION="${PROJECT_VERSION}")

include(CPack)

