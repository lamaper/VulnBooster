static char * set_eval_display_name ( set_t * set , char * value ) {
 account_t * acc = set -> data ;
 struct im_connection * ic = acc -> ic ;
 if ( ic ) {
 imcb_log ( ic , "Changing display_name not currently supported with libpurple!" ) ;
 }
 return NULL ;
 }