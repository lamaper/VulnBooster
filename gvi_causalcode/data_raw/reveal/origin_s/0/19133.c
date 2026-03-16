static int dcc_ctcp_resume_parse ( int type , const char * data , const char * nick , FILE_DCC_REC * * dcc , uoff_t * size , int * pasv_id ) {
 char * * params ;
 int paramcount , fileparams ;
 int port ;
 params = g_strsplit ( data , " " , - 1 ) ;
 paramcount = g_strv_length ( params ) ;
 if ( paramcount < 3 ) return 0 ;
 fileparams = get_file_params_count_resume ( params , paramcount ) ;
 if ( paramcount >= fileparams + 2 ) {
 port = atoi ( params [ fileparams ] ) ;
 * size = str_to_uofft ( params [ fileparams + 1 ] ) ;
 * pasv_id = ( ( port == 0 ) && ( paramcount == fileparams + 3 ) ) ? atoi ( params [ fileparams + 2 ] ) : - 1 ;
 * dcc = dcc_resume_find ( type , nick , port ) ;
 g_strfreev ( params ) ;
 return ( ( * dcc != NULL ) && ( ( * dcc ) -> pasv_id == * pasv_id ) ) ;
 }
 g_strfreev ( params ) ;
 return FALSE ;
 }