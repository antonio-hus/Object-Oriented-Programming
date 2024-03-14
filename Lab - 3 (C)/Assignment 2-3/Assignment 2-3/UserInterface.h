#pragma once
#pragma warning(disable:4996)
#include <stdio.h>

#include "Domain.h"
#include "Repository.h"
#include "Controller.h"

// User Guidance Screens
void welcome_screen();

// Interactive Screens
void add_country_screen(Repository* repo, DynamicArrayHistory* history);
void remove_country_screen(Repository* repo, DynamicArrayHistory* history);
void update_country_screen(Repository* repo, DynamicArrayHistory* history);
void undo_screen(Repository* repo, DynamicArrayHistory* history);
void redo_screen(Repository* repo, DynamicArrayHistory* history);

// Statistics Screens
void display_countries(Repository repo);
void display_countries_partial(Repository repo);
void display_countries_match(Repository repo);