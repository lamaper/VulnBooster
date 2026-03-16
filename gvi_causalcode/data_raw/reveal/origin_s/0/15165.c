int ntpqmain ( int argc , char * argv [ ] ) {
 u_int ihost ;
 int icmd ;

 taskPrioritySet ( taskIdSelf ( ) , 100 ) ;

 delay_time . l_uf = DEFDELAY ;
 init_lib ( ) ;
 ssl_applink ( ) ;
 init_auth ( ) ;
 if ( ! ipv6_works ) ai_fam_default = AF_INET ;
 {
 char * list ;
 char * msg , * fmt ;
 list = list_digest_names ( ) ;
 for ( icmd = 0 ;
 icmd < sizeof ( builtins ) / sizeof ( builtins [ 0 ] ) ;
 icmd ++ ) {
 if ( strcmp ( "keytype" , builtins [ icmd ] . keyword ) == 0 ) break ;
 }
 INSIST ( icmd < sizeof ( builtins ) / sizeof ( builtins [ 0 ] ) ) ;

 fmt = "set key type to use for authenticated requests, one of:%s" ;

 fmt = "set key type to use for authenticated requests (%s)" ;

 sprintf ( msg , fmt , list ) ;
 builtins [ icmd ] . comment = msg ;
 free ( list ) ;
 }
 progname = argv [ 0 ] ;
 {
 int optct = ntpOptionProcess ( & ntpqOptions , argc , argv ) ;
 argc -= optct ;
 argv += optct ;
 }
 debug = OPT_VALUE_SET_DEBUG_LEVEL ;
 if ( HAVE_OPT ( IPV4 ) ) ai_fam_templ = AF_INET ;
 else if ( HAVE_OPT ( IPV6 ) ) ai_fam_templ = AF_INET6 ;
 else ai_fam_templ = ai_fam_default ;
 if ( HAVE_OPT ( INTERACTIVE ) ) interactive = 1 ;
 if ( HAVE_OPT ( NUMERIC ) ) showhostnames = 0 ;
 if ( HAVE_OPT ( WIDE ) ) wideremote = 1 ;
 old_rv = HAVE_OPT ( OLD_RV ) ;
 if ( 0 == argc ) {
 ADDHOST ( DEFHOST ) ;
 }
 else {
 for ( ihost = 0 ;
 ihost < ( u_int ) argc ;
 ihost ++ ) {
 if ( '-' == * argv [ ihost ] ) {
 if ( '4' == argv [ ihost ] [ 1 ] ) {
 ai_fam_templ = AF_INET ;
 continue ;
 }
 else if ( '6' == argv [ ihost ] [ 1 ] ) {
 ai_fam_templ = AF_INET6 ;
 continue ;
 }
 else {
 }
 }
 ADDHOST ( argv [ ihost ] ) ;
 }
 }
 if ( numcmds == 0 && interactive == 0 && isatty ( fileno ( stdin ) ) && isatty ( fileno ( stderr ) ) ) {
 interactive = 1 ;
 }


 ( void ) openhost ( chosts [ 0 ] . name , chosts [ 0 ] . fam ) ;
 getcmds ( ) ;
 }
 else {
 for ( ihost = 0 ;
 ihost < numhosts ;
 ihost ++ ) {
 if ( openhost ( chosts [ ihost ] . name , chosts [ ihost ] . fam ) ) for ( icmd = 0 ;
 icmd < numcmds ;
 icmd ++ ) docmd ( ccmds [ icmd ] ) ;
 }
 }


 }