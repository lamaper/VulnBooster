void curl_formfree ( struct curl_httppost * form ) {
 struct curl_httppost * next ;
 if ( ! form ) return ;
 do {
 next = form -> next ;
 if ( form -> more ) curl_formfree ( form -> more ) ;
 if ( ! ( form -> flags & HTTPPOST_PTRNAME ) && form -> name ) free ( form -> name ) ;
 if ( ! ( form -> flags & ( HTTPPOST_PTRCONTENTS | HTTPPOST_BUFFER | HTTPPOST_CALLBACK ) ) && form -> contents ) free ( form -> contents ) ;
 if ( form -> contenttype ) free ( form -> contenttype ) ;
 if ( form -> showfilename ) free ( form -> showfilename ) ;
 free ( form ) ;
 }
 while ( ( form = next ) != NULL ) ;
 }