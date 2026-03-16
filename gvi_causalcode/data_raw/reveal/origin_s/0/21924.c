static void add_tl_data ( krb5_int16 * n_tl_datap , krb5_tl_data * * tl_datap , krb5_int16 tl_type , krb5_ui_2 len , krb5_octet * contents ) {
 krb5_tl_data * tl_data ;
 krb5_octet * copy ;
 copy = malloc ( len ) ;
 tl_data = calloc ( 1 , sizeof ( * tl_data ) ) ;
 if ( copy == NULL || tl_data == NULL ) {
 fprintf ( stderr , _ ( "Not enough memory\n" ) ) ;
 exit ( 1 ) ;
 }
 memcpy ( copy , contents , len ) ;
 tl_data -> tl_data_type = tl_type ;
 tl_data -> tl_data_length = len ;
 tl_data -> tl_data_contents = copy ;
 tl_data -> tl_data_next = NULL ;
 for ( ;
 * tl_datap != NULL ;
 tl_datap = & ( * tl_datap ) -> tl_data_next ) ;
 * tl_datap = tl_data ;
 ( * n_tl_datap ) ++ ;
 }