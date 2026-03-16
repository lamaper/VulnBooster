static int fts_parser_script_deinit ( struct fts_parser * _parser ) {
 struct script_fts_parser * parser = ( struct script_fts_parser * ) _parser ;
 int ret = parser -> failed ? - 1 : 0 ;
 if ( close ( parser -> fd ) < 0 ) i_error ( "close(%s) failed: %m" , parser -> path ) ;
 i_free ( parser -> path ) ;
 i_free ( parser ) ;
 return ret ;
 }