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

private:
    struct page_table_entry
    {   
        Address frame_number : 2;
        Address is_valid_page : 1;
    };
    
    struct frame_info
    {
        int frame_id : 2;
    };

    std::vector< page_table_entry > page_table;

    std::list< int > idle_frames;
    

};