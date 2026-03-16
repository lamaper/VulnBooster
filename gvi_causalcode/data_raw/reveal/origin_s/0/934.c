static int proc_allowed_congestion_control ( ctl_table * ctl , int write , void __user * buffer , size_t * lenp , loff_t * ppos ) {
 ctl_table tbl = {
 . maxlen = TCP_CA_BUF_MAX }
 ;
 int ret ;
 tbl . data = kmalloc ( tbl . maxlen , GFP_USER ) ;
 if ( ! tbl . data ) return - ENOMEM ;
 tcp_get_allowed_congestion_control ( tbl . data , tbl . maxlen ) ;
 ret = proc_dostring ( & tbl , write , buffer , lenp , ppos ) ;
 if ( write && ret == 0 ) ret = tcp_set_allowed_congestion_control ( tbl . data ) ;
 kfree ( tbl . data ) ;
 return ret ;
 }