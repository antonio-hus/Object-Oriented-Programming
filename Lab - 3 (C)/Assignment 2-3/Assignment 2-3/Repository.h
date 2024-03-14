#pragma once
#include "Domain.h"

// Dynamic Array based on type TElem ( Simulating using any type )
#define NULL_COUNTRY { "", "", 0 }
typedef Country TElem;

// STRUCTS BELOW
// Dynamic Array Type - has a current size, initial capacity, and Country type elements
typedef struct
{
    int size, capacity;
    TElem* elements;
}DynamicArray;

// Repository Type - based on a Dynamic Array
typedef struct
{
    DynamicArray* countries;
}Repository;

// Dynamic Array for Repository History
typedef struct
{
    int size, capacity, index;
    Repository* elements;
}DynamicArrayHistory;

// METHODS BELOW
// Initialization / Deletion
DynamicArray* da_create(int capacity);
void da_destroy(DynamicArray* arr);

// Statistics
int da_size(DynamicArray arr);
int da_empty(DynamicArray arr);
int da_full(DynamicArray arr);

// Element Getter / Setter
TElem da_getElement(DynamicArray arr, int index);
TElem da_setElement(DynamicArray* arr, int index, TElem country_value);

// Add / Remove Elements
int da_addToEnd(DynamicArray* arr, TElem country_value);
int da_addToPosition(DynamicArray* arr, int index, TElem country_value);
int da_deleteFromPosition(DynamicArray* arr, int index);

// For Repository History
DynamicArrayHistory* da_create_history();
void da_destroy_history(DynamicArrayHistory* arr);
Repository da_getHistoryState(DynamicArrayHistory arr, int index);
int da_addToEndHistory(DynamicArrayHistory* arr, Repository repository_state);