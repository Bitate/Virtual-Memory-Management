#include "Page_Table.hpp"

#include <gtest/gtest.h>

/**
 * Suppose virtual address is 8-bit, we have 2^8 = 256 bytes virtual address space.
 * With phsical memory is 16 bytes, we split it into 4 frames with each frame 4 bytes.
 * phsical address is 4-bit (16 = 2^4). For virtual address, 256/4 = 64 pages.
 * 
 * 2^6 = 64 pages
 * 2^2 = 4 bytes offset
 * 
 * We need to convert 8-bit virtual address to 4-bit phsical address.
 * 
 * With page table, we need to store the frame number, is_valid bit for each page.
 */ 
TEST(page_table_tests, translate_virtual_to_phsical_address)
{
    Page_Table pt;

    for(int i = 0; i <= 0xff; ++i)
    {
        ASSERT_LE(pt.translate_virtual_to_phsical_address(i), 0xf);
    }
}

TEST(page_table_tests, page_fault_calculation)
{
    Page_Table pt;

    pt.generate_random_reference_string(100);
}