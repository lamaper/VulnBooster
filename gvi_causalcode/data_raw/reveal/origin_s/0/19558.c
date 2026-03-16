static void read_settings ( void ) {
 keep_privates_count = settings_get_int ( "completion_keep_privates" ) ;
 keep_publics_count = settings_get_int ( "completion_keep_publics" ) ;
 completion_lowercase = settings_get_bool ( "completion_nicks_lowercase" ) ;
 completion_auto = settings_get_bool ( "completion_auto" ) ;
 completion_strict = settings_get_bool ( "completion_strict" ) ;
 completion_empty_line = settings_get_bool ( "completion_empty_line" ) ;
 completion_match_case = settings_get_choice ( "completion_nicks_match_case" ) ;
 g_free_not_null ( completion_char ) ;
 completion_char = g_strdup ( settings_get_str ( "completion_char" ) ) ;
 g_free_not_null ( cmdchars ) ;
 cmdchars = g_strdup ( settings_get_str ( "cmdchars" ) ) ;
 if ( * completion_char == '\0' ) {
 completion_auto = FALSE ;
 }
 }