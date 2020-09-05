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
        /**
         * Make sure all translated/mapped phsical address is <= 0x0f.
         * Because, we only have 4 physical frames with each 4 bytes,
         * the phsical address space is 4*4 = 16 bytes.
         * Thus, all the translated/mapped phsical address must be in 
         * the range of [0, 15]. Namely, [0, 0x0f] in hexadecimal.
         */
        ASSERT_LE(pt.translate_virtual_to_phsical_address(i), 0x0f);
        std::cout << i << std::endl;
    }
}

TEST(page_table_tests, calculate_page_fault_rate)
{
    Page_Table pt;
    pt.calculate_page_fault_rate();
}
