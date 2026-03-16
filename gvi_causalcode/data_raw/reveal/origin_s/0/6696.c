CURLcode Curl_getformdata ( struct SessionHandle * data , struct FormData * * finalform , struct curl_httppost * post , const char * custom_content_type , curl_off_t * sizep ) {
 struct FormData * form = NULL ;
 struct FormData * firstform ;
 struct curl_httppost * file ;
 CURLcode result = CURLE_OK ;
 curl_off_t size = 0 ;
 char * boundary ;
 char * fileboundary = NULL ;
 struct curl_slist * curList ;
 * finalform = NULL ;
 if ( ! post ) return result ;
 boundary = formboundary ( data ) ;
 if ( ! boundary ) return CURLE_OUT_OF_MEMORY ;
 result = AddFormDataf ( & form , NULL , "%s;
 boundary=%s\r\n" , custom_content_type ? custom_content_type : "Content-Type: multipart/form-data" , boundary ) ;
 if ( result ) {
 Curl_safefree ( boundary ) ;
 return result ;
 }
 firstform = form ;
 do {
 if ( size ) {
 result = AddFormDataf ( & form , & size , "\r\n" ) ;
 if ( result ) break ;
 }
 result = AddFormDataf ( & form , & size , "--%s\r\n" , boundary ) ;
 if ( result ) break ;
 result = AddFormDataf ( & form , & size , "Content-Disposition: form-data;
 name=\"" ) ;
 if ( result ) break ;
 result = AddFormData ( & form , FORM_DATA , post -> name , post -> namelength , & size ) ;
 if ( result ) break ;
 result = AddFormDataf ( & form , & size , "\"" ) ;
 if ( result ) break ;
 if ( post -> more ) {
 Curl_safefree ( fileboundary ) ;
 fileboundary = formboundary ( data ) ;
 if ( ! fileboundary ) {
 result = CURLE_OUT_OF_MEMORY ;
 break ;
 }
 result = AddFormDataf ( & form , & size , "\r\nContent-Type: multipart/mixed;
" " boundary=%s\r\n" , fileboundary ) ;
 if ( result ) break ;
 }
 file = post ;
 do {
 if ( post -> more ) {
 result = AddFormDataf ( & form , & size , "\r\n--%s\r\nContent-Disposition: " "attachment" , fileboundary ) ;
 if ( result ) break ;
 result = formdata_add_filename ( file , & form , & size ) ;
 if ( result ) break ;
 }
 else if ( post -> flags & ( HTTPPOST_FILENAME | HTTPPOST_BUFFER | HTTPPOST_CALLBACK ) ) {
 if ( post -> showfilename || ( post -> flags & HTTPPOST_FILENAME ) ) {
 result = formdata_add_filename ( post , & form , & size ) ;
 }
 if ( result ) break ;
 }
 if ( file -> contenttype ) {
 result = AddFormDataf ( & form , & size , "\r\nContent-Type: %s" , file -> contenttype ) ;
 if ( result ) break ;
 }
 curList = file -> contentheader ;
 while ( curList ) {
 result = AddFormDataf ( & form , & size , "\r\n%s" , curList -> data ) ;
 if ( result ) break ;
 curList = curList -> next ;
 }
 if ( result ) break ;
 result = AddFormDataf ( & form , & size , "\r\n\r\n" ) ;
 if ( result ) break ;
 if ( ( post -> flags & HTTPPOST_FILENAME ) || ( post -> flags & HTTPPOST_READFILE ) ) {
 FILE * fileread ;
 fileread = strequal ( "-" , file -> contents ) ? stdin : fopen ( file -> contents , "rb" ) ;
 if ( fileread ) {
 if ( fileread != stdin ) {
 fclose ( fileread ) ;
 result = AddFormData ( & form , FORM_FILE , file -> contents , 0 , & size ) ;
 }
 else {
 size_t nread ;
 char buffer [ 512 ] ;
 while ( ( nread = fread ( buffer , 1 , sizeof ( buffer ) , fileread ) ) != 0 ) {
 result = AddFormData ( & form , FORM_CONTENT , buffer , nread , & size ) ;
 if ( result ) break ;
 }
 }
 }
 else {
 if ( data ) failf ( data , "couldn't open file \"%s\"" , file -> contents ) ;
 * finalform = NULL ;
 result = CURLE_READ_ERROR ;
 }
 }
 else if ( post -> flags & HTTPPOST_BUFFER ) result = AddFormData ( & form , FORM_CONTENT , post -> buffer , post -> bufferlength , & size ) ;
 else if ( post -> flags & HTTPPOST_CALLBACK ) result = AddFormData ( & form , FORM_CALLBACK , post -> userp , post -> contentslength , & size ) ;
 else result = AddFormData ( & form , FORM_CONTENT , post -> contents , post -> contentslength , & size ) ;
 file = file -> more ;
 }
 while ( file && ! result ) ;
 if ( result ) break ;
 if ( post -> more ) {
 result = AddFormDataf ( & form , & size , "\r\n--%s--" , fileboundary ) ;
 if ( result ) break ;
 }
 }
 while ( ( post = post -> next ) != NULL ) ;
 if ( ! result ) result = AddFormDataf ( & form , & size , "\r\n--%s--\r\n" , boundary ) ;
 if ( result ) {
 Curl_formclean ( & firstform ) ;
 Curl_safefree ( fileboundary ) ;
 Curl_safefree ( boundary ) ;
 return result ;
 }
 * sizep = size ;
 Curl_safefree ( fileboundary ) ;
 Curl_safefree ( boundary ) ;
 * finalform = firstform ;
 return result ;
 }