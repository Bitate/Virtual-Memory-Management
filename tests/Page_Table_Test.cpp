#include "Page_Table.hpp"

#include <gtest/gtest.h>

constexpr uint64_t ONE_K_BYTES = 1024;
constexpr uint64_t ONE_M_BYTES = 1024 * ONE_K_BYTES;
constexpr uint64_t ONE_G_BYTES = 1024 * ONE_M_BYTES;

constexpr uint64_t FOUR_K_BYTES = 4 * ONE_K_BYTES;
constexpr uint64_t EIGHT_G_BYTES = 8 * ONE_G_BYTES;

TEST(page_table_tests, translate_virtual_to_phsical_address)
{
    /**
     * Assume we have 1M bytes virtual address space but we only have 128K bytes phsical address space.
     * For 1M virtual address space, the address is 20-bit long.
     * For 128K phsical address space, the address is 17-bit long.
     * 
     * Each page/frame is 1K bytes. We have 128 phsical frames available.
     */
    Page_Table pt( ONE_M_BYTES/ONE_K_BYTES, (128*ONE_K_BYTES)/ONE_K_BYTES, ONE_K_BYTES);

    for(int i = 0 ; i <= 255; ++i)
    {
        ASSERT_FALSE(pt.is_valid_page(i)) << "Error at index: " << i;
        pt.translate_virtual_to_phsical_address(i, "clock");
    }

}

