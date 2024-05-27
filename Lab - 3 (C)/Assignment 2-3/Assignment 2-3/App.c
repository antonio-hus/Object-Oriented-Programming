#include "App.h"
#include <string.h>
#include <stdio.h>

int main()
{
    // TESTS RUN SETUP BELOW
	// To run the tests, uncomment these lines:
    TestAll();

    // OBJECT INITIALIZATION BELOW
    Repository countryRepository;
    countryRepository.countries = da_create(10);
    if (countryRepository.countries == NULL) {
        // Handle allocation failure
        return 1;
    }

    DynamicArrayHistory* history = da_create_history();
    history->index = -1;

    // STARTUP VALUE INITIALIZATION BELOW
    add_startup_values(&countryRepository);
    record_state(countryRepository, history);

    // PROGRAM FLOW CONTROLLER BELOW
    int user_option = 0;
    welcome_screen();

    // Main Menu
    while (1)
    {
        // User Guidance Operation Prompts
        clear_screen();
        printf("Enter the index of the operation you want to proceed:\n");
        printf("1. Add a country\n");
        printf("2. Remove a country\n");
        printf("3. Update a country\n");
        printf("4. List Countries (All)\n");
        printf("5. List Countries (Partial String Match)\n");
        printf("6. List Countries (Filter by Continent, Sort Ascendingly)\n");
        printf("7. Undo\n");
        printf("8. Redo\n");
        printf("0. Exit\n");
        printf(">");
        scanf("%d", &user_option);

        // User Option-Based Redirecting
        if (user_option == 0) break;
        switch (user_option)
        {
        case 1: add_country_screen(&countryRepository, history); break;
        case 2: remove_country_screen(&countryRepository, history); break;
        case 3: update_country_screen(&countryRepository, history); break;
        case 4: display_countries(countryRepository); break;
        case 5: display_countries_partial(countryRepository); break;
        case 6: display_countries_match(countryRepository); break;
        case 7: undo_screen(&countryRepository, history); break;
        case 8: redo_screen(&countryRepository, history); break;
        }
    }

    // MEMORY FREES BELOW
    da_destroy(countryRepository.countries);
        da_destroy_history(history);

    // MEMORY LEAK TESTS BELOW
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

}