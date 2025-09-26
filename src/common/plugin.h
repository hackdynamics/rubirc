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

#ifndef RUBIRC_COMMONPLUGIN_H
#define RUBIRC_COMMONPLUGIN_H

#ifdef PLUGIN_C
struct _rubirc_plugin
{
	/* Keep these in sync with rubirc-plugin.h */
	/* !!don't change the order, to keep binary compat!! */
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
	      const char *format, ...);
	void (*rubirc_command) (rubirc_plugin *ph,
	       const char *command);
	void (*rubirc_commandf) (rubirc_plugin *ph,
		const char *format, ...);
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
	void *(*rubirc_read_fd) (rubirc_plugin *ph);
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

	/* PRIVATE FIELDS! */
	void *handle;		/* from dlopen */
	char *filename;	/* loaded from */
	char *name;
	char *desc;
	char *version;
	session *context;
	void *deinit_callback;	/* pointer to rubirc_plugin_deinit */
	unsigned int fake:1;		/* fake plugin. Added by rubirc_plugingui_add() */
	unsigned int free_strings:1;		/* free name,desc,version? */
};
#endif

GModule *module_load (char *filename);
char *plugin_load (session *sess, char *filename, char *arg);
int plugin_reload (session *sess, char *name, int by_filename);
void plugin_add (session *sess, char *filename, void *handle, void *init_func, void *deinit_func, char *arg, int fake);
int plugin_kill (char *name, int by_filename);
void plugin_kill_all (void);
void plugin_auto_load (session *sess);
int plugin_emit_command (session *sess, char *name, char *word[], char *word_eol[]);
int plugin_emit_server (session *sess, char *name, char *word[], char *word_eol[],
						time_t server_time);
int plugin_emit_print (session *sess, char *word[], time_t server_time);
int plugin_emit_dummy_print (session *sess, char *name);
int plugin_emit_keypress (session *sess, unsigned int state, unsigned int keyval, gunichar key);
GList* plugin_command_list(GList *tmp_list);
int plugin_show_help (session *sess, char *cmd);
void plugin_command_foreach (session *sess, void *userdata, void (*cb) (session *sess, void *userdata, char *name, char *usage));
session *plugin_find_context (const char *servname, const char *channel, server *current_server);

/* On macOS, G_MODULE_SUFFIX says "so" but meson uses "dylib"
 * https://github.com/mesonbuild/meson/issues/1160 */
#if defined(__APPLE__)
#  define PLUGIN_SUFFIX "dylib"
#else
#  define PLUGIN_SUFFIX G_MODULE_SUFFIX
#endif

#endif
