include(maven.cmake)

# Usage of FILE_SET requires cmake version 3.23
cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(messages VERSION ${VERSION} DESCRIPTION "A logger that may wreak havoc in the future" LANGUAGES CXX)

# Collect all cpp source files
file(GLOB_RECURSE Sources LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS *.cpp)

add_library(messages ${Sources})
set_property(TARGET messages PROPERTY CXX_STANDARD 23)

# Note that each public header file is added individually, 
# if you want a header to be visible to dependent projects, you must add it below
target_sources(messages PUBLIC FILE_SET HEADERS FILES important_message.h)

# To create correct namelinks of the library on installation directory, we need to set version attributes
set_target_properties(
  messages PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

# Generate Config and Version cmake files
include(CMakePackageConfigHelpers)
configure_package_config_file(messagesConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/messagesConfig.cmake
  INSTALL_DESTINATION lib/cmake/messages
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/messagesConfigVersion.cmake
  COMPATIBILITY SameMajorVersion)

# Install built files and headers
include(GNUInstallDirs)
install(TARGETS messages EXPORT messagesTargets # This somehow makes these directories visible as targer properties on downstream project
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT messages_Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT messages_Runtime
    NAMELINK_COMPONENT messages_Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT messages_Development
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/messages
    COMPONENT messages_Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

# Install libConfig.cmake file which will be used by downstream project
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/messagesConfig.cmake DESTINATION lib/cmake/messages)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/messagesConfigVersion.cmake DESTINATION lib/cmake/messages)

# Install libTarget.cmake file which will include target properties. (Include dirs etc.)
install(EXPORT messagesTargets
  FILE
    messagesTargets.cmake
  NAMESPACE
    messages::
  DESTINATION
    lib/cmake/messages
)
target_compile_definitions(messages PRIVATE BUILD_INFO="$<CONFIG>")
target_compile_definitions(messages PRIVATE VERSION="${PROJECT_VERSION}")

include(CPack)

