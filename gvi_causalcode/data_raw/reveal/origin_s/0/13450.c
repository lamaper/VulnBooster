void Curl_formclean ( struct FormData * * form_ptr ) {
 struct FormData * next , * form ;
 form = * form_ptr ;
 if ( ! form ) return ;
 do {
 next = form -> next ;
 if ( form -> type <= FORM_CONTENT ) free ( form -> line ) ;
 free ( form ) ;
 }
 while ( ( form = next ) != NULL ) ;
 * form_ptr = NULL ;
 }