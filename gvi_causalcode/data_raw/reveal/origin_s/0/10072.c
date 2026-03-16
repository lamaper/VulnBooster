static int sockstat_seq_show ( struct seq_file * seq , void * v ) {
 struct net * net = seq -> private ;
 int orphans , sockets ;
 local_bh_disable ( ) ;
 orphans = percpu_counter_sum_positive ( & tcp_orphan_count ) ;
 sockets = proto_sockets_allocated_sum_positive ( & tcp_prot ) ;
 local_bh_enable ( ) ;
 socket_seq_show ( seq ) ;
 seq_printf ( seq , "TCP: inuse %d orphan %d tw %d alloc %d mem %ld\n" , sock_prot_inuse_get ( net , & tcp_prot ) , orphans , tcp_death_row . tw_count , sockets , proto_memory_allocated ( & tcp_prot ) ) ;
 seq_printf ( seq , "UDP: inuse %d mem %ld\n" , sock_prot_inuse_get ( net , & udp_prot ) , proto_memory_allocated ( & udp_prot ) ) ;
 seq_printf ( seq , "UDPLITE: inuse %d\n" , sock_prot_inuse_get ( net , & udplite_prot ) ) ;
 seq_printf ( seq , "RAW: inuse %d\n" , sock_prot_inuse_get ( net , & raw_prot ) ) ;
 seq_printf ( seq , "FRAG: inuse %d memory %d\n" , ip_frag_nqueues ( net ) , ip_frag_mem ( net ) ) ;
 return 0 ;
 }