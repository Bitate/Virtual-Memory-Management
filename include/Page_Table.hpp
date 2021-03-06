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
#include <functional>
#include <string>

class Page_Table
{
public:
    /**
     * Address type for virtual address and phsical address.
     */
    using Address = uint64_t;

    /**
     * Page fault handler type for various page replacement algorithms.
     */
    using Page_Fault_Handler = std::function< Address() >;
public:
    /**
     * @brief  Construct a page table with m pages and n phsical frames with each k-byte.
     * @param  m  Number of pages.
     * @param  n  Number of frames.
     * @param  k  Page/Frame size in byte.
     */
    Page_Table(uint64_t m, uint64_t n, uint64_t k);
    Page_Table();
    ~Page_Table();

    Page_Table(const Page_Table&) = delete;
    Page_Table& operator=(const Page_Table&) = delete;

    Page_Table(Page_Table&&) = delete;
    Page_Table& operator=(Page_Table&&) = delete;
public:
    /**
     * @brief  Whether given page has a corresponding phsical frame.
     * @param  page_number  Page number is the index of page table.
     * @return  True if given page has a corresponding phsical frame.
     */
    bool is_valid_page(Address page_number);

    /**
     * @brief  Translate/Map a given virtual/linear address to phsical address.
     * @param  virtual_address  Virtual/Linear address.
     * @param  page_replacement_algorithm  Name of age replacement algorithm.
     * @return  Phsical address.
     */
    Address translate_virtual_to_phsical_address(Address virtual_address, const std::string& page_replacement_algorithm);

    /**
     * @brief  Handler for page fault.
     * @param  page_number  Page to be handled due to page fault.
     * @param  page_replacement_algorithm  Name of specific page replacement algorithm.
     */
    void handle_page_fault(Address page_number, const std::string& page_replacement_algorithm);

    /**
     * @brief  Generate random reference string for testing page fault rate.
     * @param  reference_string_length  Length of generated reference string.
     * @param  max_page_index  Max page index.
     * @return  A sequence of reference string.
     */
    std::vector< Address > generate_random_reference_string(int reference_string_length, Address max_page_index);

    /**
     * @brief  FIFO page replacement algorithm.
     * @return  Phsical frame number.
     */
    Address first_in_first_out_replacement();

    /**
     * @brief  LRU(least recently used) replacement algorithm.
     * @return  Phsical frame number.
     */
    Address least_recently_used_replacement();

    /**
     * @brief  Clock(also known as Second Chance) relacement algorithm.
     * @return  Phsical frame number.
     *
     * We link all available phsical frames into a circular linked list. 
     * For each page fault, we move the pointer current_frame clockwise
     * to find a node in which the is_used bit is 0. 
     * If is_used is 1, we set it to 0, and move current_frame
     * to next node. Thus, giving the node with is_used bit being 1 
     * a second chance to be replaced.
     * 
     * This algorithm degenerates to FIFO replacement if all bits are set to 1.
     */
    Address clock_replacement();
private:
    struct page_table_entry
    {   
        Address frame_number;
        Address is_valid:1;
    };

    std::vector< page_table_entry > page_table;
    
    struct frame_info
    {
        uint64_t id;
        unsigned char reference_bit : 1;
        bool is_dirty;
        bool is_busy;
	    bool is_used;
        struct frame_info* next;

        frame_info()
            :id(0), is_dirty(false), is_busy(false), next(nullptr), is_used(false), reference_bit(0)
        {
        }

        frame_info(uint64_t index)
            :id(index), is_dirty(false), is_busy(false), next(nullptr), is_used(false), reference_bit(0)
        {
        }
    };

    struct frame_info* frame_list_head = new frame_info;

    /**
     * When a frame is needed, current_frame advances
     * until it finds a page with a 0 reference bit.
     * 
     * As current_frame advances, it clears all the reference
     * bits before selecting the next page for replacement.
     */
    struct frame_info* current_frame = nullptr;
    struct frame_info* frame_list_tail = nullptr;
};
