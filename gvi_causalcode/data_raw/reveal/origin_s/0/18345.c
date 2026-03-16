int remoteRemoveClientStream ( struct qemud_client * client , struct qemud_client_stream * stream ) {
 VIR_DEBUG ( "client=%p proc=%d serial=%d" , client , stream -> procedure , stream -> serial ) ;
 struct qemud_client_stream * curr = client -> streams ;
 struct qemud_client_stream * prev = NULL ;
 struct qemud_client_filter * filter = NULL ;
 if ( client -> filters == & stream -> filter ) {
 client -> filters = client -> filters -> next ;
 }
 else {
 filter = client -> filters ;
 while ( filter ) {
 if ( filter -> next == & stream -> filter ) {
 filter -> next = filter -> next -> next ;
 break ;
 }
 filter = filter -> next ;
 }
 }
 if ( ! stream -> closed ) {
 virStreamEventRemoveCallback ( stream -> st ) ;
 virStreamAbort ( stream -> st ) ;
 }
 while ( curr ) {
 if ( curr == stream ) {
 if ( prev ) prev -> next = curr -> next ;
 else client -> streams = curr -> next ;
 remoteFreeClientStream ( client , stream ) ;
 return 0 ;
 }
 prev = curr ;
 curr = curr -> next ;
 }
 return - 1 ;
 }