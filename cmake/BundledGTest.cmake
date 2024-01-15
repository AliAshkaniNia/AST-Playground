find_package(GTest)

if (NOT GTEST_FOUND)
   # I think downloaing gtest is a cleaner approach 
   message (STATUS "Downloading gtest")
   include(FetchContent)
   FetchContent_Declare(
         googletest
         GIT_REPOSITORY https://github.com/google/googletest.git
         GIT_TAG        v1.14.0
   )
   FetchContent_MakeAvailable(googletest)
   add_library(GTest::GTest ALIAS gtest)

   # message(STATUS "Adding bundled Google Test")
   # set(BUILD_GMOCK OFF CACHE BOOL INTERNAL)
   # set(INSTALL_GTEST OFF CACHE BOOL INTERNAL)
   # add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/googletest)
   # add_library(GTest::GTest ALIAS gtest)
endif ()
