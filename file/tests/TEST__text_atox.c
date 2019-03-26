/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TEST__text_atox.c
 * Author: greg
 *
 * Created on December 11, 2017, 12:09 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Simple C Test Suite
 */

int text_atox(char* hex_string_p);

void testText_atox() {
    char* hex_string_p;
    int result = text_atox(hex_string_p);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testText_atox (TEST__text_atox) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% TEST__text_atox\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testText_atox (TEST__text_atox)\n");
    testText_atox();
    printf("%%TEST_FINISHED%% time=0 testText_atox (TEST__text_atox)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
