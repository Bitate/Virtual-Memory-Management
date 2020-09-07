#include "Page_Table.hpp"

#include <iostream>
#include <fstream>

Page_Table::Page_Table(uint64_t m, uint64_t n, uint64_t k)
{
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
     * Most significant 6-bit of virtual address is the page number.
     * So the mask is: 1111 11000 = 0xFC
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
        page_table[ page_number ].frame_number = clock_replacement();
        page_table[ page_number ].is_valid = true;
        return;
    }
}

std::vector<Page_Table::Address> Page_Table::generate_random_reference_string(int reference_string_length)
{
    std::vector<Page_Table::Address> result;
    for (int i = 0; i < reference_string_length; ++i)
    {
        Address random_address = static_cast<Address>(std::rand() % 0x3f);
        result.push_back(random_address);
    }
    return result;
}

void Page_Table::calculate_page_fault_rate()
{
    auto reference_string = generate_random_reference_string(1000);
    int page_fault_counter = 0;
    for (auto page_number : reference_string)
    {
        if (!is_valid_page(page_number))
        {
            ++page_fault_counter;
            handle_page_fault(page_number, "clock");
        }
    }

    /**
     * Page Fault Rate 0 ≤ p ≤ 1
     * if p = 0, no page faults
     * if p = 1, every reference is a fault 
     */
    std::cout << "Page fault rate is: " << page_fault_counter << '/' << 1000 << std::endl;
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
         * If we find a free frame, return id directly.
         */
        if (current_frame->is_busy == 0)
        {
            current_frame = current_frame->next;
            return current_frame->id;
        }

        /**
         * If the frame is not recently used
         */
        if (current_frame->is_used == 0)
        {
            std::cout << "Clock replacement: current frame is: " << current_frame->id << std::endl;
            current_frame = current_frame->next;
            return current_frame->id;
        }
        else
        {
            current_frame->is_used = 0;
        }
        current_frame = current_frame->next;
    }
}
