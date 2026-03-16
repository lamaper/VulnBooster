static apr_status_t modsecurity_tx_cleanup ( void * data ) {
 modsec_rec * msr = ( modsec_rec * ) data ;
 char * my_error_msg = NULL ;
 if ( msr == NULL ) return APR_SUCCESS ;
 if ( msr -> mpd != NULL ) multipart_cleanup ( msr ) ;
 if ( msr -> xml != NULL ) xml_cleanup ( msr ) ;
 modsecurity_request_body_clear ( msr , & my_error_msg ) ;
 if ( my_error_msg != NULL ) {
 msr_log ( msr , 1 , "%s" , my_error_msg ) ;
 }


 }