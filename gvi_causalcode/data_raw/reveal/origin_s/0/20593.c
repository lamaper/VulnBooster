static void DisconnectDatabase ( ParallelSlot * slot ) {
 char errbuf [ 256 ] ;
 if ( ! slot -> connection ) return ;
 if ( PQtransactionStatus ( slot -> connection ) == PQTRANS_ACTIVE ) {
 PGcancel * cancel ;
 if ( ( cancel = PQgetCancel ( slot -> connection ) ) ) {
 PQcancel ( cancel , errbuf , sizeof ( errbuf ) ) ;
 PQfreeCancel ( cancel ) ;
 }
 }
 PQfinish ( slot -> connection ) ;
 slot -> connection = NULL ;
 }