/* RUBIRC
 * Copyright (c) 2010-2012 Berke Viktor.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <winsparkle.h>

#include "rubirc-plugin.h"

#define APPCAST_URL "http://localhost"

static rubirc_plugin *ph;   /* plugin handle */
static char name[] = "Update Checker";
static char desc[] = "Check for RUBIRC updates automatically";
static char version[] = "5.0";
static const char upd_help[] = "Update Checker Usage:\n  /UPDCHK, check for RUBIRC updates\n";

static int
check_cmd (char *word[], char *word_eol[], void *userdata)
{
	win_sparkle_check_update_with_ui ();

	return RUBIRC_EAT_ALL;
}

int
rubirc_plugin_init (rubirc_plugin *plugin_handle, char **plugin_name, char **plugin_desc, char **plugin_version, char *arg)
{
	ph = plugin_handle;

	*plugin_name = name;
	*plugin_desc = desc;
	*plugin_version = version;

	win_sparkle_set_appcast_url (APPCAST_URL);
	win_sparkle_init ();

	rubirc_hook_command (ph, "UPDCHK", RUBIRC_PRI_NORM, check_cmd, upd_help, NULL);
	rubirc_command (ph, "MENU -ishare\\download.png ADD \"Help/Check for Updates\" \"UPDCHK\"");
	rubirc_printf (ph, "%s plugin loaded\n", name);

	return 1;
}

int
rubirc_plugin_deinit (void)
{
	win_sparkle_cleanup ();

	rubirc_command (ph, "MENU DEL \"Help/Check for updates\"");
	rubirc_printf (ph, "%s plugin unloaded\n", name);
	return 1;
}
