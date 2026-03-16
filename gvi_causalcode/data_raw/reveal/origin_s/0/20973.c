void free_re ( void ) {
 my_regfree ( & ps_re ) ;
 my_regfree ( & sp_re ) ;
 my_regfree ( & view_re ) ;
 my_regex_end ( ) ;
 }