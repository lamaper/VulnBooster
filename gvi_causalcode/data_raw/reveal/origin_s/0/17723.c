static void kadmin_free_tl_data ( krb5_int16 * n_tl_datap , krb5_tl_data * * tl_datap ) {
 krb5_tl_data * tl_data = * tl_datap , * next ;
 int n_tl_data = * n_tl_datap ;
 int i ;
 * n_tl_datap = 0 ;
 * tl_datap = NULL ;
 for ( i = 0 ;
 tl_data && ( i < n_tl_data ) ;
 i ++ ) {
 next = tl_data -> tl_data_next ;
 free ( tl_data -> tl_data_contents ) ;
 free ( tl_data ) ;
 tl_data = next ;
 }
 }