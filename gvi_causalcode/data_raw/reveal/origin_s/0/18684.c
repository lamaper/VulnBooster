static int ipv4_tcp_mem ( ctl_table * ctl , int write , void __user * buffer , size_t * lenp , loff_t * ppos ) {
 int ret ;
 unsigned long vec [ 3 ] ;
 struct net * net = current -> nsproxy -> net_ns ;


 . data = & vec , . maxlen = sizeof ( vec ) , . mode = ctl -> mode , }
 ;
 if ( ! write ) {
 ctl -> data = & net -> ipv4 . sysctl_tcp_mem ;
 return proc_doulongvec_minmax ( ctl , write , buffer , lenp , ppos ) ;
 }
 ret = proc_doulongvec_minmax ( & tmp , write , buffer , lenp , ppos ) ;
 if ( ret ) return ret ;

 memcg = mem_cgroup_from_task ( current ) ;
 tcp_prot_mem ( memcg , vec [ 0 ] , 0 ) ;
 tcp_prot_mem ( memcg , vec [ 1 ] , 1 ) ;
 tcp_prot_mem ( memcg , vec [ 2 ] , 2 ) ;
 rcu_read_unlock ( ) ;

 net -> ipv4 . sysctl_tcp_mem [ 1 ] = vec [ 1 ] ;
 net -> ipv4 . sysctl_tcp_mem [ 2 ] = vec [ 2 ] ;
 return 0 ;
 }