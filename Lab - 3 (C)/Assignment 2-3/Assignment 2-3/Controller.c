#include "Controller.h"
#include <stdlib.h>

// MODULE CONTAINS THE NON-UI FUNCTIONS

int find_country(char name[64], Repository repo)
{
    /*
    Searches a country by name in the given Repository
    If found, returns the index of it, otherwise -1
    :param name: The Name of the Country to Search
    :param repo: The Repository to search
    */
    for (int i = 0;i < repo.countries->size;i++)
    {
        if (strcmp(name, da_getElement(*repo.countries, i).name) == 0)
            return i;
    }
    return -1;
}

int add_country(Country new_country, Repository* repo)
{
    /*
    Description: Adds a country to the repository ( Preservers name unicity )
    :param new_country: Country to add to the repository
    :param repo: Repository to add to
    :return: Returns 1 (True) if the Country was added without Errors ( Name already in Repo ), otherwise 0
    */
    if (find_country(new_country.name, *repo) != -1)
        return 0;
    da_addToEnd(repo->countries, new_country);
    return 1;
}

int remove_country(char country_name[], Repository* repo)
{
    /*
    Description: Removes a country from the repository ( Does not preserve order - Last Element replaces Removed Element, size decreases)
    :param country_name: Name of the country to remove
    :param repo: Repository to remove from
    :return: Returns 1 (True) if the Country was removed without Errors ( Country not in Repo ), otherwise 0
    */
    int country_index = find_country(country_name, *repo);
    if (country_index == -1)
        return 0;
    da_deleteFromPosition(repo->countries, country_index);
    return 1;
}

void update_country(Country new_country, int country_index, Repository* repo)
{
    /*
    Description: Updates a country from the repository
    :param new_country: Updated version of the Country
    :param country_index: Index of the old country inside the repository
    :param repo: Repository to work in
    */
    da_setElement(repo->countries, country_index, new_country);
}

void migrate(int origin_index, int destination_index, float migrators_count, Repository* repo)
{
    /*
    Description: Updates two country from the repository ( Performs a 'migration' operation )
    Subtracts from the origin country the migrators_count and adds them to the destination country
    :param origin_index: Origin Country Index
    :param destination_index: Destination Country Index
    :param migrators_count: Number of Migrators (in millions)
    :param repo: Repository to work in
    */
    Country origin_country = da_getElement(*repo->countries, origin_index);
    Country destination_country= da_getElement(*repo->countries, destination_index);
    origin_country.population -= migrators_count;
    destination_country.population += migrators_count;
    update_country(origin_country, origin_index, repo);
    update_country(destination_country, destination_index, repo);
}

// UNDO / REDO FUNCTIONALITY BELOW
void record_state(Repository repo, DynamicArrayHistory* history)
{
    /*
        Dynamically Adds to the end of the history a new repository state (passed by value).
    */

    history->index = history->size;
    da_addToEndHistory(history, repo);
}

int undo(Repository* repo, DynamicArrayHistory* history)
{
    /*
        Executing undo operation by retrieving and setting the previous repository state from history into the current repository
        Returns 1 if undo executed, 0 in case there are no more undos
    */

    // Except no more undos case
    if (history->index == 0)
        return 0;

    // Move to the previous state
    history->index--;

    // Copy the previous state back into the repository
    Repository previous_state = history->elements[history->index];
    repo->countries->size = previous_state.countries->size;
    repo->countries->capacity = previous_state.countries->capacity;

    // Reallocate memory for the elements array
    Country* new_elements = realloc(repo->countries->elements, repo->countries->capacity * sizeof(Country));
    if (new_elements == NULL) {
        // Memory reallocation failed
        return 0;
    }
    repo->countries->elements = new_elements;

    // Copy elements from the previous state
    for (int i = 0; i < previous_state.countries->size; i++) {
        repo->countries->elements[i] = previous_state.countries->elements[i];
    }

    return 1;
}

int redo(Repository* repo, DynamicArrayHistory* history)
{
    /*
        Executing redo operation by retrieving and setting the next repository state from history into the current repository
        Returns 1 if redo executed, 0 in case there are no more redos
    */
    // Except no more redos case
    if (history->index >= history->size - 1)
        return 0;

    // Otherwise get next state
    history->index++;
    Repository copy = da_getHistoryState(*history, history->index);

    // Updating the repo size to that of the new state
    repo->countries->capacity = copy.countries->capacity;
    Country* new_elements = realloc(repo->countries->elements, repo->countries->capacity * sizeof(Country));

    // Realloc failed
    if (new_elements == NULL) {
        return 0;
    }

    // Update the pointer to the newly allocated memory
    repo->countries->elements = new_elements;
    repo->countries->size = copy.countries->size;
    for (int i = 0;i <= copy.countries->size; i++)
        repo->countries->elements[i] = copy.countries->elements[i];
    return 1;
}

// STARTUP VALUE GENERATOR BELOW
void add_startup_values(Repository* repo)
{
    /*
        Manually adds 10 Countries to the Repository as StartUp Values
    */
    Country country;
    
    // #1 Country
    strcpy(country.name, "France");
    strcpy(country.continent, "Europe");
    country.population = 67.06;
    add_country(country, repo);

    // #2 Country
    strcpy(country.name, "Germany");
    strcpy(country.continent, "Europe");
    country.population = 83.02;
    add_country(country, repo);

    // #3 Country
    strcpy(country.name, "Italy");
    strcpy(country.continent, "Europe");
    country.population = 60.36;
    add_country(country, repo);

    // #4 Country
    strcpy(country.name, "United States");
    strcpy(country.continent, "America");
    country.population = 331.42;
    add_country(country, repo);

    // #5 Country
    strcpy(country.name, "Brazil");
    strcpy(country.continent, "America");
    country.population = 212.56;
    add_country(country, repo);

    // #6 Country
    strcpy(country.name, "China");
    strcpy(country.continent, "Asia");
    country.population = 1439.32;
    add_country(country, repo);

    // #7 Country
    strcpy(country.name, "India");
    strcpy(country.continent, "Asia");
    country.population = 1380.00;
    add_country(country, repo);

    // #8 Country
    strcpy(country.name, "Nigeria");
    strcpy(country.continent, "Africa");
    country.population = 206.14;
    add_country(country, repo);

    // #9 Country
    strcpy(country.name, "Egypt");
    strcpy(country.continent, "Africa");
    country.population = 104.26;
    add_country(country, repo);

    // #10 Country
    strcpy(country.name, "Australia");
    strcpy(country.continent, "Australia");
    country.population = 25.36;
    add_country(country, repo);
}