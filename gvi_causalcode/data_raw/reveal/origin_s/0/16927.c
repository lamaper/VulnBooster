TSSslConnection TSVConnSSLConnectionGet ( TSVConn sslp ) {
 TSSslConnection ssl = nullptr ;
 NetVConnection * vc = reinterpret_cast < NetVConnection * > ( sslp ) ;
 SSLNetVConnection * ssl_vc = dynamic_cast < SSLNetVConnection * > ( vc ) ;
 if ( ssl_vc != nullptr ) {
 ssl = reinterpret_cast < TSSslConnection > ( ssl_vc -> ssl ) ;
 }
 return ssl ;
 }