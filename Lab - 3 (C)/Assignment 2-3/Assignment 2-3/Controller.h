#pragma once
#include "Repository.h"

// Methods for querring the Repository
int find_country(char name[64], Repository repo);

// Methods for modifying the Repository
int add_country(Country new_country, Repository* repo);
int remove_country(char country_name[], Repository* repo);
void update_country(Country new_country, int country_index, Repository* repo);
void migrate(int origin_index, int destination_index, float migrators_count, Repository* repo);

// Methods for Undo/Redo Functionality
void record_state(Repository repo, DynamicArrayHistory* history);
int undo(Repository* repo, DynamicArrayHistory* history);
int redo(Repository* repo, DynamicArrayHistory* history);

// Methods for adding StartUp Values to the Repository
void add_startup_values(Repository* repo);