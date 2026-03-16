int qemuAgentSetUserPassword ( qemuAgentPtr mon , const char * user , const char * password , bool crypted ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 char * password64 = NULL ;
 if ( ! ( password64 = virStringEncodeBase64 ( ( unsigned char * ) password , strlen ( password ) ) ) ) goto cleanup ;
 if ( ! ( cmd = qemuAgentMakeCommand ( "guest-set-user-password" , "b:crypted" , crypted , "s:username" , user , "s:password" , password64 , NULL ) ) ) goto cleanup ;
 if ( qemuAgentCommand ( mon , cmd , & reply , true , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 ) goto cleanup ;
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 VIR_FREE ( password64 ) ;
 return ret ;
 }