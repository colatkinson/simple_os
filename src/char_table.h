#pragma once
/* Char map, with modifiers */

/* normal,shift,control,alt */

unsigned char char_table[][4] =
{
    {0, 0, 0, 0},
    {27, 27, 27, 27},
    {'1', '!', 0, '1'},
    {'2', '"', 0, '2'},
    {'3', 156, 0, '3'},
    {'4', '$', 0, '4'},
    {'5', '%', 0, '5'},
    {'6', '&', 0, '6'},
    {'7', '/', 0, '7'},
    {'8', '(', 0, '{'},
    {'9', ')', 0, '}'},
    {'0', '=', 0, '~'},
    {39, '?', 0, '`'},
    {141, '^', 0, 0},
    {127, 127, 127, 127},
    {9, 9, 9, 9},
    {'q', 'Q', 0, 'q'},
    {'w', 'W', 0, 'w'},
    {'e', 'E', 0, 'e'},
    {'r', 'R', 0, 'r'},
    {'t', 'T', 0, 't'},
    {'y', 'Y', 0, 'y'},
    {'u', 'U', 0, 'u'},
    {'i', 'I', 0, 'i'},
    {'o', 'O', 0, 'o'},
    {'p', 'P', 0, 'p'},
    {138, 130, 0, '['},
    {'+', '*', 0, ']'},
    {'\n', '\n', '\n', '\n'}, /* Return */
    {0, 0, 0, 0}, /* left CONTROL */
    {'a', 'A', 0, 'a'},
    {'s', 'S', 0, 's'},
    {'d', 'D', 0, 'd'},
    {'f', 'F', 0, 'f'},
    {'g', 'G', 0, 'g'},
    {'h', 'H', 0, 'h'},
    {'j', 'J', 0, 'j'},
    {'k', 'K', 0, 'k'},
    {'l', 'L', 0, 'l'},
    {162, 128, 0, '@'},
    {133, 248, 0, '#'},
    {'\\', '|', 0, '\\'},
    {0, 0, 0, 0}, /* left Shift */
    {151, 0, 0, 0},
    {'z', 'Z', 0, 'z'},
    {'x', 'X', 0, 'x'},
    {'c', 'C', 0, 'c'},
    {'v', 'V', 0, 'v'},
    {'b', 'B', 0, 'b'},
    {'n', 'N', 0, 'n'},
    {'m', 'M', 0, 'm'},
    {',', ';', 0, 0},
    {'.', ':', 0, 0},
    {'-', '_', 0, 0},
    {0, 0, 0, 0},          /* right Shift */
    {'*', '*', 0, '*'},    /* * of numeric pad */
    {0, 0, 0, 0},          /* left Alt */
    {' ', ' ', 0, 0},
    {0, 0, 0, 0},          /* Caps Lock */
    {0, 0, 0, 0},          /* F1 */
    {0, 0, 0, 0},          /* F2 */
    {0, 0, 0, 0},          /* F3 */
    {0, 0, 0, 0},          /* F4 */
    {0, 0, 0, 0},          /* F5 */
    {0, 0, 0, 0},          /* F6 */
    {0, 0, 0, 0},          /* F7 */
    {0, 0, 0, 0},          /* F8 */
    {0, 0, 0, 0},          /* F9 */
    {0, 0, 0, 0},          /* F10 */

    {0, 0, 0, 0},          /* NumLock */
    {0, 0, 0, 0},          /* Scroll Lock */

    {'7', '7', 0, '7'},    /* 7 of numeric pad */
    {'8', '8', 0, '8'},
    {'9', '9', 0, '9'},
    {'-', '-', 0, '-'},
    {'4', '4', 0, '4'},
    {'5', '5', 0, '5'},
    {'6', '6', 0, '6'},
    {'+', '+', 0, '+'},
    {'1', '1', 0, '1'},
    {'2', '2', 0, '2'},
    {'3', '3', 0, '3'},
    {'0', '0', 0, '0'},
    {'.', '.', 0, '.'},
    {0, 0, 0, 0}, /* Unknown key */
    {0, 0, 0, 0}, /* Unknown key */
    {0, 0, 0, 0}, /* Unknown key */
    {0, 0, 0, 0}, /* F11 */
    {0, 0, 0, 0}, /* F12 */
};