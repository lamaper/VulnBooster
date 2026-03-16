WRITE_CLASS_ENCODER ( CephXServiceTicket ) struct CephXServiceTicketInfo {
 AuthTicket ticket ;
 CryptoKey session_key ;
 void encode ( bufferlist & bl ) const {
 __u8 struct_v = 1 ;
 : : encode ( struct_v , bl ) ;
 : : encode ( ticket , bl ) ;
 : : encode ( session_key , bl ) ;
 }
 void decode ( bufferlist : : iterator & bl ) {
 __u8 struct_v ;
 : : decode ( struct_v , bl ) ;
 : : decode ( ticket , bl ) ;
 : : decode ( session_key , bl ) ;
 }
 }
 ;
 WRITE_CLASS_ENCODER ( CephXServiceTicketInfo ) struct CephXAuthorizeChallenge : public AuthAuthorizerChallenge {
 uint64_t server_challenge ;
 void encode ( bufferlist & bl ) const {
 __u8 struct_v = 1 ;
 : : encode ( struct_v , bl ) ;
 : : encode ( server_challenge , bl ) ;
 }
 void decode ( bufferlist : : iterator & bl ) {
 __u8 struct_v ;
 : : decode ( struct_v , bl ) ;
 : : decode ( server_challenge , bl ) ;
 }
 }