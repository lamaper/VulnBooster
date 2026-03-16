static int sockstat_seq_open ( struct inode * inode , struct file * file ) {
 return single_open_net ( inode , file , sockstat_seq_show ) ;
 }