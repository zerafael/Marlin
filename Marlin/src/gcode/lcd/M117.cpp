/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if HAS_STATUS_MESSAGE

#include "../gcode.h"
#include "../../lcd/marlinui.h"

#if ENABLED(CREALITY_TOUCHSCREEN)
  #include "../../lcd/e3v2/creality/lcd_rts.h"
#endif

/**
 * M117: Set LCD Status Message
 */
void GcodeSuite::M117() {
  #if ENABLED(CREALITY_TOUCHSCREEN)
    // clear out our status areas
    for(int j = 0 ; j < TEXTBYTELEN ; j ++) {
      rtscheck.RTS_SndData(0, PRINT_FILE_TEXT_VP + j);
      rtscheck.RTS_SndData(0, SELECT_FILE_TEXT_VP + j);
    }

    if (parser.string_arg && parser.string_arg[0]) {
      char msg[20];

      if (strlen(parser.string_arg) >= TEXTBYTELEN) {
        strncpy(msg, parser.string_arg, TEXTBYTELEN - 1);
        msg[TEXTBYTELEN - 1] = '\0';
      } else {
        strcpy(msg, parser.string_arg);
      }

      rtscheck.RTS_SndData(msg, PRINT_FILE_TEXT_VP);
      rtscheck.RTS_SndData(msg, SELECT_FILE_TEXT_VP);
    }
  #else
    if (parser.string_arg && parser.string_arg[0])
      ui.set_status(parser.string_arg, true);
    else
      ui.reset_status();
  #endif

}

#endif // HAS_STATUS_MESSAGE
