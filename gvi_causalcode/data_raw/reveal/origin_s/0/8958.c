TSReturnCode TSUrlHttpFragmentSet ( TSMBuffer bufp , TSMLoc obj , const char * value , int length ) {
 return URLPartSet ( bufp , obj , value , length , & URL : : fragment_set ) ;
 }