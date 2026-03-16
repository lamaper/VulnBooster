ssize_t ___strfmon_l ( char * s , size_t maxsize , __locale_t loc , const char * format , ... ) {
 va_list ap ;
 va_start ( ap , format ) ;
 ssize_t res = __vstrfmon_l ( s , maxsize , loc , format , ap ) ;
 va_end ( ap ) ;
 return res ;
 }