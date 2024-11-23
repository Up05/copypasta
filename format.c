#include "main.h"


// A_NORMAL       Normal display (no highlight)
// A_STANDOUT     Best highlighting mode of the terminal
// A_UNDERLINE    Underlining
// A_REVERSE      Reverse video
// A_BLINK        Blinking
// A_DIM          Half bright
// A_BOLD         Extra bright or bold
// A_PROTECT      Protected mode
// A_INVIS        Invisible or blank mode
// A_ALTCHARSET   Alternate character set
// A_ITALIC       Italics (non-X/Open extension)
// A_CHARTEXT     Bit-mask to extract a character
// A_COLOR        Bit-mask to extract a color (legacy routines)


int fmt_highlight(bool on) {
    if(on) attron (A_STANDOUT);
    else   attroff(A_STANDOUT);
    return on ? A_STANDOUT : 0;
}

