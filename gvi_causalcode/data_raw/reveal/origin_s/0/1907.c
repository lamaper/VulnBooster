void WriteToc ( ArchiveHandle * AH ) {
 TocEntry * te ;
 char workbuf [ 32 ] ;
 int tocCount ;
 int i ;
 tocCount = 0 ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( ( te -> reqs & ( REQ_SCHEMA | REQ_DATA | REQ_SPECIAL ) ) != 0 ) tocCount ++ ;
 }
 WriteInt ( AH , tocCount ) ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( ( te -> reqs & ( REQ_SCHEMA | REQ_DATA | REQ_SPECIAL ) ) == 0 ) continue ;
 WriteInt ( AH , te -> dumpId ) ;
 WriteInt ( AH , te -> dataDumper ? 1 : 0 ) ;
 sprintf ( workbuf , "%u" , te -> catalogId . tableoid ) ;
 WriteStr ( AH , workbuf ) ;
 sprintf ( workbuf , "%u" , te -> catalogId . oid ) ;
 WriteStr ( AH , workbuf ) ;
 WriteStr ( AH , te -> tag ) ;
 WriteStr ( AH , te -> desc ) ;
 WriteInt ( AH , te -> section ) ;
 WriteStr ( AH , te -> defn ) ;
 WriteStr ( AH , te -> dropStmt ) ;
 WriteStr ( AH , te -> copyStmt ) ;
 WriteStr ( AH , te -> namespace ) ;
 WriteStr ( AH , te -> tablespace ) ;
 WriteStr ( AH , te -> owner ) ;
 WriteStr ( AH , te -> withOids ? "true" : "false" ) ;
 for ( i = 0 ;
 i < te -> nDeps ;
 i ++ ) {
 sprintf ( workbuf , "%d" , te -> dependencies [ i ] ) ;
 WriteStr ( AH , workbuf ) ;
 }
 WriteStr ( AH , NULL ) ;
 if ( AH -> WriteExtraTocPtr ) ( * AH -> WriteExtraTocPtr ) ( AH , te ) ;
 }
 }