TSReturnCode TSVConnTunnel ( TSVConn sslp ) {
 NetVConnection * vc = reinterpret_cast < NetVConnection * > ( sslp ) ;
 SSLNetVConnection * ssl_vc = dynamic_cast < SSLNetVConnection * > ( vc ) ;
 TSReturnCode zret = TS_SUCCESS ;
 if ( nullptr != ssl_vc ) {
 ssl_vc -> hookOpRequested = SSL_HOOK_OP_TUNNEL ;
 }
 else {
 zret = TS_ERROR ;
 }
 return zret ;
 }