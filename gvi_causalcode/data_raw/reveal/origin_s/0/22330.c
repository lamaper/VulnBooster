static void * prplcb_notify_email ( PurpleConnection * gc , const char * subject , const char * from , const char * to , const char * url ) {
 struct im_connection * ic = purple_ic_by_gc ( gc ) ;
 imcb_notify_email ( ic , "Received e-mail from %s for %s: %s <%s>" , from , to , subject , url ) ;
 return NULL ;
 }