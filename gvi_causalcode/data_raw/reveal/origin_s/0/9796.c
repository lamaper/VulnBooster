const char * TSUrlUserGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 return URLPartGet ( bufp , obj , length , & URL : : user_get ) ;
 }