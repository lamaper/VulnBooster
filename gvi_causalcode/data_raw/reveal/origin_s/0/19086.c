const char * TSUrlHttpQueryGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 return URLPartGet ( bufp , obj , length , & URL : : query_get ) ;
 }