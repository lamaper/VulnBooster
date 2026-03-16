static void set_local_port_range ( int range [ 2 ] ) {
 write_seqlock ( & sysctl_local_ports . lock ) ;
 sysctl_local_ports . range [ 0 ] = range [ 0 ] ;
 sysctl_local_ports . range [ 1 ] = range [ 1 ] ;
 write_sequnlock ( & sysctl_local_ports . lock ) ;
 }