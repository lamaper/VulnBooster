const char * TSUrlHttpParamsGet ( TSMBuffer bufp , TSMLoc obj , int * length ) {
 return URLPartGet ( bufp , obj , length , & URL : : params_get ) ;
 }