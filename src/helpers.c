#include "helpers.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>


void
chip8_help()
{
    //TODO Make print how to use program 
    printf("HELP\n");
}

char *
chip8_parse_args(int argc, char *argv[])
{
    int c;
    char *buffer = NULL;
    char *game_name = NULL;

    while((c = getopt(argc, argv, "g:")) != -1){
        switch(c){
            case 'g':
                game_name = optarg;
                break;
            case '?':
                if(optopt == 'g'){
                    fprintf(stderr, "Option -g requires an argument\n");
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Unkown option character\n");
                }
                break;
            default:
                abort();
        }
    }
   if(game_name != NULL){

        game_name = chip8_determine_game_name(game_name);
    }
    return game_name;
}

char *
chip8_determine_game_name(char *filename)
{
    char *buffer = NULL;
    char *suffix = ".ch8";
    char *prefix = "../ROMs/";
    size_t prefix_len = strlen(prefix);
    size_t str_len = strlen(filename);
    size_t suffix_len = strlen(suffix);
    if(strncmp(filename + str_len - suffix_len, suffix, suffix_len) != 0){
        buffer = malloc(str_len + suffix_len + prefix_len +1);
        if(buffer == NULL) abort();
        strcpy(buffer, prefix);
        strcat(buffer, filename);
        strcat(buffer, suffix);
        return buffer;
    }else{
        buffer = malloc(str_len + prefix_len +1);
        strcpy(buffer, prefix);
        strcat(buffer, filename);
        return buffer;
    }
}