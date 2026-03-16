static void process_dl_debug ( const char * dl_debug ) {
 static const struct {
 unsigned char len ;
 const char name [ 10 ] ;
 const char helptext [ 41 ] ;
 unsigned short int mask ;
 }
 debopts [ ] = {

 LEN_AND_STR ( "libs" ) , "display library search paths" , DL_DEBUG_LIBS | DL_DEBUG_IMPCALLS }
 , {
 LEN_AND_STR ( "reloc" ) , "display relocation processing" , DL_DEBUG_RELOC | DL_DEBUG_IMPCALLS }
 , {
 LEN_AND_STR ( "files" ) , "display progress for input file" , DL_DEBUG_FILES | DL_DEBUG_IMPCALLS }
 , {
 LEN_AND_STR ( "symbols" ) , "display symbol table processing" , DL_DEBUG_SYMBOLS | DL_DEBUG_IMPCALLS }
 , {
 LEN_AND_STR ( "bindings" ) , "display information about symbol binding" , DL_DEBUG_BINDINGS | DL_DEBUG_IMPCALLS }
 , {
 LEN_AND_STR ( "versions" ) , "display version dependencies" , DL_DEBUG_VERSIONS | DL_DEBUG_IMPCALLS }
 , {
 LEN_AND_STR ( "scopes" ) , "display scope information" , DL_DEBUG_SCOPES }
 , {
 LEN_AND_STR ( "all" ) , "all previous options combined" , DL_DEBUG_LIBS | DL_DEBUG_RELOC | DL_DEBUG_FILES | DL_DEBUG_SYMBOLS | DL_DEBUG_BINDINGS | DL_DEBUG_VERSIONS | DL_DEBUG_IMPCALLS | DL_DEBUG_SCOPES }
 , {
 LEN_AND_STR ( "statistics" ) , "display relocation statistics" , DL_DEBUG_STATISTICS }
 , {
 LEN_AND_STR ( "unused" ) , "determined unused DSOs" , DL_DEBUG_UNUSED }
 , {
 LEN_AND_STR ( "help" ) , "display this help message and exit" , DL_DEBUG_HELP }
 , }
 ;

 if ( * dl_debug != ' ' && * dl_debug != ',' && * dl_debug != ':' ) {
 size_t cnt ;
 size_t len = 1 ;
 while ( dl_debug [ len ] != '\0' && dl_debug [ len ] != ' ' && dl_debug [ len ] != ',' && dl_debug [ len ] != ':' ) ++ len ;
 for ( cnt = 0 ;
 cnt < ndebopts ;
 ++ cnt ) if ( debopts [ cnt ] . len == len && memcmp ( dl_debug , debopts [ cnt ] . name , len ) == 0 ) {
 GLRO ( dl_debug_mask ) |= debopts [ cnt ] . mask ;
 any_debug = 1 ;
 break ;
 }
 if ( cnt == ndebopts ) {
 char * copy = strndupa ( dl_debug , len ) ;
 _dl_error_printf ( "\ warning: debug option `%s' unknown;
 try LD_DEBUG=help\n" , copy ) ;
 }
 dl_debug += len ;
 continue ;
 }
 ++ dl_debug ;
 }
 if ( GLRO ( dl_debug_mask ) & DL_DEBUG_UNUSED ) {
 GLRO ( dl_lazy ) = 0 ;
 }
 if ( GLRO ( dl_debug_mask ) & DL_DEBUG_HELP ) {
 size_t cnt ;
 _dl_printf ( "\ Valid options for the LD_DEBUG environment variable are:\n\n" ) ;
 for ( cnt = 0 ;
 cnt < ndebopts ;
 ++ cnt ) _dl_printf ( " %.*s%s%s\n" , debopts [ cnt ] . len , debopts [ cnt ] . name , " " + debopts [ cnt ] . len - 3 , debopts [ cnt ] . helptext ) ;
 _dl_printf ( "\n\ To direct the debugging output into a file instead of standard output\n\ a filename can be specified using the LD_DEBUG_OUTPUT environment variable.\n" ) ;
 _exit ( 0 ) ;
 }
 }