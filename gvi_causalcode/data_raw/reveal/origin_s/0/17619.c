char * irc_ctcp_replace_variables ( struct t_irc_server * server , const char * format ) {
 char * res , * temp , * username , * realname ;
 const char * info ;
 time_t now ;
 struct tm * local_time ;
 char buf [ 1024 ] ;
 struct utsname * buf_uname ;
 temp = weechat_string_replace ( format , "$clientinfo" , "ACTION DCC CLIENTINFO FINGER PING SOURCE TIME USERINFO VERSION" ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 info = weechat_info_get ( "version_git" , "" ) ;
 temp = weechat_string_replace ( res , "$git" , info ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 info = weechat_info_get ( "version_git" , "" ) ;
 snprintf ( buf , sizeof ( buf ) , "%s%s%s%s" , weechat_info_get ( "version" , "" ) , ( info && info [ 0 ] ) ? " (git: " : "" , ( info && info [ 0 ] ) ? info : "" , ( info && info [ 0 ] ) ? ")" : "" ) ;
 temp = weechat_string_replace ( res , "$versiongit" , buf ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 info = weechat_info_get ( "version" , "" ) ;
 temp = weechat_string_replace ( res , "$version" , info ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 info = weechat_info_get ( "date" , "" ) ;
 temp = weechat_string_replace ( res , "$compilation" , info ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 buf_uname = ( struct utsname * ) malloc ( sizeof ( struct utsname ) ) ;
 if ( buf_uname ) {
 if ( uname ( buf_uname ) >= 0 ) {
 snprintf ( buf , sizeof ( buf ) , "%s %s / %s" , buf_uname -> sysname , buf_uname -> release , buf_uname -> machine ) ;
 temp = weechat_string_replace ( res , "$osinfo" , buf ) ;
 free ( res ) ;
 if ( ! temp ) {
 free ( buf_uname ) ;
 return NULL ;
 }
 res = temp ;
 }
 free ( buf_uname ) ;
 }
 info = weechat_info_get ( "weechat_site" , "" ) ;
 temp = weechat_string_replace ( res , "$site" , info ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 info = weechat_info_get ( "weechat_site_download" , "" ) ;
 temp = weechat_string_replace ( res , "$download" , info ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 now = time ( NULL ) ;
 local_time = localtime ( & now ) ;
 setlocale ( LC_ALL , "C" ) ;
 strftime ( buf , sizeof ( buf ) , weechat_config_string ( irc_config_look_ctcp_time_format ) , local_time ) ;
 setlocale ( LC_ALL , "" ) ;
 temp = weechat_string_replace ( res , "$time" , buf ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 username = weechat_string_eval_expression ( IRC_SERVER_OPTION_STRING ( server , IRC_SERVER_OPTION_USERNAME ) , NULL , NULL , NULL ) ;
 if ( username ) {
 temp = weechat_string_replace ( res , "$username" , username ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 free ( username ) ;
 }
 realname = weechat_string_eval_expression ( IRC_SERVER_OPTION_STRING ( server , IRC_SERVER_OPTION_REALNAME ) , NULL , NULL , NULL ) ;
 if ( realname ) {
 temp = weechat_string_replace ( res , "$realname" , realname ) ;
 free ( res ) ;
 if ( ! temp ) return NULL ;
 res = temp ;
 free ( realname ) ;
 }
 return res ;
 }