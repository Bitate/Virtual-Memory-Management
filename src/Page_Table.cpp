#include "Page_Table.hpp"

#include <iostream>

Page_Table::Page_Table()
{
    for(int i = 0; i < 16; ++i)
    {
        idle_frames.push_back(i);
    }

    page_table.resize(64);
    for(auto page_table_entry : page_table)
    {
        page_table_entry.is_valid_page = 0;
    }
}

bool Page_Table::is_valid_page(Address page_number)
{
    return page_table[ page_number ].is_valid_page;
}

void Page_Table::swap_in(Address page_number, Address frame_number)
{

}

void Page_Table::swap_out(Address page_number)
{
    page_table[ page_number ].is_valid_page = 0;
}

Page_Table::Address Page_Table::translate_virtual_to_phsical_address(Address virtual_address)
{
    /**
     * Most significant 6-bit of virtual address is the page number.
     * So the mask is: 1111 11000 = 0xFC
     */
    Address page_number = virtual_address & 0xfc;
    if(!is_valid_page(page_number))
    {
        std::cout << "Oop! page fault. " << std::endl;
        handle_page_fault(page_number);
    }


    return page_table[ virtual_address & 0xFC ].frame_number << 2;
}

void Page_Table::handle_page_fault(Address page_number)
{
    if(idle_frames.size() >= 1)
    {
        std::cout << "Yeah! We have idle frame(s)" << std::endl;
        page_table[ page_number ].frame_number = idle_frames.front();
        idle_frames.pop_front();
        std::cout << "OK! handle page fault. " << std::endl;
        return;
    }

    std::cout << "We do not have idle frame, we need to perfrom page-swap algorithm." << std::endl;
}

std::vector< Page_Table::Address > Page_Table::generate_random_reference_string(int reference_string_size)
{
    std::vector< Page_Table::Address > result;
    for(int i = 0; i < reference_string_size; ++i)
    {
        Address random_address = static_cast< Address >(std::rand() % 256);
        std::cout << random_address << std::endl;
        result.push_back(random_address);
    }
    return result;
}

float Page_Table::calculate_page_fault()
{
    auto reference_string = generate_random_reference_string(1000);

    int page_fault_counter = 0;
    for(auto reference_character : reference_string)
    {
        // when we find one page fault
        // ...
        ++page_fault_counter;
    }
    
    /**
     * Page Fault Rate 0 ≤ p ≤ 1
     * if p = 0, no page faults
     * if p = 1, every reference is a fault 
     */
    return page_fault_counter / 4;
}