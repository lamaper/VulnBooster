static CURLcode formdata_add_filename ( const struct curl_httppost * file , struct FormData * * form , curl_off_t * size ) {
 CURLcode result = CURLE_OK ;
 char * filename = file -> showfilename ;
 char * filebasename = NULL ;
 char * filename_escaped = NULL ;
 if ( ! filename ) {
 filebasename = strippath ( file -> contents ) ;
 if ( ! filebasename ) return CURLE_OUT_OF_MEMORY ;
 filename = filebasename ;
 }
 if ( strchr ( filename , '\\' ) || strchr ( filename , '"' ) ) {
 char * p0 , * p1 ;
 filename_escaped = malloc ( strlen ( filename ) * 2 + 1 ) ;
 if ( ! filename_escaped ) {
 Curl_safefree ( filebasename ) ;
 return CURLE_OUT_OF_MEMORY ;
 }
 p0 = filename_escaped ;
 p1 = filename ;
 while ( * p1 ) {
 if ( * p1 == '\\' || * p1 == '"' ) * p0 ++ = '\\' ;
 * p0 ++ = * p1 ++ ;
 }
 * p0 = '\0' ;
 filename = filename_escaped ;
 }
 result = AddFormDataf ( form , size , ";
 filename=\"%s\"" , filename ) ;
 Curl_safefree ( filename_escaped ) ;
 Curl_safefree ( filebasename ) ;
 return result ;
 }