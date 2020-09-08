include_directories(${CMAKE_SOURCE_DIR}/include)

set(Header_Files
    ../include/Page_Table.hpp
    ../include/Page_Fault_Rate.hpp
)

set(Source_Files
    Page_Table.cpp
    Page_Fault_Rate.cpp
)

add_library(Virtual_Memory_Management
    ${Header_Files}
    ${Source_Files}
)