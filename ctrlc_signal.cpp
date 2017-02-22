
#ifdef _WIN32

    #include "ctrlc_win32.hpp"

#elif defined __GNUG__

    #include "ctrlc_linux.hpp"

#endif

bool EXIT_PROGRAM = false;
