#include "Page_Table.hpp"

#include <gtest/gtest.h>


TEST(page_table_tests, translate_virtual_to_phsical_address)
{
    Page_Table pt;

    /**
     * We have 64 pages, we the page index is [0, 63], namely [0, 0x3f] in hexadecimal.
     */
    for(int i = 0; i <= 0x3f; ++i)
    {
        ASSERT_LE(pt.translate_virtual_to_phsical_address(i), 0xf);
        std::cout << i << std::endl;
    }
}

