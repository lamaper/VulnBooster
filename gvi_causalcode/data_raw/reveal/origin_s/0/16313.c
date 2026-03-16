void var_copy ( VAR * dest , VAR * src ) {
 dest -> int_val = src -> int_val ;
 dest -> is_int = src -> is_int ;
 dest -> int_dirty = src -> int_dirty ;
 if ( dest -> alloced_len < src -> alloced_len && ! ( dest -> str_val = dest -> str_val ? ( char * ) my_realloc ( dest -> str_val , src -> alloced_len , MYF ( MY_WME ) ) : ( char * ) my_malloc ( src -> alloced_len , MYF ( MY_WME ) ) ) ) die ( "Out of memory" ) ;
 else dest -> alloced_len = src -> alloced_len ;
 dest -> str_val_len = src -> str_val_len ;
 if ( src -> str_val_len ) memcpy ( dest -> str_val , src -> str_val , src -> str_val_len ) ;
 }