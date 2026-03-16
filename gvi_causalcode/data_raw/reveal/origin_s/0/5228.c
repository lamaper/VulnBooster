int32 get_typavgwidth ( Oid typid , int32 typmod ) {
 int typlen = get_typlen ( typid ) ;
 int32 maxwidth ;
 if ( typlen > 0 ) return typlen ;
 maxwidth = type_maximum_size ( typid , typmod ) ;
 if ( maxwidth > 0 ) {
 if ( typid == BPCHAROID ) return maxwidth ;
 if ( maxwidth <= 32 ) return maxwidth ;
 if ( maxwidth < 1000 ) return 32 + ( maxwidth - 32 ) / 2 ;
 return 32 + ( 1000 - 32 ) / 2 ;
 }
 return 32 ;
 }