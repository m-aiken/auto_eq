cmake_minimum_required(VERSION 3.22)

project(ReactiveLufsNormalisation)

set(CMAKE_CXX_STANDARD 23)

#
# Create a dependencies folder in our project.
#
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

#
# Add CPM (cmake package manager) to our project's dependencies.
#
set(CPM_DOWNLOAD_VERSION 0.39.0)
set(CPM_DOWNLOAD_LOCATION "${DEPENDENCIES_DIR}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

# Expand relative path. This is important if the provided path contains a tilde (~).
get_filename_component(CPM_DOWNLOAD_LOCATION ${CPM_DOWNLOAD_LOCATION} ABSOLUTE)

file(DOWNLOAD
     https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
     ${CPM_DOWNLOAD_LOCATION}
)

include(${CPM_DOWNLOAD_LOCATION})

#
# Add JUCE to our project's dependencies.
#
CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 7.0.12 # Need to do this because the JUCE version in GH doesn't have the preceding v (i.e v7.0.12).
    VERSION 7.0.12
    SOURCE_DIR ${DEPENDENCIES_DIR}/juce
)

#
# Add our plugin subdirectory.
#
add_subdirectory(plugin)
