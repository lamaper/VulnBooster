static void inet_get_ping_group_range_table ( struct ctl_table * table , gid_t * low , gid_t * high ) {
 gid_t * data = table -> data ;
 unsigned int seq ;
 do {
 seq = read_seqbegin ( & sysctl_local_ports . lock ) ;
 * low = data [ 0 ] ;
 * high = data [ 1 ] ;
 }
 while ( read_seqretry ( & sysctl_local_ports . lock , seq ) ) ;
 }