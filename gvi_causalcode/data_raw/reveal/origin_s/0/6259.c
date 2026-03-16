const char * TSUrlHostGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 return URLPartGet ( bufp , obj , length , & URL : : host_get ) ;
 }