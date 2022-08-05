/*
 * Copyright (c) 2022 noc
 */

#include "intro.h"

/*
    black:  \x1b[30m
    red:    \x1b[31m
    green:  \x1b[32m
    yellow: \x1b[33m
    blue:   \x1b[34m
    magenta:\x1b[35m
    cyan:   \x1b[36m
    white:  \x1b[37m
    reset:  \x1b[0m
*/

void intro_noc()
{
#ifdef WRITE_STD_OUTPUT

#ifdef LOG_USE_COLOR
    const char *_S = "\x1b[33m";
    const char *_E = "\x1b[0m";
#else
    const char *_S = "";
    const char *_E = "";
#endif

    printf("\n");
    printf("%s  ███╗░░██╗░█████╗░░█████╗░%s\n", _S, _E);
    printf("%s  ████╗░██║██╔══██╗██╔══██╗%s\n", _S, _E);
    printf("%s  ██╔██╗██║██║░░██║██║░░╚═╝%s\n", _S, _E);
    printf("%s  ██║╚████║██║░░██║██║░░██╗%s\n", _S, _E);
    printf("%s  ██║░╚███║╚█████╔╝╚█████╔╝%s\n", _S, _E);
    printf("%s  ╚═╝░░╚══╝░╚════╝░░╚════╝░%s\n", _S, _E);
    printf("\n");
#endif
}

void intro_nova()
{
#ifdef WRITE_STD_OUTPUT

#ifdef LOG_USE_COLOR
    const char *_S = "\x1b[32m";
    const char *_E = "\x1b[0m";
#else
    const char *_S = "";
    const char *_E = "";
#endif

    printf("\n");
    printf("%s  ███╗░░██╗░█████╗░██╗░░░██╗░█████╗░%s\n", _S, _E);
    printf("%s  ████╗░██║██╔══██╗██║░░░██║██╔══██╗%s\n", _S, _E);
    printf("%s  ██╔██╗██║██║░░██║╚██╗░██╔╝███████║%s\n", _S, _E);
    printf("%s  ██║╚████║██║░░██║░╚████╔╝░██╔══██║%s\n", _S, _E);
    printf("%s  ██║░╚███║╚█████╔╝░░╚██╔╝░░██║░░██║%s\n", _S, _E);
    printf("%s  ╚═╝░░╚══╝░╚════╝░░░░╚═╝░░░╚═╝░░╚═╝%s\n", _S, _E);
    printf("\n");
#endif
}

void intro_ac()
{
#ifdef WRITE_STD_OUTPUT

#ifdef LOG_USE_COLOR
    const char *_S = "\x1b[35m";
    const char *_E = "\x1b[0m";
#else
    const char *_S = "";
    const char *_E = "";
#endif
    printf("\n");
    printf("%s  ░█▀▀█ ▒█▀▀█%s\n", _S, _E);
    printf("%s  ▒█▄▄█ ▒█░░░%s\n", _S, _E);
    printf("%s  ▒█░▒█ ▒█▄▄█%s\n", _S, _E);
    printf("\n");
#endif
}

void intro_wtp()
{
#ifdef WRITE_STD_OUTPUT

#ifdef LOG_USE_COLOR
    const char *_S = "\x1b[36m";
    const char *_E = "\x1b[0m";
#else
    const char *_S = "";
    const char *_E = "";
#endif
    printf("\n");
    printf("%s  ▒█░░▒█ ▀▀█▀▀ ▒█▀▀█%s\n", _S, _E);
    printf("%s  ▒█▒█▒█ ░▒█░░ ▒█▄▄█%s\n", _S, _E);
    printf("%s  ▒█▄▀▄█ ░▒█░░ ▒█░░░%s\n", _S, _E);
    printf("\n");
#endif
}

void intro_now()
{
    printf("\n\n\n\n\n");
    time_t now = time(NULL);
    struct tm *info = localtime(&now);
    char buf[64];

    buf[strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", info)] = '\0';
    printf("%s\n", buf);
}

void intro_ver()
{
    env_load("/data/config/capwap", false);
    printf("%s %s\n", getenv("APP"), getenv("VERSION"));
}
