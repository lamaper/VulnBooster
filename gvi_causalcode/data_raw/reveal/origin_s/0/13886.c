static long get_gmoffset ( struct tm * tm ) {
 long offset ;




 if ( tm -> tm_isdst ) offset += 3600 ;
 return ( offset ) ;
 }