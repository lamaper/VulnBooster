static void icmp_put ( struct seq_file * seq ) {
 int i ;
 struct net * net = seq -> private ;
 atomic_long_t * ptr = net -> mib . icmpmsg_statistics -> mibs ;
 seq_puts ( seq , "\nIcmp: InMsgs InErrors" ) ;
 for ( i = 0 ;
 icmpmibmap [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " In%s" , icmpmibmap [ i ] . name ) ;
 seq_printf ( seq , " OutMsgs OutErrors" ) ;
 for ( i = 0 ;
 icmpmibmap [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " Out%s" , icmpmibmap [ i ] . name ) ;
 seq_printf ( seq , "\nIcmp: %lu %lu" , snmp_fold_field ( ( void __percpu * * ) net -> mib . icmp_statistics , ICMP_MIB_INMSGS ) , snmp_fold_field ( ( void __percpu * * ) net -> mib . icmp_statistics , ICMP_MIB_INERRORS ) ) ;
 for ( i = 0 ;
 icmpmibmap [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %lu" , atomic_long_read ( ptr + icmpmibmap [ i ] . index ) ) ;
 seq_printf ( seq , " %lu %lu" , snmp_fold_field ( ( void __percpu * * ) net -> mib . icmp_statistics , ICMP_MIB_OUTMSGS ) , snmp_fold_field ( ( void __percpu * * ) net -> mib . icmp_statistics , ICMP_MIB_OUTERRORS ) ) ;
 for ( i = 0 ;
 icmpmibmap [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %lu" , atomic_long_read ( ptr + ( icmpmibmap [ i ] . index | 0x100 ) ) ) ;
 }