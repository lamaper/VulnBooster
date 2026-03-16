WRITE_CLASS_ENCODER ( CephXServerChallenge ) struct CephXRequestHeader {
 __u16 request_type ;
 void encode ( bufferlist & bl ) const {
 : : encode ( request_type , bl ) ;
 }
 void decode ( bufferlist : : iterator & bl ) {
 : : decode ( request_type , bl ) ;
 }
 }
 ;
 WRITE_CLASS_ENCODER ( CephXRequestHeader ) struct CephXResponseHeader {
 uint16_t request_type ;
 int32_t status ;
 void encode ( bufferlist & bl ) const {
 : : encode ( request_type , bl ) ;
 : : encode ( status , bl ) ;
 }
 void decode ( bufferlist : : iterator & bl ) {
 : : decode ( request_type , bl ) ;
 : : decode ( status , bl ) ;
 }
 }