# Palestinian Districts Radix Sort Using Doubly Linked List in C

## Project Overview
This project implements a **2-level hierarchy system** to sort Palestinian districts and their respective towns using a **Radix Sort algorithm**. The program reads district and town data from an input file, organizes it using a **doubly linked list**, and sorts the data alphabetically by district name and by town population. The project provides a user-friendly menu to allow various operations, such as adding new districts or towns, sorting, and displaying data.

### Features
- **Doubly Linked List Implementation**:
  - Districts and their respective towns are stored in a doubly linked list, enabling efficient traversal in both directions.
- **Radix Sort Algorithm**:
  - District names are sorted alphabetically using Radix Sort, which is optimal for handling fixed-length strings (up to 50 characters).
  - Towns are sorted by population in ascending order.
- **Dynamic Input Handling**:
  - The program reads district and town data from an input file, `districts.txt`, which contains an unspecified number of entries. Each entry follows the format: `District Name | Town Name | Town Population`.
- **File I/O**:
  - Supports reading from the input file and saving sorted results to an output file, `sorted_districts.txt`, which includes district names, total population, and sorted town data.
  
### Menu Options
The program presents a menu with the following functionalities:
1. **Load Input File**: Load Palestinian districts and their towns with populations from `districts.txt`.
2. **Print Loaded Data**: Display the information before sorting, as read from the input file.
3. **Sort Districts**: Sort the districts alphabetically using the Radix Sort algorithm.
4. **Sort Towns by Population**: Sort the towns within each district by population in ascending order.
5. **Print Sorted Data**: Display the sorted districts, towns, and population details.
6. **Add New District**: Add a new district to the sorted list and maintain the order.
7. **Add New Town**: Add a new town to an existing district.
8. **Delete Town**: Remove a specific town from a district.
9. **Delete District**: Remove a district and all of its towns from the list.
10. **Calculate Population Statistics**: Calculate the total population of Palestine, as well as the minimum and maximum population of any town.
11. **Print District Populations**: Display the total population of each district without town details.
12. **Modify Town Population**: Change the population of a specific town after prompting the user for the district name.
13. **Save to Output File**: Save the sorted data to `sorted_districts.txt`.
14. **Exit**: Exit the program.

15. 
### Data Structures Used
- **Doubly Linked List**: Used to store districts and their towns for efficient traversal and manipulation.
- **Radix Sort**: Employed for sorting district names alphabetically.
- **Linked Lists for Towns**: Each district maintains a linked list of towns, which are sorted by population.

### Technologies
- **Language**: C
- **Data Structures**:
  - Doubly Linked List
  - Radix Sort
  - Linked List for managing towns

### How to Use
1. **Compile the Program**: Use the following command to compile the program:
    ```bash
    gcc -o district_sorter main.c
    ```
2. **Run the Program**: Execute the compiled program:
    ```bash
    ./district_sorter
    ```
3. **Input Options**: The menu provides options to load data, sort it, add or remove entries, and more.


