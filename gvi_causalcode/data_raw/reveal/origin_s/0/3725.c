static int netstat_seq_open ( struct inode * inode , struct file * file ) {
 return single_open_net ( inode , file , netstat_seq_show ) ;
 }