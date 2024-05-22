cmake_minimum_required(VERSION 3.22)

project(ReactiveLufsNormalisation)

set(CMAKE_CXX_STANDARD 23)

# Create a libs folder in our project.
set(PROJECT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Add CPM (cmake package manager) to our project's dependencies.
include(cmake/get_cpm.cmake)

# Add JUCE to our project's dependencies.
CPMAddPackage(
  NAME JUCE
  GITHUB_REPOSITORY juce-framework/JUCE
  GIT_TAG 7.0.12 # Need to do this because the JUCE version in GH doesn't have the preceding v (i.e v7.0.12).
  VERSION 7.0.12
  SOURCE_DIR ${PROJECT_LIB_DIR}/juce
)
