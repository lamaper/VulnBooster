void TSActionCancel ( TSAction actionp ) {
 Action * a ;
 INKContInternal * i ;
 if ( ( uintptr_t ) actionp & 0x1 ) {
 a = ( Action * ) ( ( uintptr_t ) actionp - 1 ) ;
 i = ( INKContInternal * ) a -> continuation ;
 i -> handle_event_count ( EVENT_IMMEDIATE ) ;
 }
 else {
 a = ( Action * ) actionp ;
 }
 a -> cancel ( ) ;
 }