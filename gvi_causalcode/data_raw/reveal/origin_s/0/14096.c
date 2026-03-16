static int last_msg_cmp ( LAST_MSG_REC * m1 , LAST_MSG_REC * m2 ) {
 return m1 -> time < m2 -> time ? 1 : - 1 ;
 }