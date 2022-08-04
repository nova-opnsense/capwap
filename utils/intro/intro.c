/*
 * Copyright (c) 2022 noc
 */

#include "intro.h"

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
