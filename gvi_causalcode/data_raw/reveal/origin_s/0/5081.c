TSReturnCode TSUrlHostSet ( TSMBuffer bufp , TSMLoc obj , const char * value , int length ) {
 return URLPartSet ( bufp , obj , value , length , & URL : : host_set ) ;
 }