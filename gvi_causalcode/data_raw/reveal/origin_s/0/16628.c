static void ctcp_msg_dcc_accept ( IRC_SERVER_REC * server , const char * data , const char * nick , const char * addr , const char * target , DCC_REC * chat ) {
 FILE_DCC_REC * dcc ;
 uoff_t size ;
 int pasv_id ;
 if ( ! dcc_ctcp_resume_parse ( DCC_GET_TYPE , data , nick , & dcc , & size , & pasv_id ) || ( dcc != NULL && DCC_GET ( dcc ) -> get_type != DCC_GET_RESUME ) ) {
 signal_emit ( "dcc error ctcp" , 5 , "ACCEPT" , data , nick , addr , target ) ;
 }
 else if ( dcc != NULL && dcc_resume_file_check ( dcc , server , size ) ) {
 if ( ! dcc_is_passive ( dcc ) ) dcc_get_connect ( DCC_GET ( dcc ) ) ;
 else dcc_get_passive ( DCC_GET ( dcc ) ) ;
 }
 }