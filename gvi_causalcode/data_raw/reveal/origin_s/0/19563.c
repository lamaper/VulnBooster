static void icmpmsg_put ( struct seq_file * seq ) {

 unsigned short type [ PERLINE ] ;
 unsigned long vals [ PERLINE ] , val ;
 struct net * net = seq -> private ;
 count = 0 ;
 for ( i = 0 ;
 i < ICMPMSG_MIB_MAX ;
 i ++ ) {
 val = atomic_long_read ( & net -> mib . icmpmsg_statistics -> mibs [ i ] ) ;
 if ( val ) {
 type [ count ] = i ;
 vals [ count ++ ] = val ;
 }
 if ( count == PERLINE ) {
 icmpmsg_put_line ( seq , vals , type , count ) ;
 count = 0 ;
 }
 }
 icmpmsg_put_line ( seq , vals , type , count ) ;
