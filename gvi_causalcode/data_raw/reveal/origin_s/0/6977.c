static int ipv4_local_port_range ( ctl_table * table , int write , void __user * buffer , size_t * lenp , loff_t * ppos ) {
 int ret ;
 int range [ 2 ] ;
 ctl_table tmp = {
 . data = & range , . maxlen = sizeof ( range ) , . mode = table -> mode , . extra1 = & ip_local_port_range_min , . extra2 = & ip_local_port_range_max , }
 ;
 inet_get_local_port_range ( range , range + 1 ) ;
 ret = proc_dointvec_minmax ( & tmp , write , buffer , lenp , ppos ) ;
 if ( write && ret == 0 ) {
 if ( range [ 1 ] < range [ 0 ] ) ret = - EINVAL ;
 else set_local_port_range ( range ) ;
 }
 return ret ;
 }