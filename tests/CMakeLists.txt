include_directories(${CMAKE_SOURCE_DIR}/include)

set(All_Tests_Source_Files
    Page_Table_Test.cpp
)

add_executable(All_Tests
    ${All_Tests_Source_Files}
)
target_link_libraries(All_Tests PUBLIC
    gtest_main
    Virtual_Memory_Management
)

