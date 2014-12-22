
/*
example apps: 
  csv_print / csv_show
  
  csvquote
  csv-split  	https://github.com/PerformanceHorizonGroup/csv-split/blob/master/libcsv.c
	csv-split is a simple utility that can parse and break up large CSV files into smaller peices, with various 
  csv-filter
  
  csv-cut	https://github.com/nektomk/csvcut
  csv-paste
  
  csv-converter  tsv, json, html, wiki, md, 
  https://github.com/webcarrot/csv2json/blob/master/csv2json.c
  
  
  https://raw.githubusercontent.com/SurajGupta/r-source/a9ca6414aba36da7e3e9168aceed00383ea1db10/src/main/scan.c
  
  
*/

// https://github.com/dbro/csvquote/blob/master/csvquote.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define NDEBUG
#include "dbg.h"

#define READ_BUFFER_SIZE 4096
#define NON_PRINTING_FIELD_SEPARATOR 0x1F
#define NON_PRINTING_RECORD_SEPARATOR 0x1E

/*
TODO: verify that it handles multi-byte characters and unicode and utf-8 etc
*/

typedef void (*translator)(const char, const char, const char, char *);
typedef enum { RESTORE_MODE, SANITIZE_MODE } operation_mode;


int main(int argc, char *argv[]) {
    // default parameters
    FILE *input = NULL;
    char del = ',';
    char quo = '"';
    char rec = '\n';
    operation_mode op_mode = SANITIZE_MODE;

    int opt;
    while ((opt = getopt(argc, argv, "usd:tq:r:")) != -1) {
        switch (opt) {
            case 'u':
                op_mode = RESTORE_MODE;
                break;
            case 's':
                op_mode = SANITIZE_MODE;
                break;
            case 'd':
                del = optarg[0]; // byte
                break;
            case 't':
                del = '\t';
                break;
            case 'q':
                quo = optarg[0]; // byte
                break;
            case 'r':
                rec = optarg[0]; // byte
                break;
            case ':':
                // -d or -q or -r without operand
                fprintf(stderr,
                    "Option -%c requires an operand\n", optopt);
                goto usage;
            case '?':
                goto usage;
            default:
                fprintf(stderr,
                    "Unrecognized option: '-%c'\n", optopt);
                goto usage;
        }
    }
/*
    // Process stdin or file names
    if (optind >= argc) {
        check(copy_file(stdin, op_mode, del, quo, rec) == 0,
            "failed to copy from stdin");
    } else {
        // supports multiple file names
        int i;
        for (i=optind; i<argc; i++) {
            input = fopen(argv[i], "r");
            check(input != 0, "failed to open file %s", argv[optind]);
            check(copy_file(input, op_mode, del, quo, rec) == 0,
                "failed to copy from file %s", argv[i]);
            if (input) { fclose(input); }
        }
    }
*/
    return 0;

usage:
    fprintf(stderr, "Usage: %s [OPTION] [files]\n", argv[0]);
    fprintf(stderr, "\tfiles are zero or more filenames. If none given, read from standard input\n");
    fprintf(stderr, "\t-u\tdefault false\trestore mode. replace nonprinting characters with original characters\n");
    fprintf(stderr, "\t-d\tdefault ,\tfield separator character\n");
    fprintf(stderr, "\t-t\tdefault false\tuse tab as the field separator character\n");
    fprintf(stderr, "\t-q\tdefault \"\tfield quoting character\n");
    fprintf(stderr, "\t-r\tdefault \\n\trecord separator character\n");
    return 1;

error:
    if (input) { fclose(input); }
    return 1;
}
