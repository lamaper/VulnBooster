static int proc_tcp_congestion_control ( ctl_table * ctl , int write , void __user * buffer , size_t * lenp , loff_t * ppos ) {
 char val [ TCP_CA_NAME_MAX ] ;
 ctl_table tbl = {
 . data = val , . maxlen = TCP_CA_NAME_MAX , }
 ;
 int ret ;
 tcp_get_default_congestion_control ( val ) ;
 ret = proc_dostring ( & tbl , write , buffer , lenp , ppos ) ;
 if ( write && ret == 0 ) ret = tcp_set_default_congestion_control ( val ) ;
 return ret ;
 }