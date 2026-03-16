static void add_sconv_object ( struct archive * a , struct archive_string_conv * sc ) {
 struct archive_string_conv * * psc ;
 psc = & ( a -> sconv ) ;
 while ( * psc != NULL ) psc = & ( ( * psc ) -> next ) ;
 * psc = sc ;
 }