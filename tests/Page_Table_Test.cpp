#include "Page_Table.hpp"

#include <gtest/gtest.h>

constexpr uint64_t ONE_K_BYTES = 1024;
constexpr uint64_t ONE_M_BYTES = 1024 * ONE_K_BYTES;
constexpr uint64_t ONE_G_BYTES = 1024 * ONE_M_BYTES;

constexpr uint64_t FOUR_K_BYTES = 4 * ONE_K_BYTES;
constexpr uint64_t EIGHT_G_BYTES = 8 * ONE_G_BYTES;

TEST(page_table_tests, clock_replacement_test)
{
    /**
     * Assume we have 1M bytes virtual address space but we only have 128K bytes phsical address space.
     * For 1M virtual address space, the address is 20-bit long.
     * For 128K phsical address space, the address is 17-bit long.
     * 
     * Each page/frame is 1K bytes. We have 128 phsical frames and 1024 virtual pages.
     */
    Page_Table pt(1024, 128, ONE_K_BYTES);

    /**
     * Generate 1000 page reference index with each page index is in the range of [0, 1023].
     */
    auto random_reference_string = pt.generate_random_reference_string(2000, 1024);
    
    int page_fault_counter = 0;
    int page_ok_counter = 0;
    for(auto page_number : random_reference_string)
    {
        if(pt.is_valid_page(page_number) == 0)
        {
            pt.handle_page_fault(page_number, "clock");
            ++page_fault_counter;
        }
        else // page is valid
        {
            ++page_ok_counter;
        }
    }
    std::cout << "Page fault: " << page_fault_counter << " times." << std::endl;
}