const char * TSUrlSchemeGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 return URLPartGet ( bufp , obj , length , & URL : : scheme_get ) ;
 }