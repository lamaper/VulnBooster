static int proc_tcp_available_congestion_control ( ctl_table * ctl , int write , void __user * buffer , size_t * lenp , loff_t * ppos ) {
 ctl_table tbl = {
 . maxlen = TCP_CA_BUF_MAX , }
 ;
 int ret ;
 tbl . data = kmalloc ( tbl . maxlen , GFP_USER ) ;
 if ( ! tbl . data ) return - ENOMEM ;
 tcp_get_available_congestion_control ( tbl . data , TCP_CA_BUF_MAX ) ;
 ret = proc_dostring ( & tbl , write , buffer , lenp , ppos ) ;
 kfree ( tbl . data ) ;
 return ret ;
 }