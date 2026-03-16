static void set_ping_group_range ( struct ctl_table * table , gid_t range [ 2 ] ) {
 gid_t * data = table -> data ;
 write_seqlock ( & sysctl_local_ports . lock ) ;
 data [ 0 ] = range [ 0 ] ;
 data [ 1 ] = range [ 1 ] ;
 write_sequnlock ( & sysctl_local_ports . lock ) ;
 }