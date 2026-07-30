# @ANSI

```
$ atansi --help
atansi (@ANSI)
    Usage: atansi [FILENAME]
        or atansi --version

    replace macros with @ to ANSI color escape code
    in selected file or stdin

    list of macros:
        @@            : @
        @0            : \e[0m (reset)
        @1, @b        : \e[1m (bold)
        @2, @(dim)    : \e[2m (dim/faint)
        @3, @i        : \e[3m (italic)
        @4, @u        : \e[4m (underline)
        @5, @(blink)  : \e[5m (blink)
        @6, @(fblink) : \e[6m (fast blink)
        @7, @r        : \e[7m (reverse)
        @8, @(hidden) : \e[8m (invisible)
        @9, @s        : \e[9m (strikethrough)

        @(30), @(black)   : \e[30m (black)
        @(31), @(red)     : \e[31m (red)
        @(32), @(green)   : \e[32m (green)
        @(33), @(yellow)  : \e[33m (yellow)
        @(34), @(blue)    : \e[34m (blue)
        @(35), @(magenta) : \e[35m (magenta)
        @(36), @(cian)    : \e[36m (cian)
        @(37), @(white)   : \e[37m (white)

        @(40), @(blackb)   : \e[40m (black)
        @(41), @(redb)     : \e[41m (red)
        @(42), @(greenb)   : \e[42m (green)
        @(43), @(yellowb)  : \e[43m (yellow)
        @(44), @(blueb)    : \e[44m (blue)
        @(45), @(magentab) : \e[45m (magenta)
        @(46), @(cianb)    : \e[46m (cian)
        @(47), @(whiteb)   : \e[47m (white)
```
