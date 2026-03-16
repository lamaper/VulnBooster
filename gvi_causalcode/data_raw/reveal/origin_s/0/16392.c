static void HtmlCopy ( char * * ppsz_html , char * * ppsz_subtitle , const char * psz_text ) {
 HtmlPut ( ppsz_html , psz_text ) ;
 * ppsz_subtitle += strlen ( psz_text ) ;
 }