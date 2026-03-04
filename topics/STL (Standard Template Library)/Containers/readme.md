# C++ STL Containers

The C++ Standard Template Library (STL) provides a rich set of template classes for managing collections of data. This README explains the different types of STL containers, their typical use cases, and some details about their implementation.

## Table of Contents

- [C++ STL Containers](#c-stl-containers)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Sequence Containers](#sequence-containers)
    - [Vector](#vector)
    - [Deque](#deque)
    - [List](#list)
    - [Forward List](#forward-list)
    - [Array](#array)
  - [Associative Containers](#associative-containers)
    - [Set](#set)
    - [Multiset](#multiset)
    - [Map](#map)
    - [Multimap](#multimap)
  - [Unordered Associative Containers](#unordered-associative-containers)
    - [Unordered Set](#unordered-set)
    - [Unordered Multiset](#unordered-multiset)
    - [Unordered Map](#unordered-map)
    - [Unordered Multimap](#unordered-multimap)
  - [Container Adapters](#container-adapters)
    - [Stack](#stack)
    - [Queue](#queue)
    - [Priority Queue](#priority-queue)
  - [Conclusion](#conclusion)

## Introduction

The STL containers are designed to handle various data storage needs. They are categorized based on their functionality and underlying implementation.

## Sequence Containers

Sequence containers maintain the ordering of elements and allow access to elements using iterators or indexes.

### Vector

- **Description**: A dynamic array that can grow and shrink in size.
- **Implementation**: Typically implemented using a contiguous block of memory.
- **Key Operations**: 
  - **Access**: Random access via the subscript operator (`[]`) and `at()`.
  - **Insertion/Deletion**: Efficient at the end (`push_back`, `pop_back`), less efficient in the middle.
- **Use Case**: When you need random access to elements and fast insertion/deletion at the end.

### Deque

- **Description**: A double-ended queue that allows fast insertions and deletions at both ends.
- **Implementation**: Often implemented as a sequence of contiguous memory blocks.
- **Key Operations**: 
  - **Access**: Random access via the subscript operator (`[]`) and `at()`.
  - **Insertion/Deletion**: Efficient at both ends (`push_front`, `push_back`, `pop_front`, `pop_back`).
- **Use Case**: When you need to add or remove elements from both ends and require random access.

### List

- **Description**: A doubly-linked list allowing efficient insertions and deletions anywhere in the list.
- **Implementation**: Doubly-linked list.
- **Key Operations**: 
  - **Access**: Sequential access only (no random access).
  - **Insertion/Deletion**: Efficient anywhere in the list.
- **Use Case**: When you need efficient insertions and deletions at arbitrary positions.

### Forward List

- **Description**: A singly-linked list with efficient insertions and deletions at the front.
- **Implementation**: Singly-linked list.
- **Key Operations**: 
  - **Access**: Sequential access only (no random access).
  - **Insertion/Deletion**: Efficient at the front.
- **Use Case**: When you need a lightweight list with efficient operations at the front.

### Array

- **Description**: A fixed-size array with a constant size determined at compile time.
- **Implementation**: Contiguous block of memory.
- **Key Operations**: 
  - **Access**: Random access via the subscript operator (`[]`).
  - **Insertion/Deletion**: Not supported; fixed size.
- **Use Case**: When you need a fixed-size collection with fast access and no dynamic resizing.

## Associative Containers

Associative containers store elements in a specific order based on keys or values.

### Set

- **Description**: A collection of unique elements stored in a sorted order.
- **Implementation**: Typically implemented as a balanced binary search tree (e.g., Red-Black Tree).
- **Key Operations**: 
  - **Insertion/Deletion**: Logarithmic time complexity.
  - **Access**: Efficient searching, insertion, and deletion.
- **Use Case**: When you need a collection of unique elements with automatic sorting.

### Multiset

- **Description**: Similar to `set`, but allows duplicate elements.
- **Implementation**: Same as `set` (usually a balanced binary search tree).
- **Key Operations**: 
  - **Insertion/Deletion**: Logarithmic time complexity.
  - **Access**: Efficient searching and insertion of duplicate elements.
- **Use Case**: When you need a collection of elements where duplicates are allowed.

### Map

- **Description**: A collection of key-value pairs with unique keys, stored in a sorted order by keys.
- **Implementation**: Typically implemented as a balanced binary search tree (e.g., Red-Black Tree).
- **Key Operations**: 
  - **Insertion/Deletion**: Logarithmic time complexity.
  - **Access**: Efficient access to values by key.
- **Use Case**: When you need a dictionary-like data structure with unique keys.

### Multimap

- **Description**: Similar to `map`, but allows multiple values for a single key.
- **Implementation**: Same as `map` (usually a balanced binary search tree).
- **Key Operations**: 
  - **Insertion/Deletion**: Logarithmic time complexity.
  - **Access**: Efficient access to values with duplicate keys.
- **Use Case**: When you need a dictionary-like structure where multiple values can be associated with a single key.

## Unordered Associative Containers

Unordered associative containers use hashing to provide average-case constant time complexity for operations.

### Unordered Set

- **Description**: A collection of unique elements using a hash table.
- **Implementation**: Hash table.
- **Key Operations**: 
  - **Insertion/Deletion/Access**: Average-case constant time complexity.
  - **Order**: Elements are not stored in any specific order.
- **Use Case**: When you need fast access and do not require sorted elements.

### Unordered Multiset

- **Description**: Similar to `unordered_set`, but allows duplicate elements.
- **Implementation**: Hash table.
- **Key Operations**: 
  - **Insertion/Deletion/Access**: Average-case constant time complexity.
  - **Order**: Elements are not stored in any specific order.
- **Use Case**: When you need a fast collection of elements where duplicates are allowed.

### Unordered Map

- **Description**: A collection of key-value pairs with unique keys, using a hash table.
- **Implementation**: Hash table.
- **Key Operations**: 
  - **Insertion/Deletion/Access**: Average-case constant time complexity.
  - **Order**: Keys are not stored in any specific order.
- **Use Case**: When you need fast access to values by key and do not require sorted keys.

### Unordered Multimap

- **Description**: Similar to `unordered_map`, but allows multiple values for a single key.
- **Implementation**: Hash table.
- **Key Operations**: 
  - **Insertion/Deletion/Access**: Average-case constant time complexity.
  - **Order**: Keys are not stored in any specific order.
- **Use Case**: When you need fast access to values with duplicate keys and do not require sorted keys.

## Container Adapters

Container adapters provide specific functionalities built on top of other container types.

### Stack

- **Description**: A container adapter that provides LIFO (Last-In-First-Out) functionality.
- **Implementation**: Typically built using `std::deque` or `std::vector`.
- **Key Operations**: 
  - **Push**: Add elements to the top.
  - **Pop**: Remove elements from the top.
  - **Top**: Access the top element.
- **Use Case**: When you need a stack with LIFO behavior.

### Queue

- **Description**: A container adapter that provides FIFO (First-In-First-Out) functionality.
- **Implementation**: Typically built using `std::deque` or `std::list`.
- **Key Operations**: 
  - **Push**: Add elements to the back.
  - **Pop**: Remove elements from the front.
  - **Front**: Access the front element.
  - **Back**: Access the back element.
- **Use Case**: When you need a queue with FIFO behavior.

### Priority Queue

- **Description**: A container adapter that provides access to elements based on priority (highest priority first).
- **Implementation**: Typically built using a heap data structure.
- **Key Operations**: 
  - **Push**: Add elements with a priority.
  - **Pop**: Remove the element with the highest priority.
  - **Top**: Access the element with the highest priority.
- **Use Case**: When you need to manage elements with varying priorities.

## Conclusion

STL containers offer a wide range of functionalities to manage collections of data efficiently. Choosing the right container depends on your specific needs, such as the type of access required, whether you need ordering or uniqueness,
