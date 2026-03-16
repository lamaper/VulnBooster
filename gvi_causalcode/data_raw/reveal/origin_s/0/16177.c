static CURLcode AddFormDataf ( struct FormData * * formp , curl_off_t * size , const char * fmt , ... ) {
 char s [ 4096 ] ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 vsnprintf ( s , sizeof ( s ) , fmt , ap ) ;
 va_end ( ap ) ;
 return AddFormData ( formp , FORM_DATA , s , 0 , size ) ;
 }