static gboolean ng_read_bytes ( wtap * wth , void * buffer , unsigned int nbytes , gboolean is_random , int * err , gchar * * err_info ) {
 if ( ! ng_read_bytes_or_eof ( wth , buffer , nbytes , is_random , err , err_info ) ) {
 if ( * err == 0 ) * err = WTAP_ERR_SHORT_READ ;
 return FALSE ;
 }
 return TRUE ;
 }