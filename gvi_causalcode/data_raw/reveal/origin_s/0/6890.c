int qemuAgentSetVCPUs ( qemuAgentPtr mon , qemuAgentCPUInfoPtr info , size_t ninfo ) {
 int rv ;
 int nmodified ;
 size_t i ;
 do {
 if ( ( rv = qemuAgentSetVCPUsCommand ( mon , info , ninfo , & nmodified ) ) < 0 ) return - 1 ;
 if ( rv == nmodified ) return 0 ;
 for ( i = 0 ;
 i < ninfo && rv > 0 ;
 i ++ ) {
 if ( ! info [ i ] . modified ) continue ;
 info [ i ] . modified = false ;
 rv -- ;
 }
 }
 while ( 1 ) ;
 return 0 ;
 }