void TSVConnReenable ( TSVConn vconn ) {
 NetVConnection * vc = reinterpret_cast < NetVConnection * > ( vconn ) ;
 SSLNetVConnection * ssl_vc = dynamic_cast < SSLNetVConnection * > ( vc ) ;
 if ( ssl_vc != nullptr ) {
 EThread * eth = this_ethread ( ) ;
 bool reschedule = eth != ssl_vc -> thread ;
 if ( ! reschedule ) {
 MUTEX_TRY_LOCK ( trylock , ssl_vc -> mutex , eth ) ;
 if ( trylock . is_locked ( ) ) {
 ssl_vc -> reenable ( ssl_vc -> nh ) ;
 }
 else {
 reschedule = true ;
 }
 }
 if ( reschedule ) {
 ssl_vc -> thread -> schedule_imm ( new TSSslCallback ( ssl_vc ) ) ;
 }
 }
 }