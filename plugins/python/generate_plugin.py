#!/usr/bin/env python3

import sys
import cffi

builder = cffi.FFI()

# rubirc-plugin.h
with open(sys.argv[1]) as f:
    output = []
    eat_until_endif = 0
    # This is very specific to rubirc-plugin.h, it is not a cpp
    for line in f:
        if line.startswith('#define'):
            continue
        elif line.endswith('RUBIRC_PLUGIN_H\n'):
            continue
        elif 'time.h' in line:
            output.append('typedef int... time_t;')
        elif line.startswith('#if'):
            eat_until_endif += 1
        elif line.startswith('#endif'):
            eat_until_endif -= 1
        elif eat_until_endif and '_rubirc_context' not in line:
            continue
        else:
            output.append(line)
    builder.cdef(''.join(output))

builder.embedding_api('''
extern "Python" int _on_py_command(char **, char **, void *);
extern "Python" int _on_load_command(char **, char **, void *);
extern "Python" int _on_unload_command(char **, char **, void *);
extern "Python" int _on_reload_command(char **, char **, void *);
extern "Python" int _on_say_command(char **, char **, void *);

extern "Python" int _on_command_hook(char **, char **, void *);
extern "Python" int _on_print_hook(char **, void *);
extern "Python" int _on_print_attrs_hook(char **, rubirc_event_attrs *, void *);
extern "Python" int _on_server_hook(char **, char **, void *);
extern "Python" int _on_server_attrs_hook(char **, char **, rubirc_event_attrs *, void *);
extern "Python" int _on_timer_hook(void *);

extern "Python" int _on_plugin_init(char **, char **, char **, char *, char *);
extern "Python" int _on_plugin_deinit(void);

static rubirc_plugin *ph;
''')

builder.set_source('_rubirc_embedded', '''
/* Python's header defines these.. */
#undef HAVE_MEMRCHR
#undef HAVE_STRINGS_H

#include "config.h"
#include "rubirc-plugin.h"

static rubirc_plugin *ph;
CFFI_DLLEXPORT int _on_plugin_init(char **, char **, char **, char *, char *);
CFFI_DLLEXPORT int _on_plugin_deinit(void);

int rubirc_plugin_init(rubirc_plugin *plugin_handle,
                        char **name_out, char **description_out,
                        char **version_out, char *arg)
{
    if (ph != NULL)
    {
        puts ("Python plugin already loaded\\n");
        return 0; /* Prevent loading twice */
    }

    ph = plugin_handle;
    return _on_plugin_init(name_out, description_out, version_out, arg, RUBIRCLIBDIR);
}

int rubirc_plugin_deinit(void)
{
    int ret = _on_plugin_deinit();
    ph = NULL;
    return ret;
}
''')

# python.py
with open(sys.argv[2]) as f:
    builder.embedding_init_code(f.read())

# python.c
builder.emit_c_code(sys.argv[3])
