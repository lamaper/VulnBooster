void RecordsConfigIterate ( RecordElementCallback callback , void * data ) {
 for ( unsigned i = 0 ;
 i < countof ( RecordsConfig ) ;
 ++ i ) {
 callback ( & RecordsConfig [ i ] , data ) ;
 }
 }