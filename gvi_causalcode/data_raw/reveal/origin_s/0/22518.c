static int netstat_seq_show ( struct seq_file * seq , void * v ) {
 int i ;
 struct net * net = seq -> private ;
 seq_puts ( seq , "TcpExt:" ) ;
 for ( i = 0 ;
 snmp4_net_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %s" , snmp4_net_list [ i ] . name ) ;
 seq_puts ( seq , "\nTcpExt:" ) ;
 for ( i = 0 ;
 snmp4_net_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %lu" , snmp_fold_field ( ( void __percpu * * ) net -> mib . net_statistics , snmp4_net_list [ i ] . entry ) ) ;
 seq_puts ( seq , "\nIpExt:" ) ;
 for ( i = 0 ;
 snmp4_ipextstats_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %s" , snmp4_ipextstats_list [ i ] . name ) ;
 seq_puts ( seq , "\nIpExt:" ) ;
 for ( i = 0 ;
 snmp4_ipextstats_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %llu" , snmp_fold_field64 ( ( void __percpu * * ) net -> mib . ip_statistics , snmp4_ipextstats_list [ i ] . entry , offsetof ( struct ipstats_mib , syncp ) ) ) ;
 seq_putc ( seq , '\n' ) ;
 return 0 ;
 }