static uchar * check_get_key ( ACL_USER * buff , size_t * length , my_bool not_used __attribute__ ( ( unused ) ) ) {
 * length = buff -> hostname_length ;
 return ( uchar * ) buff -> host . hostname ;
 }