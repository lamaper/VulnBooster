static void docmd ( const char * cmdline ) {
 char * tokens [ 1 + MAXARGS + 2 ] ;
 struct parse pcmd ;
 int ntok ;
 static int i ;
 struct xcmd * xcmd ;
 tokenize ( cmdline , tokens , & ntok ) ;
 if ( ntok == 0 ) return ;
 i = findcmd ( tokens [ 0 ] , builtins , opcmds , & xcmd ) ;
 if ( i == 0 ) {
 ( void ) fprintf ( stderr , "***Command `%s' unknown\n" , tokens [ 0 ] ) ;
 return ;
 }
 else if ( i >= 2 ) {
 ( void ) fprintf ( stderr , "***Command `%s' ambiguous\n" , tokens [ 0 ] ) ;
 return ;
 }
 for ( i = MAXARGS + 1 ;
 i < ntok ;
 ++ i ) {
 fprintf ( stderr , "***Extra arg `%s' ignored\n" , tokens [ i ] ) ;
 }
 pcmd . keyword = tokens [ 0 ] ;
 pcmd . nargs = 0 ;
 for ( i = 0 ;
 i < MAXARGS && xcmd -> arg [ i ] != NO ;
 i ++ ) {
 if ( ( i + 1 ) >= ntok ) {
 if ( ! ( xcmd -> arg [ i ] & OPT ) ) {
 printusage ( xcmd , stderr ) ;
 return ;
 }
 break ;
 }
 if ( ( xcmd -> arg [ i ] & OPT ) && ( * tokens [ i + 1 ] == '>' ) ) break ;
 if ( ! getarg ( tokens [ i + 1 ] , ( int ) xcmd -> arg [ i ] , & pcmd . argval [ i ] ) ) return ;
 pcmd . nargs ++ ;
 }
 i ++ ;
 if ( i < ntok && * tokens [ i ] == '>' ) {
 char * fname ;
 if ( * ( tokens [ i ] + 1 ) != '\0' ) fname = tokens [ i ] + 1 ;
 else if ( ( i + 1 ) < ntok ) fname = tokens [ i + 1 ] ;
 else {
 ( void ) fprintf ( stderr , "***No file for redirect\n" ) ;
 return ;
 }
 current_output = fopen ( fname , "w" ) ;
 if ( current_output == NULL ) {
 ( void ) fprintf ( stderr , "***Error opening %s: " , fname ) ;
 perror ( "" ) ;
 return ;
 }
 i = 1 ;
 }
 else {
 current_output = stdout ;
 i = 0 ;
 }
 if ( interactive && setjmp ( interrupt_buf ) ) {
 jump = 0 ;
 return ;
 }
 else {
 jump ++ ;
 ( xcmd -> handler ) ( & pcmd , current_output ) ;
 jump = 0 ;
 if ( i ) ( void ) fclose ( current_output ) ;
 }
 return ;
 }