const char * GetInputMessageTypeName ( const IPC : : Message & message ) {
 switch ( message . type ( ) ) {

 break ;
 }
 ;
 return "NonInputMsgType" ;
 }