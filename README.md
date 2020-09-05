# Virtual-Memory-Management

## Page Replacement Algorithms
1. Find the location of the desired page on the disk.
2. Find a free frame:
    1. If there is a free frame, use it.
    2. If there is no free frame, use a page-replacement algorithm to select a victim frame.
    3. Write the victim frame to the disk; change the page and frame tables accordingly.
3. Read the desired page into the newly freed frame; change the page and frame tables.
4. Continue the user process from where the page fault occurred.

Notice that, if no frames are free, two page transfers (one out and one in) are required. This situation effectively doubles the page-fault service time and increases the effective access time accordingly.

We can reduce this overhead by using a modify bit (or dirty bit). When this method is used, each page or frame has a modify bit associated with it in the hardware. The modify bit for a page is set by the hardware whenever any byte in the page is written into, indicating that the page has been modified. 

When we select a page for replacement, we examine its modify bit. If the bit is set, we know that the page has been modified since it was read in from the disk. In this case, we must write the page back to the disk. If the modify bit is not set, the page has not been modified since it was read into memory. In this case, we need not write the memory page back to the disk: it is already in disk. This technique also applies to read-only pages (for example, pages of binary code). We just discard the un-modified pages. This mehod can significantly reduce the time required to service a page fault, since it reduces I/O time by one-half if the page has not been modified.

## What is a good page replacement algorithm?
The lower page fault rate, the better page replacement algorithm. Because with each page fault, we have to perform one disk I/O, which is so expensive.

## What's the role of disk?

## Second Chance Replacement Algorithm
Also known as enhanced clock algorithm.
Dirty bit: write bit, denote that the page has been modified.


|is_busy | is_dirty |    | is_busy | is_dirty |
|--------|----------|----|---------|----------|
|   0    |     0    | -> |     replace page   |
|   0    |     1    | -> |    0    |     0    |
|   1    |     0    | -> |    0    |     0    | 
|   1    |     1    | -> |    0    |     1    |


# Reference
[操作系统 清华大学 (向勇、陈渝)](https://www.bilibili.com/video/BV1js411b7vg?p=28)