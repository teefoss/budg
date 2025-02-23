/*
 * budg.c - Monthly Budget Progress Calcuator
 *
 * Copyright (C) 2025 Thomas Foster (www.github.com/teefoss)
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not
 *    be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VERSION "1.0"

const int month_len[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int parse_int(const char * str) {
    char *endptr;
    errno = 0;
    long value = strtol(str, &endptr, 10);

    if ( errno == ERANGE ) {
        printf("Error: value out of range\n");
        exit(EXIT_FAILURE);
    }

    if ( endptr == str || *endptr != '\0' ) {
        printf("Error: invalid number format\n");
        exit(EXIT_FAILURE);
    }

    return (int)value;
}

int main(int argc, char ** argv)
{
    if ( argc == 1 ) {
        printf("Error: expected arguments.\n");
        printf("Usage: %s [initial budget] (current funds)\n", argv[0]);
        printf("       %s --info\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ( strcmp(argv[1], "--info") == 0 ) {
        printf("%s Ver. %s -- Monthly Budget Progress Calculator\n",
               argv[0], VERSION);
        printf("Copyright (C) 2025 Thomas Foster (www.github.com/teefoss)\n");
        return EXIT_SUCCESS;
    }

    int funds = parse_int(argv[1]);
    if ( funds == 0 ) {
        printf("Error: bad budget value\n");
        return EXIT_FAILURE;
    }

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int days_left = month_len[tm_info->tm_mon] - tm_info->tm_mday;
    float progress = (float)days_left / (float)month_len[tm_info->tm_mon];
    float expected = roundf((float)funds * progress);
    
    printf("Current funds should be %.0f.\n", expected);

    if ( argc == 3 ) {
        float actual = (float)parse_int(argv[2]);
        float diff = actual - expected;

        if ( diff == 0.0f ) {
            printf("You are on budget.\n");
        } else {
            printf("You are %s budget by %.0f.\n",
                   diff < 0 ? "over" : "under", fabsf(diff));
        }

        printf("There are %d days left; spend limit of %.0f per day.\n",
               days_left, actual / days_left);
    }

    return EXIT_SUCCESS;
}
