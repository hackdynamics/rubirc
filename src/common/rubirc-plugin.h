/* RUBIRC
 * Copyright (C) 1998-2010 Peter Zelezny.
 * Copyright (C) 2009-2013 Berke Viktor.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* You can distribute this header with your plugins for easy compilation */
#ifndef RUBIRC_PLUGIN_H
#define RUBIRC_PLUGIN_H

#include <time.h>

#define RUBIRC_PRI_HIGHEST	127
#define RUBIRC_PRI_HIGH		64
#define RUBIRC_PRI_NORM		0
#define RUBIRC_PRI_LOW		(-64)
#define RUBIRC_PRI_LOWEST	(-128)

#define RUBIRC_FD_READ		1
#define RUBIRC_FD_WRITE		2
#define RUBIRC_FD_EXCEPTION	4
#define RUBIRC_FD_NOTSOCKET	8

#define RUBIRC_EAT_NONE		0	/* pass it on through! */
#define RUBIRC_EAT_RUBIRC		1	/* don't let RUBIRC see this event */
#define RUBIRC_EAT_PLUGIN	2	/* don't let other plugins see this event */
#define RUBIRC_EAT_ALL		(RUBIRC_EAT_RUBIRC|RUBIRC_EAT_PLUGIN)	/* don't let anything see this event */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _rubirc_plugin rubirc_plugin;
typedef struct _rubirc_list rubirc_list;
typedef struct _rubirc_hook rubirc_hook;
#ifndef PLUGIN_C
typedef struct _rubirc_context rubirc_context;
#endif
typedef struct
{
	time_t server_time_utc; /* 0 if not used */
} rubirc_event_attrs;

#ifndef PLUGIN_C
struct _rubirc_plugin
{
	/* these are only used on win32 */
	rubirc_hook *(*rubirc_hook_command) (rubirc_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);
	rubirc_hook *(*rubirc_hook_server) (rubirc_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);
	rubirc_hook *(*rubirc_hook_print) (rubirc_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);
	rubirc_hook *(*rubirc_hook_timer) (rubirc_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);
	rubirc_hook *(*rubirc_hook_fd) (rubirc_plugin *ph,
		   int fd,
		   int flags,
		   int (*callback) (int fd, int flags, void *user_data),
		   void *userdata);
	void *(*rubirc_unhook) (rubirc_plugin *ph,
	      rubirc_hook *hook);
	void (*rubirc_print) (rubirc_plugin *ph,
	     const char *text);
	void (*rubirc_printf) (rubirc_plugin *ph,
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
	void (*rubirc_command) (rubirc_plugin *ph,
	       const char *command);
	void (*rubirc_commandf) (rubirc_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
	int (*rubirc_nickcmp) (rubirc_plugin *ph,
	       const char *s1,
	       const char *s2);
	int (*rubirc_set_context) (rubirc_plugin *ph,
		   rubirc_context *ctx);
	rubirc_context *(*rubirc_find_context) (rubirc_plugin *ph,
		    const char *servname,
		    const char *channel);
	rubirc_context *(*rubirc_get_context) (rubirc_plugin *ph);
	const char *(*rubirc_get_info) (rubirc_plugin *ph,
		const char *id);
	int (*rubirc_get_prefs) (rubirc_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);
	rubirc_list * (*rubirc_list_get) (rubirc_plugin *ph,
		const char *name);
	void (*rubirc_list_free) (rubirc_plugin *ph,
		 rubirc_list *xlist);
	const char * const * (*rubirc_list_fields) (rubirc_plugin *ph,
		   const char *name);
	int (*rubirc_list_next) (rubirc_plugin *ph,
		 rubirc_list *xlist);
	const char * (*rubirc_list_str) (rubirc_plugin *ph,
		rubirc_list *xlist,
		const char *name);
	int (*rubirc_list_int) (rubirc_plugin *ph,
		rubirc_list *xlist,
		const char *name);
	void * (*rubirc_plugingui_add) (rubirc_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);
	void (*rubirc_plugingui_remove) (rubirc_plugin *ph,
			void *handle);
	int (*rubirc_emit_print) (rubirc_plugin *ph,
			const char *event_name, ...);
	int (*rubirc_read_fd) (rubirc_plugin *ph,
			void *src,
			char *buf,
			int *len);
	time_t (*rubirc_list_time) (rubirc_plugin *ph,
		rubirc_list *xlist,
		const char *name);
	char *(*rubirc_gettext) (rubirc_plugin *ph,
		const char *msgid);
	void (*rubirc_send_modes) (rubirc_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);
	char *(*rubirc_strip) (rubirc_plugin *ph,
	     const char *str,
	     int len,
	     int flags);
	void (*rubirc_free) (rubirc_plugin *ph,
	    void *ptr);
	int (*rubirc_pluginpref_set_str) (rubirc_plugin *ph,
		const char *var,
		const char *value);
	int (*rubirc_pluginpref_get_str) (rubirc_plugin *ph,
		const char *var,
		char *dest);
	int (*rubirc_pluginpref_set_int) (rubirc_plugin *ph,
		const char *var,
		int value);
	int (*rubirc_pluginpref_get_int) (rubirc_plugin *ph,
		const char *var);
	int (*rubirc_pluginpref_delete) (rubirc_plugin *ph,
		const char *var);
	int (*rubirc_pluginpref_list) (rubirc_plugin *ph,
		char *dest);
	rubirc_hook *(*rubirc_hook_server_attrs) (rubirc_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							rubirc_event_attrs *attrs, void *user_data),
		   void *userdata);
	rubirc_hook *(*rubirc_hook_print_attrs) (rubirc_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], rubirc_event_attrs *attrs,
						   void *user_data),
		  void *userdata);
	int (*rubirc_emit_print_attrs) (rubirc_plugin *ph, rubirc_event_attrs *attrs,
									 const char *event_name, ...);
	rubirc_event_attrs *(*rubirc_event_attrs_create) (rubirc_plugin *ph);
	void (*rubirc_event_attrs_free) (rubirc_plugin *ph,
									  rubirc_event_attrs *attrs);
};
#endif


rubirc_hook *
rubirc_hook_command (rubirc_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);

rubirc_event_attrs *rubirc_event_attrs_create (rubirc_plugin *ph);

void rubirc_event_attrs_free (rubirc_plugin *ph, rubirc_event_attrs *attrs);

rubirc_hook *
rubirc_hook_server (rubirc_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);

rubirc_hook *
rubirc_hook_server_attrs (rubirc_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							rubirc_event_attrs *attrs, void *user_data),
		   void *userdata);

rubirc_hook *
rubirc_hook_print (rubirc_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);

rubirc_hook *
rubirc_hook_print_attrs (rubirc_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], rubirc_event_attrs *attrs,
						   void *user_data),
		  void *userdata);

rubirc_hook *
rubirc_hook_timer (rubirc_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);

rubirc_hook *
rubirc_hook_fd (rubirc_plugin *ph,
		int fd,
		int flags,
		int (*callback) (int fd, int flags, void *user_data),
		void *userdata);

void *
rubirc_unhook (rubirc_plugin *ph,
	      rubirc_hook *hook);

void
rubirc_print (rubirc_plugin *ph,
	     const char *text);

void
rubirc_printf (rubirc_plugin *ph,
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

void
rubirc_command (rubirc_plugin *ph,
	       const char *command);

void
rubirc_commandf (rubirc_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

int
rubirc_nickcmp (rubirc_plugin *ph,
	       const char *s1,
	       const char *s2);

int
rubirc_set_context (rubirc_plugin *ph,
		   rubirc_context *ctx);

rubirc_context *
rubirc_find_context (rubirc_plugin *ph,
		    const char *servname,
		    const char *channel);

rubirc_context *
rubirc_get_context (rubirc_plugin *ph);

const char *
rubirc_get_info (rubirc_plugin *ph,
		const char *id);

int
rubirc_get_prefs (rubirc_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);

rubirc_list *
rubirc_list_get (rubirc_plugin *ph,
		const char *name);

void
rubirc_list_free (rubirc_plugin *ph,
		 rubirc_list *xlist);

const char * const *
rubirc_list_fields (rubirc_plugin *ph,
		   const char *name);

int
rubirc_list_next (rubirc_plugin *ph,
		 rubirc_list *xlist);

const char *
rubirc_list_str (rubirc_plugin *ph,
		rubirc_list *xlist,
		const char *name);

int
rubirc_list_int (rubirc_plugin *ph,
		rubirc_list *xlist,
		const char *name);

time_t
rubirc_list_time (rubirc_plugin *ph,
		 rubirc_list *xlist,
		 const char *name);

void *
rubirc_plugingui_add (rubirc_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);

void
rubirc_plugingui_remove (rubirc_plugin *ph,
			void *handle);

int 
rubirc_emit_print (rubirc_plugin *ph,
		  const char *event_name, ...);

int 
rubirc_emit_print_attrs (rubirc_plugin *ph, rubirc_event_attrs *attrs,
						  const char *event_name, ...);

char *
rubirc_gettext (rubirc_plugin *ph,
	       const char *msgid);

void
rubirc_send_modes (rubirc_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);

char *
rubirc_strip (rubirc_plugin *ph,
	     const char *str,
	     int len,
	     int flags);

void
rubirc_free (rubirc_plugin *ph,
	    void *ptr);

int
rubirc_pluginpref_set_str (rubirc_plugin *ph,
		const char *var,
		const char *value);

int
rubirc_pluginpref_get_str (rubirc_plugin *ph,
		const char *var,
		char *dest);

int
rubirc_pluginpref_set_int (rubirc_plugin *ph,
		const char *var,
		int value);
int
rubirc_pluginpref_get_int (rubirc_plugin *ph,
		const char *var);

int
rubirc_pluginpref_delete (rubirc_plugin *ph,
		const char *var);

int
rubirc_pluginpref_list (rubirc_plugin *ph,
		char *dest);

#if !defined(PLUGIN_C) && (defined(WIN32) || defined(__CYGWIN__))
#ifndef RUBIRC_PLUGIN_HANDLE
#define RUBIRC_PLUGIN_HANDLE (ph)
#endif
#define rubirc_hook_command ((RUBIRC_PLUGIN_HANDLE)->rubirc_hook_command)
#define rubirc_event_attrs_create ((RUBIRC_PLUGIN_HANDLE)->rubirc_event_attrs_create)
#define rubirc_event_attrs_free ((RUBIRC_PLUGIN_HANDLE)->rubirc_event_attrs_free)
#define rubirc_hook_server ((RUBIRC_PLUGIN_HANDLE)->rubirc_hook_server)
#define rubirc_hook_server_attrs ((RUBIRC_PLUGIN_HANDLE)->rubirc_hook_server_attrs)
#define rubirc_hook_print ((RUBIRC_PLUGIN_HANDLE)->rubirc_hook_print)
#define rubirc_hook_print_attrs ((RUBIRC_PLUGIN_HANDLE)->rubirc_hook_print_attrs)
#define rubirc_hook_timer ((RUBIRC_PLUGIN_HANDLE)->rubirc_hook_timer)
#define rubirc_hook_fd ((RUBIRC_PLUGIN_HANDLE)->rubirc_hook_fd)
#define rubirc_unhook ((RUBIRC_PLUGIN_HANDLE)->rubirc_unhook)
#define rubirc_print ((RUBIRC_PLUGIN_HANDLE)->rubirc_print)
#define rubirc_printf ((RUBIRC_PLUGIN_HANDLE)->rubirc_printf)
#define rubirc_command ((RUBIRC_PLUGIN_HANDLE)->rubirc_command)
#define rubirc_commandf ((RUBIRC_PLUGIN_HANDLE)->rubirc_commandf)
#define rubirc_nickcmp ((RUBIRC_PLUGIN_HANDLE)->rubirc_nickcmp)
#define rubirc_set_context ((RUBIRC_PLUGIN_HANDLE)->rubirc_set_context)
#define rubirc_find_context ((RUBIRC_PLUGIN_HANDLE)->rubirc_find_context)
#define rubirc_get_context ((RUBIRC_PLUGIN_HANDLE)->rubirc_get_context)
#define rubirc_get_info ((RUBIRC_PLUGIN_HANDLE)->rubirc_get_info)
#define rubirc_get_prefs ((RUBIRC_PLUGIN_HANDLE)->rubirc_get_prefs)
#define rubirc_list_get ((RUBIRC_PLUGIN_HANDLE)->rubirc_list_get)
#define rubirc_list_free ((RUBIRC_PLUGIN_HANDLE)->rubirc_list_free)
#define rubirc_list_fields ((RUBIRC_PLUGIN_HANDLE)->rubirc_list_fields)
#define rubirc_list_next ((RUBIRC_PLUGIN_HANDLE)->rubirc_list_next)
#define rubirc_list_str ((RUBIRC_PLUGIN_HANDLE)->rubirc_list_str)
#define rubirc_list_int ((RUBIRC_PLUGIN_HANDLE)->rubirc_list_int)
#define rubirc_plugingui_add ((RUBIRC_PLUGIN_HANDLE)->rubirc_plugingui_add)
#define rubirc_plugingui_remove ((RUBIRC_PLUGIN_HANDLE)->rubirc_plugingui_remove)
#define rubirc_emit_print ((RUBIRC_PLUGIN_HANDLE)->rubirc_emit_print)
#define rubirc_emit_print_attrs ((RUBIRC_PLUGIN_HANDLE)->rubirc_emit_print_attrs)
#define rubirc_list_time ((RUBIRC_PLUGIN_HANDLE)->rubirc_list_time)
#define rubirc_gettext ((RUBIRC_PLUGIN_HANDLE)->rubirc_gettext)
#define rubirc_send_modes ((RUBIRC_PLUGIN_HANDLE)->rubirc_send_modes)
#define rubirc_strip ((RUBIRC_PLUGIN_HANDLE)->rubirc_strip)
#define rubirc_free ((RUBIRC_PLUGIN_HANDLE)->rubirc_free)
#define rubirc_pluginpref_set_str ((RUBIRC_PLUGIN_HANDLE)->rubirc_pluginpref_set_str)
#define rubirc_pluginpref_get_str ((RUBIRC_PLUGIN_HANDLE)->rubirc_pluginpref_get_str)
#define rubirc_pluginpref_set_int ((RUBIRC_PLUGIN_HANDLE)->rubirc_pluginpref_set_int)
#define rubirc_pluginpref_get_int ((RUBIRC_PLUGIN_HANDLE)->rubirc_pluginpref_get_int)
#define rubirc_pluginpref_delete ((RUBIRC_PLUGIN_HANDLE)->rubirc_pluginpref_delete)
#define rubirc_pluginpref_list ((RUBIRC_PLUGIN_HANDLE)->rubirc_pluginpref_list)
#endif

#ifdef __cplusplus
}
#endif
#endif
