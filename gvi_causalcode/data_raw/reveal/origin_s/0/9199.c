int TSAcceptorIDGet ( TSAcceptor acceptor ) {
 NetAccept * na = reinterpret_cast < NetAccept * > ( acceptor ) ;
 return na ? na -> id : - 1 ;
 }