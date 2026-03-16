WRITE_CLASS_ENCODER ( CephXResponseHeader ) struct CephXTicketBlob {
 uint64_t secret_id ;
 bufferlist blob ;
 CephXTicketBlob ( ) : secret_id ( 0 ) {
 }
 void encode ( bufferlist & bl ) const {
 __u8 struct_v = 1 ;
 : : encode ( struct_v , bl ) ;
 : : encode ( secret_id , bl ) ;
 : : encode ( blob , bl ) ;
 }
 void decode ( bufferlist : : iterator & bl ) {
 __u8 struct_v ;
 : : decode ( struct_v , bl ) ;
 : : decode ( secret_id , bl ) ;
 : : decode ( blob , bl ) ;
 }
 }
 ;
 WRITE_CLASS_ENCODER ( CephXTicketBlob ) struct CephXAuthenticate {
 uint64_t client_challenge ;
 uint64_t key ;
 CephXTicketBlob old_ticket ;
 void encode ( bufferlist & bl ) const {
 __u8 struct_v = 1 ;
 : : encode ( struct_v , bl ) ;
 : : encode ( client_challenge , bl ) ;
 : : encode ( key , bl ) ;
 : : encode ( old_ticket , bl ) ;
 }
 void decode ( bufferlist : : iterator & bl ) {
 __u8 struct_v ;
 : : decode ( struct_v , bl ) ;
 : : decode ( client_challenge , bl ) ;
 : : decode ( key , bl ) ;
 : : decode ( old_ticket , bl ) ;
 }
 }