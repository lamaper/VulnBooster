static int ipv4_ping_group_range ( ctl_table * table , int write , void __user * buffer , size_t * lenp , loff_t * ppos ) {
 int ret ;
 gid_t range [ 2 ] ;
 ctl_table tmp = {
 . data = & range , . maxlen = sizeof ( range ) , . mode = table -> mode , . extra1 = & ip_ping_group_range_min , . extra2 = & ip_ping_group_range_max , }
 ;
 inet_get_ping_group_range_table ( table , range , range + 1 ) ;
 ret = proc_dointvec_minmax ( & tmp , write , buffer , lenp , ppos ) ;
 if ( write && ret == 0 ) set_ping_group_range ( table , range ) ;
 return ret ;
 }