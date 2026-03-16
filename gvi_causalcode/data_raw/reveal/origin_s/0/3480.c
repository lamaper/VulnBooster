const char * TSUrlHttpFragmentGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 return URLPartGet ( bufp , obj , length , & URL : : fragment_get ) ;
 }