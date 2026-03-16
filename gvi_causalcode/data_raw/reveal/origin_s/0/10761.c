TSMatcherLine TSMatcherLineCreate ( void ) {
 return reinterpret_cast < TSMatcherLine > ( ats_malloc ( sizeof ( matcher_line ) ) ) ;
 }