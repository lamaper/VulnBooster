void remoteFreeClientStream ( struct qemud_client * client , struct qemud_client_stream * stream ) {
 struct qemud_client_message * msg ;
 if ( ! stream ) return ;
 VIR_DEBUG ( "proc=%d serial=%d" , stream -> procedure , stream -> serial ) ;
 msg = stream -> rx ;
 while ( msg ) {
 struct qemud_client_message * tmp = msg -> next ;
 qemudClientMessageRelease ( client , msg ) ;
 msg = tmp ;
 }
 virStreamFree ( stream -> st ) ;
 VIR_FREE ( stream ) ;
 }