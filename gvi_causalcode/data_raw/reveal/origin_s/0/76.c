static void ctcp_msg_dcc_resume ( IRC_SERVER_REC * server , const char * data , const char * nick , const char * addr , const char * target , DCC_REC * chat ) {
 FILE_DCC_REC * dcc ;
 char * str ;
 uoff_t size ;
 int pasv_id = - 1 ;
 if ( ! dcc_ctcp_resume_parse ( DCC_SEND_TYPE , data , nick , & dcc , & size , & pasv_id ) ) {
 signal_emit ( "dcc error ctcp" , 5 , "RESUME" , data , nick , addr , target ) ;
 }
 else if ( dcc != NULL && dcc_resume_file_check ( dcc , server , size ) ) {
 if ( ! dcc_is_passive ( dcc ) ) {
 str = g_strdup_printf ( DCC_SEND ( dcc ) -> file_quoted ? "DCC ACCEPT \"%s\" %d %" PRIuUOFF_T : "DCC ACCEPT %s %d %" PRIuUOFF_T , dcc -> arg , dcc -> port , dcc -> transfd ) ;
 }
 else {
 str = g_strdup_printf ( DCC_SEND ( dcc ) -> file_quoted ? "DCC ACCEPT \"%s\" 0 %" PRIuUOFF_T " %d" : "DCC ACCEPT %s 0 %" PRIuUOFF_T " %d" , dcc -> arg , dcc -> transfd , dcc -> pasv_id ) ;
 }
 dcc_ctcp_message ( dcc -> server , dcc -> nick , dcc -> chat , FALSE , str ) ;
 g_free ( str ) ;
 }
 }