
#if defined _WIN32

    #include "ctrlc_win32.hpp"

#elif defined _GNUG_

    #include "ctrlc_linux.hpp"

#endif

bool EXIT_PROGRAM = false;
