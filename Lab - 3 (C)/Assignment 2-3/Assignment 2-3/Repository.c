#pragma once
#include "Repository.h"
#include <stdlib.h>

// Dynamic Array Methods
// Initialization ( for Countries )
DynamicArray* da_create(int capacity)
{
	/*
		Creates and returns a pointer to a new DynamicArray with a specified initial capacity
	*/

	// Allocate memory for the DynamicArray structure
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (arr == NULL) {
		// Allocation failed, return NULL
		return NULL;
	}

	// Allocate memory for the elements array
	arr->elements = (TElem*)malloc(capacity * sizeof(TElem));
	if (arr->elements == NULL) {
		// Allocation failed, free the previously allocated memory and return NULL
		free(arr);
		return NULL;
	}

	// Initialize size and capacity
	arr->size = 0;
	arr->capacity = capacity;

	// Return a pointer to the DynamicArray
	return arr;
}

// Deletion
void da_destroy(DynamicArray* arr)
{
	/*
		Frees memory for the elements of the specified DynamicArray and the Array itself
	*/

	free(arr->elements);
	free(arr);
}

// STATISTICS BELOW
int da_size(DynamicArray arr)
{
	/*
		Returns the number of elements inside the specified DynamicArray
	*/
	return arr.size;
}

int da_empty(DynamicArray arr)
{
	/*
		Returns 1 if the DynamicArray has no elements, 0 otherwise
	*/
	return arr.size == 0;
}

int da_full(DynamicArray arr)
{
	/*
		Returns 1 if the DynamicArray has reached its capacity, 0 otherwise
	*/
	return arr.size == arr.capacity;
}

// Element Getter / Setter
TElem da_getElement(DynamicArray arr, int index)
{
	/*
	    Checks if the index is in bounds then
		Returns the TElem found at the specified index (integer) in the array
		Otherwise, return the Null Country
	*/
	Country null_country = NULL_COUNTRY;
	if (index<0 || index>arr.size)
		return null_country;
	return arr.elements[index];
}

TElem da_setElement(DynamicArray* arr, int index, TElem country_value)
{
	/*
	    Checks if the index is in bounds then
		Sets a new value to & Returns the TElem found at the specified index (integer) in the array
		Otherwise, return the Null Country
	*/
	Country null_country = NULL_COUNTRY;
	if (index<0 || index>arr->size)
		return null_country;
	arr->elements[index] = country_value;
	return arr->elements[index];
}

// Add / Remove Elements
int da_addToEnd(DynamicArray* arr, TElem country_value)
{
	/*
		If the array has reached its capacity, reallocated with a double size
		Finally, add a new TElem to the end of the DynamicArray
	*/
	if (da_full(*arr)) {

		// Double Capacity
		arr->capacity *= 2;
		Country* new_elements = realloc(arr->elements, arr->capacity * sizeof(Country));


		// Realloc failed
		if (new_elements == NULL) {
			return 0;
		}

		// Update the pointer to the newly allocated memory
		arr->elements = new_elements;
	}
	arr->elements[arr->size++] = country_value;
	return 1;
}

int da_addToPosition(DynamicArray* arr, int index, TElem country_value)
{
	/*
	    Checks if index in range and proceeds if so, otherwise returns 0 => not added.
		If the array has reached its capacity, reallocated with a double size
		Finally, add a new TElem to the end of the DynamicArray
	*/

	// Checking the Index
	if (index<0 || index>arr->size) return 0;

	// Dealing with a full array
	if (da_full(*arr)) {

		// Double Capacity
		arr->capacity *= 2;
		Country* new_elements = realloc(arr->elements, arr->capacity * sizeof(Country));


		// Realloc failed
		if (new_elements == NULL) {
			return 0;
		}

		// Update the pointer to the newly allocated memory
		arr->elements = new_elements;
	}

	// Finally, migrate all elements to the right to make room for the new value
	for (int i = arr->size - 1; i >= index; i--)
		arr->elements[i + 1] = arr->elements[i];

	// Add new value to the given index
	arr->elements[index] = country_value;
	arr->size++;
	return 1;
}

int da_deleteFromPosition(DynamicArray* arr, int index)
{
	/*
		Checks if index in range and proceeds if so, otherwise returns 0 => not removed.
		Remove an element by overwriting it with the elements from the right.
		If the array has reached half its capacity, reallocated with a half size
	*/

	// Checking the Index
	if (index<0 || index>arr->size) return 0;

	// Shift elements to the left to remove the element at the given index
	for (int i = index; i < arr->size - 1; i++) {
		arr->elements[i] = arr->elements[i + 1];
	}

	// Decrement the size of the dynamic array
	arr->size--;

	// Dealing with a half empty array
	if (arr->size < arr->capacity / 2) {

		// Halve the capacity
		arr->capacity /= 2;

		// Reallocate memory for the smaller array
		Country* new_elements = realloc(arr->elements, arr->capacity * sizeof(Country));
		if (new_elements == NULL) {
			// Realloc failed, handle error (e.g., return an error code)
			return 0;
		}

		// Update the pointer to the newly allocated memory
		arr->elements = new_elements;
	}

	return 1;
}

// REPOSITORY HISTORY DYNAMIC ARRAY IMPLEMENTATION BELOW
// Initialization for Repository History
DynamicArrayHistory* da_create_history()
{
	/*
		Creates and returns a pointer to a new DynamicArray with a specified initial capacity
	*/

	// Allocate memory for the DynamicArray structure
	DynamicArrayHistory* arr = (DynamicArrayHistory*)malloc(sizeof(DynamicArrayHistory));
	if (arr == NULL) {
		// Allocation failed, return NULL
		return NULL;
	}

	// Allocate memory for the elements array
	arr->elements = (Repository*)malloc(sizeof(Repository));
	if (arr->elements == NULL) {
		// Allocation failed, free the previously allocated memory and return NULL
		free(arr);
		return NULL;
	}

	// Initialize size and capacity
	arr->size = 0;
	arr->capacity = 1;

	// Return a pointer to the DynamicArray
	return arr;
}

// Deletion
void da_destroy_history(DynamicArrayHistory* arr)
{
	/*
		Frees memory for the elements of the specified DynamicArray and the Array itself
	*/

	for (int i = 0; i < arr->size; i++) {
		da_destroy(arr->elements[i].countries);
	}

	free(arr->elements);
	free(arr);
}

// Repository State Getter
Repository da_getHistoryState(DynamicArrayHistory arr, int index)
{
	/*
		Returns the Repository found at the specified index (integer) in the history
	*/
	return arr.elements[index];
}

// Push New State
int da_addToEndHistory(DynamicArrayHistory* arr, Repository repository_state)
{
	/*
		If the array has reached its capacity, reallocated with a double size
		Finally, add a new Repository State to the end of the DynamicArray
	*/
	if (arr->size >= arr->capacity) {
		// Double Capacity
		arr->capacity *= 2;
		Repository* new_elements = realloc(arr->elements, arr->capacity * sizeof(Repository));

		// Realloc failed
		if (new_elements == NULL) {
			return 0;
		}

		// Update the pointer to the newly allocated memory
		arr->elements = new_elements;
	}

	// Copy the repository state before adding it to the history
	Repository copied_state;
	copied_state.countries = da_create(repository_state.countries->capacity);
	for (int i = 0; i < repository_state.countries->size; i++) {
		da_addToEnd(copied_state.countries, da_getElement(*repository_state.countries, i));
	}

	arr->elements[arr->size] = copied_state;
	arr->size++;
	return 1;
}