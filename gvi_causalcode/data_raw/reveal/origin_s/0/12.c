int keyring_register_filename ( const char * fname , int read_only , void * * ptr ) {
 KR_NAME kr ;
 if ( active_handles ) BUG ( ) ;
 for ( kr = kr_names ;
 kr ;
 kr = kr -> next ) {
 if ( same_file_p ( kr -> fname , fname ) ) {
 if ( read_only ) kr -> read_only = 1 ;
 * ptr = kr ;
 return 0 ;
 }
 }
 kr = xmalloc ( sizeof * kr + strlen ( fname ) ) ;
 strcpy ( kr -> fname , fname ) ;
 kr -> read_only = read_only ;
 kr -> lockhd = NULL ;
 kr -> is_locked = 0 ;
 kr -> did_full_scan = 0 ;
 kr -> next = kr_names ;
 kr_names = kr ;
 if ( ! kr_offtbl ) kr_offtbl = new_offset_hash_table ( ) ;
 * ptr = kr ;
 return 1 ;
 }