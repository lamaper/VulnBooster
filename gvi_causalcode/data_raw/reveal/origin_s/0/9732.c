static FILE * dumpcffstrings ( struct pschars * strs ) {
 FILE * file = tmpfile ( ) ;
 _dumpcffstrings ( file , strs ) ;
 PSCharsFree ( strs ) ;
 return ( file ) ;
 }