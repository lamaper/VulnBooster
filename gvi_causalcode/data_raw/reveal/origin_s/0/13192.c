static size_t wrap_fwrite ( const void * ptr , size_t size , size_t nmemb , FILE * stream ) {
 return fwrite ( ptr , size , nmemb , stream ) ;
 }