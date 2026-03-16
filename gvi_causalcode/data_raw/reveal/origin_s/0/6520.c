static int compare_entry ( const void * _mn1 , const void * _mn2 ) {
 const NameEntry * mn1 = _mn1 , * mn2 = _mn2 ;
 if ( mn1 -> platform != mn2 -> platform ) return ( mn1 -> platform - mn2 -> platform ) ;
 if ( mn1 -> specific != mn2 -> specific ) return ( mn1 -> specific - mn2 -> specific ) ;
 if ( mn1 -> lang != mn2 -> lang ) return ( mn1 -> lang - mn2 -> lang ) ;
 return ( mn1 -> strid - mn2 -> strid ) ;
 }