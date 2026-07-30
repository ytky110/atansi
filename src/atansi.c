#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.0.2"
#define MACRO_BUF 20

int substit(FILE* target);

int main(int argc, char** argv) {
    FILE* target;

    argc--;

    if (argc > 1) {
        fprintf(stderr, "atansi: too much argument\n");
        printf("Usage: atansi [FILENAME]\n");
        return 2;
    }

    if (argc == 0) {
        target = stdin;
    }
    else {
        if (strcmp(argv[1], "--help") == 0) {
            printf("atansi (@ANSI)\n");
            printf("    Usage: atansi [FILENAME]\n");
            printf("        or atansi --version\n\n");
            printf("    replace macros with @ to ANSI color escape code\n");
            printf("    in selected file or stdin\n\n");
            printf("    list of macros:\n");
            printf("        @@            : @\n");
            printf("        @0            : \\e[0m (reset)\n");
            printf("        @1, @b        : \\e[1m (\e[1mbold\e[0m)\n");
            printf("        @2, @(dim)    : \\e[2m (\e[2mdim/faint\e[0m)\n");
            printf("        @3, @i        : \\e[3m (\e[3mitalic\e[0m)\n");
            printf("        @4, @u        : \\e[4m (\e[4munderline\e[0m)\n");
            printf("        @5, @(blink)  : \\e[5m (\e[5mblink\e[0m)\n");
            printf("        @6, @(fblink) : \\e[6m (\e[6mfast blink\e[0m)\n");
            printf("        @7, @r        : \\e[7m (\e[7mreverse\e[0m)\n");
            printf("        @8, @(hidden) : \\e[8m (\e[8minvisible\e[0m)\n");
            printf("        @9, @s        : \\e[9m (\e[9mstrikethrough\e[0m)\n");
            printf("\n");
            printf("        @(30), @(black)   : \\e[30m (\e[30mblack\e[0m)\n");
            printf("        @(31), @(red)     : \\e[31m (\e[31mred\e[0m)\n");
            printf("        @(32), @(green)   : \\e[32m (\e[32mgreen\e[0m)\n");
            printf("        @(33), @(yellow)  : \\e[33m (\e[33myellow\e[0m)\n");
            printf("        @(34), @(blue)    : \\e[34m (\e[34mblue\e[0m)\n");
            printf("        @(35), @(magenta) : \\e[35m (\e[35mmagenta\e[0m)\n");
            printf("        @(36), @(cian)    : \\e[36m (\e[36mcian\e[0m)\n");
            printf("        @(37), @(white)   : \\e[37m (\e[37mwhite\e[0m)\n");
            printf("\n");
            printf("        @(40), @(blackb)   : \\e[40m (\e[40mblack\e[0m)\n");
            printf("        @(41), @(redb)     : \\e[41m (\e[41mred\e[0m)\n");
            printf("        @(42), @(greenb)   : \\e[42m (\e[42mgreen\e[0m)\n");
            printf("        @(43), @(yellowb)  : \\e[43m (\e[43myellow\e[0m)\n");
            printf("        @(44), @(blueb)    : \\e[44m (\e[44mblue\e[0m)\n");
            printf("        @(45), @(magentab) : \\e[45m (\e[45mmagenta\e[0m)\n");
            printf("        @(46), @(cianb)    : \\e[46m (\e[46mcian\e[0m)\n");
            printf("        @(47), @(whiteb)   : \\e[47m (\e[47mwhite\e[0m)\n");
            return 0;
        }
        if (strcmp(argv[1], "--version") == 0) {
            printf(
                "atansi %s\n"
                "\n"
                "Written by Yutaka Goy,\n"
                "in C, on 2025-08-09\n", VERSION);
            return 0;
        }

        target = fopen(argv[1], "r");
        if (target == NULL) {
            fprintf(stderr, "atansi: %s: no such file\n", argv[1]);
            return 1;
        }
    }

    substit(target);

    return 0;
}

int substit(FILE* target) {
    signed char c;

    while ((c = fgetc(target)) != EOF) {
        if (c != '@') {
            printf("%c", c);
        }
        else {
            signed char next;
            next = fgetc(target);

            if (next == EOF) {
                if (target != stdin)
                    fclose(target);

                fprintf(stderr, "atansi: EOF after @\n");
                exit(1);
            }
            else if (next == '@') {
                printf("@");
            }
            else if (next == '0') {
                printf("\e[0m");
            }
            else if (next == 'b' || next == '1') {
                printf("\e[1m");
            }
            else if (next == '2') {
                printf("\e[2m");
            }
            else if (next == 'i' || next == '3') {
                printf("\e[3m");
            }
            else if (next == 'u' || next == '4') {
                printf("\e[4m");
            }
            else if (next == '5') {
                printf("\e[5m");
            }
            else if (next == '6') {
                printf("\e[6m");
            }
            else if (next == 'r' || next == '7') {
                printf("\e[7m");
            }
            else if (next == '8') {
                printf("\e[8m");
            }
            else if (next == 's' || next == '9') {
                printf("\e[9m");
            }
            else if (next == '(') {
                signed char buf[MACRO_BUF];
                int i = 0;
                while (1) {
                    if (i >= MACRO_BUF-1) {
                        if (target != stdin)
                            fclose(target);

                        fprintf(stderr, "atansi: too long macro name\n");
                        exit(1);
                    }

                    if ((buf[i] = fgetc(target)) != EOF) {
                        if (buf[i] == ')') {
                            buf[i+1] = '\0';
                            break;
                        }
                    }
                    else {
                        fprintf(stderr, "atansi: EOF in macro name\n");
                        exit(1);
                    }

                    i++;
                }

                if (strcmp(buf, "dim)") == 0) {
                    printf("\e[2m");
                }
                else if (strcmp(buf, "blink)") == 0) {
                    printf("\e[5m");
                }
                else if (strcmp(buf, "fblink)") == 0) {
                    printf("\e[6m");
                }
                else if (strcmp(buf, "hidden)") == 0) {
                    printf("\e[8m");
                }
                else if (strcmp(buf, "black)") == 0 || strcmp(buf, "30)") == 0) {
                    printf("\e[30m");
                }
                else if (strcmp(buf, "red)") == 0 || strcmp(buf, "31)") == 0) {
                    printf("\e[31m");
                }
                else if (strcmp(buf, "green)") == 0 || strcmp(buf, "32)") == 0) {
                    printf("\e[32m");
                }
                else if (strcmp(buf, "yellow)") == 0 || strcmp(buf, "33)") == 0) {
                    printf("\e[33m");
                }
                else if (strcmp(buf, "blue)") == 0 || strcmp(buf, "34)") == 0) {
                    printf("\e[34m");
                }
                else if (strcmp(buf, "magenta)") == 0 || strcmp(buf, "35)") == 0) {
                    printf("\e[35m");
                }
                else if (strcmp(buf, "cian)") == 0 || strcmp(buf, "36)") == 0) {
                    printf("\e[36m");
                }
                else if (strcmp(buf, "white)") == 0 || strcmp(buf, "37)") == 0) {
                    printf("\e[37m");
                }
                else if (strcmp(buf, "blackb)") == 0 || strcmp(buf, "40)") == 0) {
                    printf("\e[40m");
                }
                else if (strcmp(buf, "redb)") == 0 || strcmp(buf, "41)") == 0) {
                    printf("\e[41m");
                }
                else if (strcmp(buf, "greenb)") == 0 || strcmp(buf, "42)") == 0) {
                    printf("\e[42m");
                }
                else if (strcmp(buf, "yellowb)") == 0 || strcmp(buf, "43)") == 0) {
                    printf("\e[43m");
                }
                else if (strcmp(buf, "blueb)") == 0 || strcmp(buf, "44)") == 0) {
                    printf("\e[44m");
                }
                else if (strcmp(buf, "magentab)") == 0 || strcmp(buf, "45)") == 0) {
                    printf("\e[45m");
                }
                else if (strcmp(buf, "cianb)") == 0 || strcmp(buf, "46)") == 0) {
                    printf("\e[46m");
                }
                else if (strcmp(buf, "whiteb)") == 0 || strcmp(buf, "47)") == 0) {
                    printf("\e[47m");
                }
                else {
                    if (target != stdin)
                        fclose(target);
                    fprintf(stderr, "atansi: @(%s: unknown macro\n", buf);
                    exit(1);
                }
            }
            else {
                if (target != stdin)
                    fclose(target);

                fprintf(stderr, "atansi: @%c: unknown macro\n", next);
                exit(1);
            }
        }
    }

    if (target != stdin)
        fclose(target);

    return 0;
}
