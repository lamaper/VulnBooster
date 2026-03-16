static void process_envvars ( enum mode * modep ) {
 char * * runp = _environ ;
 char * envline ;
 enum mode mode = normal ;
 char * debug_output = NULL ;
 GLRO ( dl_profile_output ) = & "/var/tmp\0/var/profile" [ __libc_enable_secure ? 9 : 0 ] ;
 while ( ( envline = _dl_next_ld_env_entry ( & runp ) ) != NULL ) {
 size_t len = 0 ;
 while ( envline [ len ] != '\0' && envline [ len ] != '=' ) ++ len ;
 if ( envline [ len ] != '=' ) continue ;
 switch ( len ) {
 case 4 : if ( memcmp ( envline , "WARN" , 4 ) == 0 ) GLRO ( dl_verbose ) = envline [ 5 ] != '\0' ;
 break ;
 case 5 : if ( memcmp ( envline , "DEBUG" , 5 ) == 0 ) {
 process_dl_debug ( & envline [ 6 ] ) ;
 break ;
 }
 if ( memcmp ( envline , "AUDIT" , 5 ) == 0 ) process_dl_audit ( & envline [ 6 ] ) ;
 break ;
 case 7 : if ( memcmp ( envline , "VERBOSE" , 7 ) == 0 ) {
 version_info = envline [ 8 ] != '\0' ;
 break ;
 }
 if ( memcmp ( envline , "PRELOAD" , 7 ) == 0 ) {
 preloadlist = & envline [ 8 ] ;
 break ;
 }
 if ( memcmp ( envline , "PROFILE" , 7 ) == 0 && envline [ 8 ] != '\0' ) GLRO ( dl_profile ) = & envline [ 8 ] ;
 break ;
 case 8 : if ( memcmp ( envline , "BIND_NOW" , 8 ) == 0 ) {
 GLRO ( dl_lazy ) = envline [ 9 ] == '\0' ;
 break ;
 }
 if ( memcmp ( envline , "BIND_NOT" , 8 ) == 0 ) GLRO ( dl_bind_not ) = envline [ 9 ] != '\0' ;
 break ;
 case 9 : if ( ! __libc_enable_secure && memcmp ( envline , "SHOW_AUXV" , 9 ) == 0 ) _dl_show_auxv ( ) ;
 break ;
 case 10 : if ( memcmp ( envline , "HWCAP_MASK" , 10 ) == 0 ) GLRO ( dl_hwcap_mask ) = __strtoul_internal ( & envline [ 11 ] , NULL , 0 , 0 ) ;
 break ;
 case 11 : if ( ! __libc_enable_secure && memcmp ( envline , "ORIGIN_PATH" , 11 ) == 0 ) GLRO ( dl_origin_path ) = & envline [ 12 ] ;
 break ;
 case 12 : if ( memcmp ( envline , "LIBRARY_PATH" , 12 ) == 0 ) {
 library_path = & envline [ 13 ] ;
 break ;
 }
 if ( memcmp ( envline , "DEBUG_OUTPUT" , 12 ) == 0 ) {
 debug_output = & envline [ 13 ] ;
 break ;
 }
 if ( ! __libc_enable_secure && memcmp ( envline , "DYNAMIC_WEAK" , 12 ) == 0 ) GLRO ( dl_dynamic_weak ) = 1 ;
 break ;
 case 13 : # ifdef EXTRA_LD_ENVVARS_13 EXTRA_LD_ENVVARS_13 # endif if ( ! __libc_enable_secure && memcmp ( envline , "USE_LOAD_BIAS" , 13 ) == 0 ) {
 GLRO ( dl_use_load_bias ) = envline [ 14 ] == '1' ? - 1 : 0 ;
 break ;
 }
 if ( memcmp ( envline , "POINTER_GUARD" , 13 ) == 0 ) GLRO ( dl_pointer_guard ) = envline [ 14 ] != '0' ;
 break ;
 case 14 : if ( ! __libc_enable_secure && memcmp ( envline , "PROFILE_OUTPUT" , 14 ) == 0 && envline [ 15 ] != '\0' ) GLRO ( dl_profile_output ) = & envline [ 15 ] ;
 break ;
 case 16 : if ( memcmp ( envline , "TRACE_PRELINKING" , 16 ) == 0 ) {
 mode = trace ;
 GLRO ( dl_verbose ) = 1 ;
 GLRO ( dl_debug_mask ) |= DL_DEBUG_PRELINK ;
 GLRO ( dl_trace_prelink ) = & envline [ 17 ] ;
 }
 break ;
 case 20 : if ( memcmp ( envline , "TRACE_LOADED_OBJECTS" , 20 ) == 0 ) mode = trace ;
 break ;

 }
 * modep = mode ;
 if ( __builtin_expect ( __libc_enable_secure , 0 ) ) {
 static const char unsecure_envvars [ ] = # ifdef EXTRA_UNSECURE_ENVVARS EXTRA_UNSECURE_ENVVARS # endif UNSECURE_ENVVARS ;
 const char * nextp ;
 nextp = unsecure_envvars ;
 do {
 unsetenv ( nextp ) ;
 nextp = ( char * ) ( strchr ) ( nextp , '\0' ) + 1 ;
 }
 while ( * nextp != '\0' ) ;
 if ( __access ( "/etc/suid-debug" , F_OK ) != 0 ) {
 unsetenv ( "MALLOC_CHECK_" ) ;
 GLRO ( dl_debug_mask ) = 0 ;
 }
 if ( mode != normal ) _exit ( 5 ) ;
 }
 else if ( any_debug && debug_output != NULL ) {



 char buf [ name_len + 12 ] ;
 char * startp ;
 buf [ name_len + 11 ] = '\0' ;
 startp = _itoa ( __getpid ( ) , & buf [ name_len + 11 ] , 10 , 0 ) ;
 * -- startp = '.' ;
 startp = memcpy ( startp - name_len , debug_output , name_len ) ;
 GLRO ( dl_debug_fd ) = __open ( startp , flags , DEFFILEMODE ) ;
 if ( GLRO ( dl_debug_fd ) == - 1 ) GLRO ( dl_debug_fd ) = STDOUT_FILENO ;
 }
 }