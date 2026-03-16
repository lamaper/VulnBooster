TSNextProtocolSet TSGetcloneProtoSet ( TSAcceptor tna ) {
 NetAccept * na = reinterpret_cast < NetAccept * > ( tna ) ;
 return ( na && na -> snpa ) ? reinterpret_cast < TSNextProtocolSet > ( na -> snpa -> cloneProtoSet ( ) ) : nullptr ;
 }