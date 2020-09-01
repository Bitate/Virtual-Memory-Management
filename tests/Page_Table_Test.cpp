#include "Page_Table.hpp"

#include <gtest/gtest.h>


TEST(page_table_tests, translate_virtual_to_phsical_address)
{
    // Page_Table pt;

    // for(int i = 0; i < 0xff; ++i)
    // {
    //     ASSERT_LE(pt.translate_virtual_to_phsical_address(i), 0xf);
    //     std::cout << i << std::endl;
    // }
}

TEST(page_table_tests, print_frame_info)
{
    Page_Table pt;

    pt.print_frame_list();

}
