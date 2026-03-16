static void _initializeULanguageTag ( ULanguageTag * langtag ) {
 int32_t i ;
 langtag -> buf = NULL ;
 langtag -> language = EMPTY ;
 for ( i = 0 ;
 i < MAXEXTLANG ;
 i ++ ) {
 langtag -> extlang [ i ] = NULL ;
 }
 langtag -> script = EMPTY ;
 langtag -> region = EMPTY ;
 langtag -> variants = NULL ;
 langtag -> extensions = NULL ;
 langtag -> grandfathered = EMPTY ;
 langtag -> privateuse = EMPTY ;
 }