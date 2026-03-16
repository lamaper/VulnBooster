void DisconnectDatabase ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 char errbuf [ 1 ] ;
 if ( ! AH -> connection ) return ;
 if ( AH -> connCancel ) {
 if ( PQtransactionStatus ( AH -> connection ) == PQTRANS_ACTIVE ) PQcancel ( AH -> connCancel , errbuf , sizeof ( errbuf ) ) ;
 set_archive_cancel_info ( AH , NULL ) ;
 }
 PQfinish ( AH -> connection ) ;
 AH -> connection = NULL ;
 }