#pragma once

// Country Type - has a name (string ), continent ( string ) and population ( floating point, represent population in millions)
typedef struct
{
    char name[64];
    char continent[64];
    float population;
} Country;
