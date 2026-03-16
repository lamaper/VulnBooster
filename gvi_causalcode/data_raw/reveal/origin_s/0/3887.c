bool virLogProbablyLogMessage ( const char * str ) {
 bool ret = false ;
 if ( ! virLogRegex ) return false ;
 if ( regexec ( virLogRegex , str , 0 , NULL , 0 ) == 0 ) ret = true ;
 return ret ;
 }