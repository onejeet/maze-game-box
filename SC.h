

/*
 *
 * SC
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : SC.h
 * Date                : 19.07.2007
 * Font size in bytes  : 6732
 * Font width          : 6
 * Font height         : 13
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef SC_H
#define SC_H

#define SC_WIDTH 4
#define SC_HEIGHT 6

static uint8_t SC[] PROGMEM = {
    0x1A, 0x4C, // size
    0x04, // width
    0x06, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x01, 0x03, 0x06, 0x05, 0x09, 0x09, 0x01, 0x03, 0x03, 
    0x05, 0x07, 0x02, 0x03, 0x01, 0x03, 0x05, 0x03, 0x05, 0x05, 
    0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x01, 0x02, 0x06, 0x06, 
    0x06, 0x04, 0x0A, 0x08, 0x07, 0x07, 0x08, 0x07, 0x06, 0x08, 
    0x08, 0x03, 0x04, 0x08, 0x07, 0x0B, 0x08, 0x08, 0x06, 0x08, 
    0x08, 0x05, 0x07, 0x08, 0x07, 0x0B, 0x08, 0x08, 0x07, 0x03, 
    0x03, 0x02, 0x06, 0x06, 0x02, 0x05, 0x05, 0x04, 0x06, 0x04, 
    0x04, 0x05, 0x06, 0x03, 0x02, 0x06, 0x03, 0x09, 0x06, 0x05, 
    0x06, 0x06, 0x04, 0x04, 0x03, 0x06, 0x06, 0x09, 0x05, 0x07, 
    0x05, 0x03, 0x01, 0x03, 0x05, 0x06, 
    
    // font data
    0xFE, 0x10, // 33
    0x0E, 0x00, 0x0E, 0x00, 0x00, 0x00, // 34
    0xD0, 0x78, 0x56, 0x50, 0xF8, 0x56, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, // 35
    0x1C, 0x12, 0xFF, 0x22, 0xC4, 0x08, 0x10, 0x38, 0x10, 0x08, // 36
    0x0C, 0x12, 0x8C, 0x40, 0x30, 0x08, 0x86, 0x40, 0x80, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x08, 0x10, 0x08, // 37
    0xC0, 0x20, 0x3C, 0xD2, 0x8A, 0x46, 0x30, 0x10, 0x00, 0x08, 0x10, 0x10, 0x10, 0x08, 0x10, 0x10, 0x10, 0x08, // 38
    0x0E, 0x00, // 39
    0xF0, 0x0C, 0x02, 0x08, 0x30, 0x40, // 40
    0x02, 0x0C, 0xF0, 0x40, 0x30, 0x08, // 41
    0x14, 0x08, 0x3E, 0x08, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x20, 0x20, 0x20, 0xFC, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x50, 0x30, // 44
    0x80, 0x80, 0x80, 0x00, 0x00, 0x00, // 45
    0x00, 0x10, // 46
    0x00, 0xF8, 0x06, 0x18, 0x00, 0x00, // 47
    0xFC, 0x02, 0x02, 0x02, 0xFC, 0x08, 0x10, 0x10, 0x10, 0x08, // 48
    0x04, 0xFE, 0x00, 0x10, 0x18, 0x10, // 49
    0x04, 0x02, 0x82, 0x42, 0x3C, 0x10, 0x18, 0x10, 0x10, 0x18, // 50
    0x04, 0x02, 0x22, 0x32, 0xCC, 0x10, 0x10, 0x10, 0x10, 0x08, // 51
    0xC0, 0xA0, 0x90, 0x8C, 0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, // 52
    0x00, 0x0C, 0x0A, 0x12, 0xE2, 0x10, 0x10, 0x10, 0x08, 0x00, // 53
    0xF0, 0x28, 0x14, 0x12, 0xE2, 0x08, 0x10, 0x10, 0x10, 0x08, // 54
    0x04, 0x02, 0x02, 0xF2, 0x0E, 0x00, 0x00, 0x18, 0x00, 0x00, // 55
    0x8C, 0x52, 0x62, 0x52, 0x8C, 0x08, 0x10, 0x10, 0x10, 0x08, // 56
    0x3C, 0x42, 0x42, 0xC2, 0x7C, 0x10, 0x10, 0x08, 0x00, 0x00, // 57
    0x10, 0x10, // 58
    0x10, 0x00, 0x50, 0x30, // 59
    0x20, 0x50, 0x50, 0x50, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x88, 0x88, 0x50, 0x50, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x0C, 0xC2, 0x22, 0x1C, 0x00, 0x10, 0x00, 0x00, // 63
    0xF0, 0x08, 0xE4, 0x12, 0x0A, 0x0A, 0x92, 0x7A, 0x04, 0xF8, 0x18, 0x20, 0x48, 0x90, 0x90, 0x88, 0x88, 0x90, 0x48, 0x20, // 64
    0x00, 0x80, 0x78, 0x46, 0x58, 0x60, 0x80, 0x00, 0x10, 0x18, 0x10, 0x00, 0x00, 0x10, 0x18, 0x10, // 65
    0x02, 0xFE, 0x22, 0x22, 0x22, 0x3C, 0xC0, 0x10, 0x18, 0x10, 0x10, 0x10, 0x10, 0x08, // 66
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x04, 0x8E, 0x00, 0x08, 0x10, 0x10, 0x10, 0x08, 0x00, // 67
    0x02, 0xFE, 0x02, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x10, 0x18, 0x10, 0x10, 0x10, 0x10, 0x08, 0x00, // 68
    0x02, 0xFE, 0x22, 0x22, 0x72, 0x06, 0x00, 0x10, 0x18, 0x10, 0x10, 0x10, 0x10, 0x08, // 69
    0x02, 0xFE, 0x22, 0x22, 0x72, 0x06, 0x10, 0x18, 0x10, 0x00, 0x00, 0x00, // 70
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x24, 0xEE, 0x20, 0x00, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x00, // 71
    0x02, 0xFE, 0x22, 0x20, 0x20, 0x22, 0xFE, 0x02, 0x10, 0x18, 0x10, 0x00, 0x00, 0x10, 0x18, 0x10, // 72
    0x02, 0xFE, 0x02, 0x10, 0x18, 0x10, // 73
    0x00, 0x02, 0xFE, 0x02, 0x18, 0x10, 0x08, 0x00, // 74
    0x02, 0xFE, 0x22, 0x50, 0x88, 0x06, 0x02, 0x02, 0x10, 0x18, 0x10, 0x00, 0x00, 0x18, 0x10, 0x10, // 75
    0x02, 0xFE, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x10, 0x10, 0x10, 0x10, 0x08, // 76
    0x02, 0xFE, 0x06, 0x38, 0xC0, 0x00, 0xE0, 0x18, 0x06, 0xFE, 0x02, 0x10, 0x18, 0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 0x10, 0x18, 0x10, // 77
    0x02, 0xFE, 0x08, 0x10, 0x60, 0x82, 0xFE, 0x02, 0x10, 0x18, 0x10, 0x00, 0x00, 0x00, 0x18, 0x00, // 78
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x00, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x00, // 79
    0x02, 0xFE, 0x22, 0x22, 0x22, 0x1C, 0x10, 0x18, 0x10, 0x00, 0x00, 0x00, // 80
    0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x00, 0x08, 0x10, 0x10, 0x30, 0x50, 0x48, 0x40, // 81
    0x02, 0xFE, 0x22, 0x22, 0xE2, 0x1C, 0x00, 0x00, 0x10, 0x18, 0x10, 0x00, 0x00, 0x08, 0x10, 0x10, // 82
    0x0C, 0x12, 0x22, 0x22, 0xC6, 0x18, 0x10, 0x10, 0x10, 0x08, // 83
    0x06, 0x02, 0x02, 0xFE, 0x02, 0x02, 0x06, 0x00, 0x00, 0x10, 0x18, 0x10, 0x00, 0x00, // 84
    0x02, 0xFE, 0x02, 0x00, 0x00, 0x02, 0xFE, 0x02, 0x00, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x00, // 85
    0x02, 0x1E, 0xE2, 0x00, 0xE2, 0x1E, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // 86
    0x02, 0x1E, 0xE2, 0x80, 0x62, 0x1E, 0xE2, 0x80, 0x72, 0x0E, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // 87
    0x02, 0x06, 0x8A, 0x70, 0x70, 0x8A, 0x06, 0x02, 0x10, 0x18, 0x10, 0x00, 0x00, 0x10, 0x18, 0x10, // 88
    0x02, 0x06, 0x3A, 0xC0, 0x30, 0x0A, 0x06, 0x02, 0x00, 0x00, 0x10, 0x18, 0x10, 0x00, 0x00, 0x00, // 89
    0x00, 0x86, 0x42, 0x32, 0x0A, 0x06, 0x82, 0x10, 0x18, 0x10, 0x10, 0x10, 0x10, 0x18, // 90
    0xFE, 0x02, 0x02, 0x78, 0x40, 0x40, // 91
    0x06, 0xF8, 0x00, 0x00, 0x00, 0x18, // 92
    0x02, 0xFE, 0x40, 0x78, // 93
    0x10, 0x0C, 0x02, 0x02, 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x04, 0x08, 0x00, 0x00, // 96
    0xA0, 0x50, 0x50, 0xE0, 0x00, 0x08, 0x10, 0x10, 0x18, 0x10, // 97
    0xFE, 0x20, 0x10, 0x10, 0xE0, 0x08, 0x10, 0x10, 0x10, 0x08, // 98
    0xE0, 0x10, 0x10, 0x30, 0x08, 0x10, 0x10, 0x08, // 99
    0xE0, 0x10, 0x10, 0x22, 0xFE, 0x00, 0x08, 0x10, 0x10, 0x08, 0x18, 0x10, // 100
    0xE0, 0x50, 0x50, 0x60, 0x08, 0x10, 0x10, 0x08, // 101
    0x10, 0xFC, 0x12, 0x02, 0x10, 0x18, 0x10, 0x00, // 102
    0x60, 0x90, 0x90, 0x70, 0x10, 0x68, 0x90, 0x90, 0x90, 0x60, // 103
    0x02, 0xFE, 0x20, 0x10, 0xE0, 0x00, 0x10, 0x18, 0x10, 0x00, 0x18, 0x10, // 104
    0x10, 0xF2, 0x00, 0x10, 0x18, 0x10, // 105
    0x10, 0xF2, 0x80, 0x78, // 106
    0x02, 0xFE, 0x40, 0xB0, 0x10, 0x00, 0x10, 0x18, 0x10, 0x00, 0x18, 0x10, // 107
    0x02, 0xFE, 0x00, 0x10, 0x18, 0x10, // 108
    0x10, 0xF0, 0x20, 0x10, 0xE0, 0x20, 0x10, 0xE0, 0x00, 0x10, 0x18, 0x10, 0x00, 0x18, 0x10, 0x00, 0x18, 0x10, // 109
    0x10, 0xF0, 0x20, 0x10, 0xE0, 0x00, 0x10, 0x18, 0x10, 0x00, 0x18, 0x10, // 110
    0xE0, 0x10, 0x10, 0x10, 0xE0, 0x08, 0x10, 0x10, 0x10, 0x08, // 111
    0x10, 0xF0, 0x20, 0x10, 0x10, 0xE0, 0x80, 0xF8, 0x88, 0x10, 0x10, 0x08, // 112
    0xE0, 0x10, 0x10, 0x20, 0xF0, 0x00, 0x08, 0x10, 0x10, 0x88, 0xF8, 0x80, // 113
    0x10, 0xF0, 0x20, 0x10, 0x10, 0x18, 0x10, 0x00, // 114
    0x60, 0x50, 0x90, 0xB0, 0x18, 0x10, 0x10, 0x08, // 115
    0x10, 0xFC, 0x10, 0x00, 0x18, 0x10, // 116
    0x10, 0xF0, 0x00, 0x10, 0xF0, 0x00, 0x00, 0x08, 0x10, 0x10, 0x18, 0x10, // 117
    0x30, 0xD0, 0x00, 0xC0, 0x30, 0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // 118
    0x10, 0xF0, 0x00, 0x90, 0xF0, 0x10, 0xC0, 0x30, 0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // 119
    0x10, 0x30, 0xC0, 0x30, 0x10, 0x10, 0x18, 0x00, 0x18, 0x10, // 120
    0x10, 0x70, 0x90, 0x00, 0xD0, 0x30, 0x10, 0x80, 0x80, 0x48, 0x30, 0x08, 0x00, 0x00, // 121
    0x30, 0x10, 0xD0, 0x30, 0x10, 0x10, 0x18, 0x10, 0x10, 0x18, // 122
    0x40, 0xBC, 0x02, 0x00, 0x38, 0x40, // 123
    0xFE, 0x78, // 124
    0x02, 0xBC, 0x40, 0x40, 0x38, 0x00, // 125
    0x80, 0x40, 0xC0, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFC, 0x04, 0x04, 0x04, 0x04, 0xFC, 0x18, 0x10, 0x10, 0x10, 0x10, 0x18 // 127
    
};

#endif
