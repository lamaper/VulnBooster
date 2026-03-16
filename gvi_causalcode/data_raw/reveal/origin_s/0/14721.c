TSAcceptor TSAcceptorGetbyID ( int ID ) {
 Debug ( "ssl" , "getNetAccept in INK API.cc %p" , naVec . at ( ID ) ) ;
 return reinterpret_cast < TSAcceptor > ( naVec . at ( ID ) ) ;
 }