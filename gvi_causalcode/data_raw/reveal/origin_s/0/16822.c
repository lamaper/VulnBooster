static size_t wrap_fread ( void * ptr , size_t size , size_t nmemb , FILE * stream ) {
 return fread ( ptr , size , nmemb , stream ) ;
 }