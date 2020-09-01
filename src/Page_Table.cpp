#include "Page_Table.hpp"

#include <iostream>
#include <fstream>

Page_Table::Page_Table()
{
    /**
     * We have only 4 frames.
     */
    frame_list_head->next = new frame_info;
    frame_list_head->next->id = 0;
    for(int i = 1; i < 3; ++i)
    {
        auto tmp = new frame_info;
        tmp->id = i;
        tmp->next = frame_list_head->next;
        frame_list_head->next = tmp;
        delete tmp;
    }
    frame_info* frame_list_tail = frame_list_head->next;
    while(frame_list_tail->next)
    {
        frame_list_tail = frame_list_tail->next;
    }
    frame_list_tail->next = frame_list_head;
    std::cout << "Create frame circular list" << std::endl;

    /**
     * We have 64 pages
     */
    page_table.resize(64);
    for(auto page_table_entry : page_table)
    {
        page_table_entry.is_valid = 0;
    }
}

bool Page_Table::is_valid_page(Address page_number)
{
    return page_table[ page_number ].is_valid;
}

void Page_Table::swap_in(Address page_number, Address frame_number)
{

}

void Page_Table::swap_out(Address page_number)
{
    page_table[ page_number ].is_valid = 0;
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
    auto iterator = frame_list_head->next;
    int iteration_counter = -1;
    while(iterator)
    {
        if(iterator == frame_list_head)
        {
            ++iteration_counter;
        }
        

        /**
         * We need to change bit.
         */
        if(iteration_counter == 1)
        {

        }

        if(iterator->is_busy == 0)
        {
            std::cout << "We have free frame" << std::endl;
            /**
             * Map page to frame.
             */
            page_table[ page_number ].frame_number = iterator->id;
            iterator->is_busy = 1;
            return;
        }
        iterator = iterator->next;
    }

    /**
     * We choose the frame at the beginning of the all_frames list.
     */
    std::cout << "Perform page swap algorithm" << std::endl;
    return;
}

std::vector< Page_Table::Address > Page_Table::generate_random_reference_string(int reference_string_size)
{
    std::vector< Page_Table::Address > result;
    for(int i = 0; i < reference_string_size; ++i)
    {
        Address random_address = static_cast< Address >(std::rand() % 256);
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

void Page_Table::print_frame_list()
{
    while(frame_list_head)
    {
        std::cout << frame_list_head->id << std::endl;
    }
}