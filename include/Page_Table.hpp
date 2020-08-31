#pragma once

#include <vector>
#include <list>

class Page_Table
{
public:
    using Address = unsigned char;
public:
    Page_Table();
public:
    bool is_valid_page(Address page_number);

    Address translate_virtual_to_phsical_address(Address virtual_address);

    void handle_page_fault(Address page_number);

    void swap_in(Address page_number, Address frame_number);

    void swap_out(Address page_number);

    std::vector< Address > generate_random_reference_string(int reference_string_size);

    float calculate_page_fault();

    void first_in_first_out_replacement();
    void least_recently_used_replacement();
    void second_chance_replacement();
    void counting_based_replacement();
    void page_buffering_replacement();

private:
    struct page_table_entry
    {   
        Address frame_number : 2;
        Address is_valid_page : 1;
    };
    
    struct frame_info
    {
        int frame_id : 2;
        int dirty_bit : 1;
    };

    std::vector< page_table_entry > page_table;

    std::list< int > idle_frames;
    
    std::list< frame_info > all_frames;

};