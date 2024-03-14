#include "Tests.h"

// TESTS BELOW
int TestAll() {
    int result = 1; // Assume success by default

    result &= TestAddition();
    result &= TestRemoval();
    result &= TestUpdate();
    result &= TestMigrate();
    result &= TestUndoRedo();

    if (result)
        printf("All tests passed successfully!\n");
    else
        printf("There have been some errors...!\n");

    return result;
}

// Method for testing country addition
int TestAddition() {
    Repository repo;
    repo.countries = da_create(10);

    // Adding a country
    Country new_country = { "France", "Europe", 67.06 };
    add_country(new_country, &repo);

    // Testing if the country was added
    int index = find_country("France", repo);
    if (index == -1) {
        printf("TestAddition failed: Country was not added\n");
        return 0;
    }

    da_destroy(repo.countries);

    return 1;
}

// Method for testing country removal
int TestRemoval() {
    Repository repo;
    repo.countries = da_create(10);

    // Adding a country
    Country new_country = { "France", "Europe", 67.06 };
    add_country(new_country, &repo);

    // Removing the added country
    int removed = remove_country("France", &repo);

    // Testing if the country was removed
    if (!removed || find_country("France", repo) != -1) {
        printf("TestRemoval failed: Country was not removed\n");
        return 0;
    }

    da_destroy(repo.countries);

    return 1;
}

// Method for testing country update
int TestUpdate() {
    Repository repo;
    repo.countries = da_create(10);

    // Adding a country
    Country new_country = { "France", "Europe", 67.06 };
    add_country(new_country, &repo);

    // Updating the added country
    Country updated_country = { "France", "Europe", 70.00 };
    update_country(updated_country, 0, &repo);

    // Testing if the country was updated
    Country updated = da_getElement(*repo.countries, 0);
    if (updated.population != 70.00) {
        printf("TestUpdate failed: Country was not updated\n");
        return 0;
    }

    da_destroy(repo.countries);

    return 1;
}

// Method for testing migration
int TestMigrate() {
    Repository repo;
    repo.countries = da_create(10);

    // Adding two countries
    Country origin_country = { "France", "Europe", 60 };
    add_country(origin_country, &repo);

    Country destination_country = { "Germany", "Europe", 80 };
    add_country(destination_country, &repo);

    // Migrating citizens from origin to destination
    migrate(0, 1, 10, &repo);

    // Testing if migration occurred successfully
    Country updated_origin = da_getElement(*repo.countries, 0);
    Country updated_destination = da_getElement(*repo.countries, 1);
    if (updated_origin.population != 50 || updated_destination.population != 90) {
        printf("TestMigrate failed: Migration was not successful\n");
        return 0;
    }

    da_destroy(repo.countries);

    return 1;
}

// Method for testing undo and redo operations
// Undo / Redo has the same method for any kind of operation, thus we'll only test on the update feature
int TestUndoRedo() {
    Repository repo;
    repo.countries = da_create(10);

    // Adding a country
    Country new_country = { "France", "Europe", 60 };
    add_country(new_country, &repo);

    // Recording state for undo/redo
    DynamicArrayHistory* history = da_create_history();
    history->index = -1;
    record_state(repo, history);

    // Updating the added country
    Country updated_country = { "France", "Europe", 70 };
    update_country(updated_country, 0, &repo);
    record_state(repo, history); // Recording updated state

    // Undoing the update
    undo(&repo, history);

    // Testing if the undo operation was successful
    Country undone = da_getElement(*repo.countries, 0);
    if (undone.population != 60) {
        printf("TestUndoRedo failed: Undo operation was not successful\n");
        return 0;
    }

    // Redoing the update
    int redo_result = redo(&repo, history); // Check the return value

    // Testing if the redo operation was successful
    if (redo_result == 0) { // Check if redo failed
        printf("TestUndoRedo failed: Redo operation failed\n");
        return 0;
    }

    Country redone = da_getElement(*repo.countries, 0);
    if (redone.population != 70) {
        printf("TestUndoRedo failed: Redo operation was not successful\n");
        return 0;
    }

    da_destroy(repo.countries);
    da_destroy_history(history);

    return 1;
}