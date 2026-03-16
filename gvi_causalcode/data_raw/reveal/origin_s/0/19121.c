static struct im_connection * purple_ic_by_gc ( PurpleConnection * gc ) {
 return purple_ic_by_pa ( purple_connection_get_account ( gc ) ) ;
 }