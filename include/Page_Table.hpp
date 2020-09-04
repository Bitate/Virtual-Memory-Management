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

#pragma once

#include <vector>
#include <list>

class Page_Table
{
public:
    using Address = unsigned char;
public:
    Page_Table();
    ~Page_Table();
public:
    bool is_valid_page(Address page_number);

    Address translate_virtual_to_phsical_address(Address virtual_address);

    void handle_page_fault(Address page_number);

    void swap_in(Address page_number, Address frame_number);

    void swap_out(Address page_number);

    std::vector< Address > generate_random_reference_string(int reference_string_size);

    float calculate_page_fault();

    void print_frame_list();

    Address first_in_first_out_replacement();

    Address least_recently_used_replacement();

    /**
     * @brief  Clock based page-swap.
     * @return  Phsical frame number.
     *
     * We link all available phsical frames info 
     * into a circular linked list. For each page 
     * fault, we move the pointer clockwise to find 
     * a node in which the is_used bit is 0. If we 
     * do not find that bit, in the second iteration,
     * we change the first node's is_used bit to 0.
     */
    Address clock_replacement();

    /**
     * @brief  Second chance replacement.
     * @return  Phsical frame number.
     */
    Address second_chance_replacement();


private:
    struct page_table_entry
    {   
        Address frame_number : 2;
        Address is_valid : 1;
    };

    std::vector< page_table_entry > page_table;
    
    struct frame_info
    {
        int id;
        bool is_dirty;
        bool is_busy;
	bool is_used;
        struct frame_info* next;

	frame_info():id(0), is_dirty(false), is_busy(false), next(nullptr), is_used(false)
	{}
	frame_info(int index):id(index), is_dirty(false), is_busy(false), next(nullptr), is_used(false)
	{}
    };

    struct frame_info* frame_list_head = new frame_info;
    struct frame_info* frame_list_tail = nullptr;

};
