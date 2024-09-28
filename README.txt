o ---------------------------------------------------------------------------- o
| GTK-4.0 calendar program named *calendar* by Simon Euchner written in C      |
o ---------------------------------------------------------------------------- o


LICENSE NOTICE.

    LICENSES: GPL-3.0

    IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS IF FREE
               TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE
               LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION.
               THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY NEGATIVE
               EFFECTS THIS SOFTWARE MAY CAUSE.


Conventions.

    The code is written with a few conventions I have chosen. If I did not make
    a mistake everything should be consistent. For usage of *const* I have
    adopted the convention to use it mostly but not overdue it artificially.
    Indentations are always 4 spaces. Excpet for the *main* function I have the
    *{* right next to the fucntion header. Prototypes are defined for all
    functions, with the exception of *main*.

    Regarding GTK functions and widgets, I chose to (mostly) not hide widgets
    for the main window in function bodies, which is well possible because of
    the reference-counting GTK does. I have chosen this more *verbose* way to
    make the code, in my humble opinion, more readable and see through. This way
    I hope possible future feature adds are more convenient to implement.


Contents.

    Directories are marked with a *.d* ending.

    src.d     : Source code for program *calendar*.
    inc.d     : Include directory where C headers are stored
    obj.d     : Directory holding object code generated during compilation.
    bin.d     : Directory where the main executable named *calendar* is saved.
    txt.d     : Directory saving notes written by the user in form of text
                files.
    year.txt  : File where last viewed year is saved. Default year at startup of
                *calendar* is this particular year.
    dbtm-*.txt: File to keep track which day buttons to mark. The asterisk shall
                be a placeholder for a year number.

    Filenames are all 4 characters long (without the extension). Only exception
    is *calendar.c*. A list of files is given below:

        calendar.c/.h : Main functions for program *calendar*
        defi.h        : General definitions
        sett.c/.h     : User interface to change settings
        csss.c/.h     : Defines and loads *calendar*s CSS string
        init.c/.h     : Functions to initialize widgets, set widget specific
                        properties and load CSS settings
        calh.c/.h     : Create calendar header
        call.c/.h     : Create calendar layout
        dhcs.c/.h     : Define signal handlers and connect signals
        dtiw.c/.h     : Draw text input window
        dniw.c/.h     : Draw notes input window
        mcdb.c/.h     : Function to mark current day button


Branches.

    main: On this branch I keep the finished program with possible
          changes not included in the current released version. You
          can also try this version if you are feeling a bit more 
          'adventurous'.

    release: Contents of the current release. I consider this (hopefully) stable
             and usable; this is probably what you want. After a few changes
             to *main* have been made, I will merge it into this branch and
             create a new release.

    dev: Here I work on the calendar. Usage of *dev* is just to stay with
         common practice, I obviously do not consider writing a calendar actual
         development. 


Installation instructions.

    Download the latest release on this repository.

    Step 1. *cd* into directory *calendar.d*

    Step 2. Select where you want to store runtime data, i.e. notes,
            current year, etc. and set the correct ABSOLUTE path in the file
            *src.d/sett.h*. In this file the program *calendar* can be
            configured.

    Step 3. Place *dat.d* at the specified position in the file system.
            Obvously you need to have permissions to add and remove files at
            this location.

    Step 4. Run make to compile. Place the binary *calendar* in *bin.d* at a
            place you like. For example in ~/.local/bin.

    Step 5. Congratulations, you have installed *calendar*. The interface is
            self explanatory. Note that the program is written in a way that
            it does not get slower with increasing number of notes. Also,
            it takes care of any unneeded file automatically and the only
            location where it interacts with is *dat.d*.


Final note.

    If you install this program I hope you like it as much as I do.

    For questions/suggestions regarding this program please feel free to open an
    issue. I will try my best to react on the time scale of human life. ;-)

    PS: Please no questions like 'what is a header file'. I gues it is better to
        consult an internet search engine for questions like this.

    PPS: If you actually read this file I thank you and hope you have a very,
         very nice day.
