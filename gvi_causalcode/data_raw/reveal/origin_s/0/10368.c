static void HtmlNPut ( char * * ppsz_html , const char * psz_text , int i_max ) {
 char * psz_html = * ppsz_html ;
 if ( psz_html == NULL ) return ;
 const size_t i_offset = strlen ( psz_html ) ;
 const size_t i_len = strnlen ( psz_text , i_max ) ;
 psz_html = realloc ( psz_html , i_offset + i_len + 1 ) ;
 if ( psz_html != NULL ) {
 memcpy ( psz_html + i_offset , psz_text , i_len ) ;
 psz_html [ i_offset + i_len ] = '\0' ;
 }
 else free ( * ppsz_html ) ;
 * ppsz_html = psz_html ;
 }