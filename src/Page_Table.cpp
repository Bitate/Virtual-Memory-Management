#include "Page_Table.hpp"

#include <iostream>
#include <fstream>
#include <random>

Page_Table::Page_Table(uint64_t m, uint64_t n, uint64_t k)
{
    /**
     * Construct frame circular list.
     */
    frame_list_head->next = new frame_info(0);
    for (uint64_t i = 1; i < n; ++i)
    {
        auto tmp = new frame_info(i);
        tmp->next = frame_list_head->next;
        frame_list_head->next = tmp;
        tmp = nullptr;
    }

    frame_list_tail = frame_list_head->next;
    while (frame_list_tail->next)
    {
        frame_list_tail = frame_list_tail->next;
    }
    frame_list_tail->next = frame_list_head;

    current_frame = frame_list_head;
    
    /**
     * Construct page table with m entries.
     */
    page_table.resize(m);
    for (auto page_table_entry : page_table)
    {
        page_table_entry.is_valid = 0;
    }
}

Page_Table::~Page_Table()
{
    std::cout << std::endl;
    while (frame_list_head != frame_list_tail)
    {
        frame_info *tmp = frame_list_head;

        if (frame_list_head->next)
        {
            frame_list_head = frame_list_head->next;
        }
    }
}

bool Page_Table::is_valid_page(Address page_number)
{
    return page_table[ page_number ].is_valid;
}

Page_Table::Address Page_Table::translate_virtual_to_phsical_address(Address virtual_address, const std::string& page_replacement_algorithm)
{
    /**
     * TODO:
     */
    Address page_number = virtual_address & 0xfc;
    if (!is_valid_page(page_number))
    {
        handle_page_fault(page_number, "clock");
    }

    return page_table[virtual_address & 0xFC].frame_number << 2;
}

void Page_Table::handle_page_fault(Address page_number, const std::string& page_replacement_algorithm)
{
    if(page_replacement_algorithm == "clock")
    {
        auto chosen_frame_number =  clock_replacement();
        page_table[ page_number ].frame_number = chosen_frame_number;
        page_table[ page_number ].is_valid = 1;
        return;
    }
}

std::vector<Page_Table::Address> Page_Table::generate_random_reference_string(int reference_string_length, Address max_page_index)
{
    /**
     * Generate random number :)
     * Taken from: https://stackoverflow.com/a/13445752/11850070
     */
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, static_cast<int>(max_page_index)); // distribution in range [0, max_page_index]

    std::vector<Page_Table::Address> result;
    for (int i = 0; i < reference_string_length; ++i)
    {
        Address random_address = static_cast<Address>(dist6(rng) % max_page_index);
        result.push_back(random_address);
    }
    return result;
}

Page_Table::Address Page_Table::least_recently_used_replacement()
{
    return 0;
}

Page_Table::Address Page_Table::clock_replacement()
{
    while (current_frame)
    {
        /**
         * If the reference bit is 0.
         */
        if (current_frame->reference_bit == 0)
        {
            Address chosen_frame_number = current_frame->id;
            
            current_frame->reference_bit = 1;
            current_frame = current_frame->next;
            
            return chosen_frame_number;
        }
        else // reference bit is 1, set to 0, thus give this second chance.
        {
            current_frame->reference_bit = 0;
            current_frame = current_frame->next;
        }
    }
    return 0;
}
