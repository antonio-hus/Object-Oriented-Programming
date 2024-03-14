#include "UserInterface.h"
#include <string.h>

void clear_screen()
{
    /*
    Prints '\n' 40 times(Simulates a Clear Screen)
    */
    for (int i = 0;i < 40;i++) printf("\n");
}

void enter_proceed()
{
    /*
    Program BreakPoint(Resume on User clicking Enter)
    Empties the char buffer from previous '\n' characters and awaits a new one
    */
    while (getchar() != '\n');
    scanf("%c");
}

void welcome_screen()
{
    /*
    Displays Generic Welcome Screen
    */
    clear_screen();
    printf("Welcome to the Country Management App\n");
    printf("Made by Antonio Hus, Group 914/1\n\n\n\n\n");
    printf("Press 'Enter' to proceed");
    enter_proceed();
}

void add_country_screen(Repository* repo, DynamicArrayHistory* history)
{
    /*
    Displays Interactive Add Country Screen
    */

    Country new_country;

    // Prompting user for new country's details
    clear_screen();
    printf("Enter the Name of the Country: ");
    scanf("%s", &new_country.name);
    printf("Enter the Continent: ");
    scanf("%s", &new_country.continent);
    printf("Enter the Population (in millions): ");
    scanf("%f", &new_country.population);
    printf("\n");

    // Verifiy Valid Continent
    if (strcmp(new_country.continent, "Europe") == 0 || strcmp(new_country.continent, "America") == 0 ||
        strcmp(new_country.continent, "Africa") == 0 || strcmp(new_country.continent, "Australia") == 0 ||
        strcmp(new_country.continent, "Asia") == 0)
    {

        // Try to add country ( might fail due to name unicty criteria )
        if (add_country(new_country, repo)) {
            printf("Operation was successful!");

            // Record new state for undo / redo purposes
            record_state(*repo, history);
        }
        else printf("Operation failed (Country already in Repository)! Try again ...");

    }
    else printf("Operation failed (Invalid Continent Name)! Try again ...");

    // Proceed on enter back to the Main Menu
    printf("\nPress 'Enter' to proceed...");
    enter_proceed();
}

void remove_country_screen(Repository* repo, DynamicArrayHistory* history)
{
    /*
    Displays Interactive Remove Country Screen
    */

    char country_name[64];

    // Prompting user for name of the country to remove
    clear_screen();
    printf("Enter the Name of the Country to remove:\n");
    scanf("%s", &country_name);

    // Displays the output of the action
    if (remove_country(country_name, repo)) {
        printf("Operation was successful!");

        // Record new state for undo / redo purposes
        record_state(*repo, history);
    }
    else printf("Operation failed (Country not in Repository)! Try again ...");

    // Proceed on enter back to the Main Menu
    printf("\nPress 'Enter' to proceed...");
    enter_proceed();
}

void update_country_screen(Repository* repo, DynamicArrayHistory* history)
{
    /*
    Displays Interactive Update Country Screen with Single Update and Migrate Options
    */
    clear_screen();
    while (1)
    {
        printf("1. Update the country\n");
        printf("2. Manage Migrations\n");
        printf("0. Go back\n");

        int user_option = 0;
        scanf("%d", &user_option);
        if (user_option == 0)
            return;
        else if (user_option == 1)
        {
            char country_name[64];

            clear_screen();
            printf("Enter the Name of the Country to update: ");
            scanf("%s", country_name);

            int country_index = find_country(country_name, *repo);
            if (country_index == -1)
            {
                printf("Invalid Country Name ... Retry\n\n");
                continue;
            }

            Country updated_country;
            printf("\nEnter the new fields:\n");
            printf("New Name of the Country: ");
            scanf("%s", &updated_country.name);
            printf("New Continent: ");
            scanf("%s", &updated_country.continent);
            printf("New Population (in millions): ");
            scanf("%f", &updated_country.population);
            printf("\n");

            update_country(updated_country, country_index, repo);

            // Record new state for undo / redo purposes
            record_state(*repo, history);
            break;
        }
        else if (user_option == 2)
        {
            Country updated_origin, updated_destination;
            char origin_country_name[64], destination_country_name[64];
            int origin_country_index, destination_country_index;
            float migrators = 0;

            clear_screen();
            printf("Which Country should people migrate FROM: ");
            scanf("%s", origin_country_name);
            printf("Which Country should people migrate TO: ");
            scanf("%s", destination_country_name);
            printf("How many citizens (in millions) should migrate: ");
            scanf("%f", &migrators);

            origin_country_index = find_country(origin_country_name, *repo);
            destination_country_index = find_country(destination_country_name, *repo);

            if (origin_country_index == -1 || destination_country_index == -1)
            {
                printf("Invalid Countries ... Retry!\n\n");
                continue;
            }

            if (origin_country_index == destination_country_index)
            {
                printf("Cannot migrate to the same country ... Retry!\n\n");
                continue;
            }
            
            if (da_getElement(*(repo->countries), origin_country_index).population < migrators)
            {
                printf("Invalid migrators numbers ... Retry!\n\n");
                continue;
            }

            migrate(origin_country_index, destination_country_index, migrators, repo);

            // Record new state for undo / redo purposes
            record_state(*repo, history);
            break;
        }
        else printf("Invalid Option..Retry\n\n");
    }
}

void display_countries(Repository repo)
{
    /*
    Displays a list of all countries
    */

    clear_screen();
    printf("The countries are: \n\n");
    for (int i = 0;i < repo.countries->size;i++) {
        Country country = da_getElement(*(repo.countries), i);
        printf("Name: %s | Continent: %s | Population: %f\n", country.name,country.continent, country.population);
    }

    // Proceed on enter back to the Main Menu
    printf("\n\nPress 'Enter' to continue...");
    enter_proceed();
}

void display_countries_partial(Repository repo)
{
    /*
    Displays a list of all countries that partially match a search querry
    (Substring Pattern in Name)
    */
    char substr[64];

    clear_screen();
    printf("Enter the substring to look for: ");
    scanf("%s", substr);

    printf("The countries are: \n\n");

    // For an empty string input, show all
    if (strlen(substr) == 0)
        for (int i = 0;i < repo.countries->size;i++) {
            Country country = da_getElement(*(repo.countries), i);
            printf("Name: %s | Continent: %s | Population: %f\n", country.name, country.continent, country.population);
        }
    // Otherwise use strstr to identify if we have a matching substring
    else
        for (int i = 0;i < repo.countries->size;i++) {
            Country country = da_getElement(*(repo.countries), i);
            if (strstr(country.name, substr) != NULL)
                printf("Name: %s | Continent: %s | Population: %f\n", country.name, country.continent, country.population);
        }

    // Proceed on enter back to the Main Menu
    printf("\n\nPress 'Enter' to continue...");
    enter_proceed();
}

void display_countries_match(Repository repo)
{
    /*
    Displays a list of all countries inside a given continent with a population greater than a given value
    (Sorted Ascendingly by Population)
    */

    char continent[10];
    float population;

    // Dynamic Sized Array for Countries meeting the criteria
    DynamicArray* sorted_countries = da_create(1);

    clear_screen();
    printf("Enter the name of the continent to look for: ");
    scanf("%s", continent);
    printf("Enter the minimum required population: ");
    scanf("%f", &population);

    printf("The countries in ascending order are: \n\n");

    // Obtaining & Sorting the Countries meeting the required criteria
    int k;
    for (int i = 0; i < repo.countries->size; i++) {
        Country country = da_getElement(*repo.countries, i);
        if ((strcmp(country.continent, continent) == 0 || strcmp(continent, "all") == 0) && country.population > population)
        {
            k = 0;
            while (k < sorted_countries->size && (da_getElement(*sorted_countries, k).population > country.population))
                k++;
            da_addToPosition(sorted_countries, k, country);
        }
    }

    // Printing the Countries
    for (int i = 0; i < sorted_countries->size; i++) {
        Country country = da_getElement(*sorted_countries, i);
        printf("Name: %s | Continent: %s | Population: %f\n", country.name, country.continent, country.population);
    }

    // Free Memory of the Dynamic Array
    da_destroy(sorted_countries);

    // Proceed on enter back to the Main Menu
    printf("\n\nPress 'Enter' to continue...");
    enter_proceed();
}

void undo_screen(Repository* repo, DynamicArrayHistory* history)
{
    // Trying to Undo
    clear_screen();
    if(undo(repo, history))
        printf("Undo Successfully executed!\n");
    else
        printf("No more Undos - Operation Aborted!\n");
    
    // Proceed on enter back to the Main Menu
    printf("\n\nPress 'Enter' to continue...");
    enter_proceed();
}

void redo_screen(Repository* repo, DynamicArrayHistory* history)
{
    // Trying to Redo
    clear_screen();
    if (redo(repo, history))
        printf("Redo Successfully executed!\n");
    else
        printf("No more Redos - Operation Aborted!\n");

    // Proceed on enter back to the Main Menu
    printf("\n\nPress 'Enter' to continue...");
    enter_proceed();
}