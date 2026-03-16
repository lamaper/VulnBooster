static int snmp_seq_open ( struct inode * inode , struct file * file ) {
 return single_open_net ( inode , file , snmp_seq_show ) ;
 }