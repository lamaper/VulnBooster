static int snmp_seq_show ( struct seq_file * seq , void * v ) {
 int i ;
 struct net * net = seq -> private ;
 seq_puts ( seq , "Ip: Forwarding DefaultTTL" ) ;
 for ( i = 0 ;
 snmp4_ipstats_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %s" , snmp4_ipstats_list [ i ] . name ) ;
 seq_printf ( seq , "\nIp: %d %d" , IPV4_DEVCONF_ALL ( net , FORWARDING ) ? 1 : 2 , sysctl_ip_default_ttl ) ;
 BUILD_BUG_ON ( offsetof ( struct ipstats_mib , mibs ) != 0 ) ;
 for ( i = 0 ;
 snmp4_ipstats_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %llu" , snmp_fold_field64 ( ( void __percpu * * ) net -> mib . ip_statistics , snmp4_ipstats_list [ i ] . entry , offsetof ( struct ipstats_mib , syncp ) ) ) ;
 icmp_put ( seq ) ;
 icmpmsg_put ( seq ) ;
 seq_puts ( seq , "\nTcp:" ) ;
 for ( i = 0 ;
 snmp4_tcp_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %s" , snmp4_tcp_list [ i ] . name ) ;
 seq_puts ( seq , "\nTcp:" ) ;
 for ( i = 0 ;
 snmp4_tcp_list [ i ] . name != NULL ;
 i ++ ) {
 if ( snmp4_tcp_list [ i ] . entry == TCP_MIB_MAXCONN ) seq_printf ( seq , " %ld" , snmp_fold_field ( ( void __percpu * * ) net -> mib . tcp_statistics , snmp4_tcp_list [ i ] . entry ) ) ;
 else seq_printf ( seq , " %lu" , snmp_fold_field ( ( void __percpu * * ) net -> mib . tcp_statistics , snmp4_tcp_list [ i ] . entry ) ) ;
 }
 seq_puts ( seq , "\nUdp:" ) ;
 for ( i = 0 ;
 snmp4_udp_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %s" , snmp4_udp_list [ i ] . name ) ;
 seq_puts ( seq , "\nUdp:" ) ;
 for ( i = 0 ;
 snmp4_udp_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %lu" , snmp_fold_field ( ( void __percpu * * ) net -> mib . udp_statistics , snmp4_udp_list [ i ] . entry ) ) ;
 seq_puts ( seq , "\nUdpLite:" ) ;
 for ( i = 0 ;
 snmp4_udp_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %s" , snmp4_udp_list [ i ] . name ) ;
 seq_puts ( seq , "\nUdpLite:" ) ;
 for ( i = 0 ;
 snmp4_udp_list [ i ] . name != NULL ;
 i ++ ) seq_printf ( seq , " %lu" , snmp_fold_field ( ( void __percpu * * ) net -> mib . udplite_statistics , snmp4_udp_list [ i ] . entry ) ) ;
 seq_putc ( seq , '\n' ) ;
 return 0 ;
 }