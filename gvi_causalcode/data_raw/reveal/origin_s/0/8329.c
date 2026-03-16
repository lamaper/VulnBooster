static int alloc_tl_data ( krb5_int16 n_tl_data , krb5_tl_data * * tldp ) {
 krb5_tl_data * * tlp = tldp ;
 int i ;
 for ( i = 0 ;
 i < n_tl_data ;
 i ++ ) {
 * tlp = calloc ( 1 , sizeof ( krb5_tl_data ) ) ;
 if ( * tlp == NULL ) return ENOMEM ;
 memset ( * tlp , 0 , sizeof ( krb5_tl_data ) ) ;
 tlp = & ( ( * tlp ) -> tl_data_next ) ;
 }
 return 0 ;
 }