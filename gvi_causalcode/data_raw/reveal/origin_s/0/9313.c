static kadm5_ret_t copy_tl_data ( krb5_int16 n_tl_data , krb5_tl_data * tl_data , krb5_tl_data * * out ) {
 kadm5_ret_t ret ;
 krb5_tl_data * tl , * tl_new ;
 if ( ( ret = alloc_tl_data ( n_tl_data , out ) ) ) return ret ;
 tl = tl_data ;
 tl_new = * out ;
 for ( ;
 tl ;
 tl = tl -> tl_data_next , tl_new = tl_new -> tl_data_next ) {
 tl_new -> tl_data_contents = malloc ( tl -> tl_data_length ) ;
 if ( tl_new -> tl_data_contents == NULL ) return ENOMEM ;
 memcpy ( tl_new -> tl_data_contents , tl -> tl_data_contents , tl -> tl_data_length ) ;
 tl_new -> tl_data_type = tl -> tl_data_type ;
 tl_new -> tl_data_length = tl -> tl_data_length ;
 }
 return 0 ;
 }