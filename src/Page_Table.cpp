#include "Page_Table.hpp"

#include <iostream>
#include <fstream>

Page_Table::Page_Table()
{
    /**
     * We have only 4 frame.
     */
	std::cout << "Initialize new frame: 0" << std::endl;
	frame_list_head->next = new frame_info(0);
	 for(int i = 1; i < 4; ++i)
	 {
	     auto tmp = new frame_info(i);
	     tmp->next = frame_list_head->next;
	     frame_list_head->next = tmp;
	     tmp = nullptr;
	     std::cout << "Initialize new frame: " << frame_list_head->next->id << std::endl;
	 }
	 
	 frame_list_tail = frame_list_head->next;
	 while(frame_list_tail->next)
	 {
	     
		 frame_list_tail = frame_list_tail->next;
	 }
	 frame_list_tail->next = frame_list_head;
	 std::cout << "Link all frames into a circular list" << std::endl;

    /**
     * We have 64 pages
     */
    page_table.resize(64);
    for(auto page_table_entry : page_table)
    {
        page_table_entry.is_valid = 0;
    }
}

Page_Table::~Page_Table()
{
	std::cout << "Destruct frame circular list" << std::endl;
	while(frame_list_head != frame_list_tail)
	{
		frame_info* tmp = frame_list_head;
	
		if(frame_list_head->next)
		{
			frame_list_head = frame_list_head->next;
		}
		std::cout << "Delete frame: " << tmp->id << std::endl;
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
	/**
	 * We need to set a frame to this page_number.
	 */
        handle_page_fault(page_number);
    }

    return page_table[ virtual_address & 0xFC ].frame_number << 2;
}

void Page_Table::handle_page_fault(Address page_number)
{
    auto iterator = frame_list_head->next;
    int iteration_counter = 0;
    while(iterator != frame_list_tail)
    {
			if(iteration_counter == 0)
			{
				if(iterator->is_busy == false)
				{
					std::cout << "We have free frame, no page fault. " << std::endl;	
					break;
				}
				iterator = iterator->next;
			}
			else
			{
                if(iterator->is_busy == false)
                {
                    std::cout << "Second time we have free frame." << std::endl;
                }
                else
                {
                    iterator->is_busy == false;
                    break;
                }
			}
    }

    page_table[ page_number ].frame_number = iterator->id; 
    iterator->is_busy = true;                             
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

Page_Table::Address Page_Table::least_recently_used_replacement()
{
    // TODO
}

Page_Table::Address Page_Table::clock_replacement()
{
    
}
