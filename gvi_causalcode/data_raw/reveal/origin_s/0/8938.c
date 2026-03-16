static void handle_null_request ( int tun_fd , int dns_fd , struct query * q , int domain_len ) {
 struct in_addr tempip ;
 char in [ 512 ] ;
 char logindata [ 16 ] ;
 char out [ 64 * 1024 ] ;
 char unpacked [ 64 * 1024 ] ;
 char * tmp [ 2 ] ;
 int userid ;
 int read ;
 userid = - 1 ;
 if ( domain_len < 2 ) return ;
 memcpy ( in , q -> name , MIN ( domain_len , sizeof ( in ) ) ) ;
 if ( in [ 0 ] == 'V' || in [ 0 ] == 'v' ) {
 int version = 0 ;
 read = unpack_data ( unpacked , sizeof ( unpacked ) , & ( in [ 1 ] ) , domain_len - 1 , b32 ) ;
 if ( read > 4 ) {
 version = ( ( ( unpacked [ 0 ] & 0xff ) << 24 ) | ( ( unpacked [ 1 ] & 0xff ) << 16 ) | ( ( unpacked [ 2 ] & 0xff ) << 8 ) | ( ( unpacked [ 3 ] & 0xff ) ) ) ;
 }
 if ( version == VERSION ) {
 userid = find_available_user ( ) ;
 if ( userid >= 0 ) {
 int i ;
 struct sockaddr_in * tempin ;
 users [ userid ] . seed = rand ( ) ;
 tempin = ( struct sockaddr_in * ) & ( q -> from ) ;
 memcpy ( & ( users [ userid ] . host ) , & ( tempin -> sin_addr ) , sizeof ( struct in_addr ) ) ;
 memcpy ( & ( users [ userid ] . q ) , q , sizeof ( struct query ) ) ;
 users [ userid ] . encoder = get_base32_encoder ( ) ;
 users [ userid ] . downenc = 'T' ;
 send_version_response ( dns_fd , VERSION_ACK , users [ userid ] . seed , userid , q ) ;
 syslog ( LOG_INFO , "accepted version for user #%d from %s" , userid , format_addr ( & q -> from , q -> fromlen ) ) ;
 users [ userid ] . q . id = 0 ;
 users [ userid ] . q . id2 = 0 ;
 users [ userid ] . q_sendrealsoon . id = 0 ;
 users [ userid ] . q_sendrealsoon . id2 = 0 ;
 users [ userid ] . q_sendrealsoon_new = 0 ;
 users [ userid ] . outpacket . len = 0 ;
 users [ userid ] . outpacket . offset = 0 ;
 users [ userid ] . outpacket . sentlen = 0 ;
 users [ userid ] . outpacket . seqno = 0 ;
 users [ userid ] . outpacket . fragment = 0 ;
 users [ userid ] . outfragresent = 0 ;
 users [ userid ] . inpacket . len = 0 ;
 users [ userid ] . inpacket . offset = 0 ;
 users [ userid ] . inpacket . seqno = 0 ;
 users [ userid ] . inpacket . fragment = 0 ;
 users [ userid ] . fragsize = 100 ;
 users [ userid ] . conn = CONN_DNS_NULL ;
 users [ userid ] . lazy = 0 ;

 users [ userid ] . outpacketq_filled = 0 ;

 for ( i = 0 ;
 i < DNSCACHE_LEN ;
 i ++ ) {
 users [ userid ] . dnscache_q [ i ] . id = 0 ;
 users [ userid ] . dnscache_answerlen [ i ] = 0 ;
 }
 }
 users [ userid ] . dnscache_lastfilled = 0 ;

 i < QMEMPING_LEN ;
 i ++ ) users [ userid ] . qmemping_type [ i ] = T_UNSET ;
 users [ userid ] . qmemping_lastfilled = 0 ;
 for ( i = 0 ;
 i < QMEMDATA_LEN ;
 i ++ ) users [ userid ] . qmemdata_type [ i ] = T_UNSET ;
 users [ userid ] . qmemdata_lastfilled = 0 ;
 }
 else {
 send_version_response ( dns_fd , VERSION_FULL , created_users , 0 , q ) ;
 syslog ( LOG_INFO , "dropped user from %s, server full" , format_addr ( & q -> from , q -> fromlen ) ) ;
 }
 }
 else {
 send_version_response ( dns_fd , VERSION_NACK , VERSION , 0 , q ) ;
 syslog ( LOG_INFO , "dropped user from %s, sent bad version %08X" , format_addr ( & q -> from , q -> fromlen ) , version ) ;
 }
 return ;
 }
 else if ( in [ 0 ] == 'L' || in [ 0 ] == 'l' ) {
 read = unpack_data ( unpacked , sizeof ( unpacked ) , & ( in [ 1 ] ) , domain_len - 1 , b32 ) ;
 if ( read < 17 ) {
 write_dns ( dns_fd , q , "BADLEN" , 6 , 'T' ) ;
 return ;
 }
 userid = unpacked [ 0 ] ;
 if ( check_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 syslog ( LOG_WARNING , "dropped login request from user #%d from unexpected source %s" , userid , format_addr ( & q -> from , q -> fromlen ) ) ;
 return ;
 }
 else {
 users [ userid ] . last_pkt = time ( NULL ) ;
 login_calculate ( logindata , 16 , password , users [ userid ] . seed ) ;
 if ( read >= 18 && ( memcmp ( logindata , unpacked + 1 , 16 ) == 0 ) ) {
 users [ userid ] . authenticated = 1 ;
 tempip . s_addr = my_ip ;
 tmp [ 0 ] = strdup ( inet_ntoa ( tempip ) ) ;
 tempip . s_addr = users [ userid ] . tun_ip ;
 tmp [ 1 ] = strdup ( inet_ntoa ( tempip ) ) ;
 read = snprintf ( out , sizeof ( out ) , "%s-%s-%d-%d" , tmp [ 0 ] , tmp [ 1 ] , my_mtu , netmask ) ;
 write_dns ( dns_fd , q , out , read , users [ userid ] . downenc ) ;
 q -> id = 0 ;
 syslog ( LOG_NOTICE , "accepted password from user #%d, given IP %s" , userid , tmp [ 1 ] ) ;
 free ( tmp [ 1 ] ) ;
 free ( tmp [ 0 ] ) ;
 }
 else {
 write_dns ( dns_fd , q , "LNAK" , 4 , 'T' ) ;
 syslog ( LOG_WARNING , "rejected login request from user #%d from %s, bad password" , userid , format_addr ( & q -> from , q -> fromlen ) ) ;
 }
 }
 return ;
 }
 else if ( in [ 0 ] == 'I' || in [ 0 ] == 'i' ) {
 in_addr_t replyaddr ;
 unsigned addr ;
 char reply [ 5 ] ;
 userid = b32_8to5 ( in [ 1 ] ) ;
 if ( check_authenticated_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 return ;
 }
 if ( ns_ip != INADDR_ANY ) {
 replyaddr = ns_ip ;
 }
 else {
 memcpy ( & replyaddr , & q -> destination . s_addr , sizeof ( in_addr_t ) ) ;
 }
 addr = htonl ( replyaddr ) ;
 reply [ 0 ] = 'I' ;
 reply [ 1 ] = ( addr >> 24 ) & 0xFF ;
 reply [ 2 ] = ( addr >> 16 ) & 0xFF ;
 reply [ 3 ] = ( addr >> 8 ) & 0xFF ;
 reply [ 4 ] = ( addr >> 0 ) & 0xFF ;
 write_dns ( dns_fd , q , reply , sizeof ( reply ) , 'T' ) ;
 }
 else if ( in [ 0 ] == 'Z' || in [ 0 ] == 'z' ) {
 write_dns ( dns_fd , q , in , domain_len , 'T' ) ;
 return ;
 }
 else if ( in [ 0 ] == 'S' || in [ 0 ] == 's' ) {
 int codec ;
 struct encoder * enc ;
 if ( domain_len < 3 ) {
 write_dns ( dns_fd , q , "BADLEN" , 6 , 'T' ) ;
 return ;
 }
 userid = b32_8to5 ( in [ 1 ] ) ;
 if ( check_authenticated_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 return ;
 }
 codec = b32_8to5 ( in [ 2 ] ) ;
 switch ( codec ) {
 case 5 : enc = get_base32_encoder ( ) ;
 user_switch_codec ( userid , enc ) ;
 write_dns ( dns_fd , q , enc -> name , strlen ( enc -> name ) , users [ userid ] . downenc ) ;
 break ;
 case 6 : enc = get_base64_encoder ( ) ;
 user_switch_codec ( userid , enc ) ;
 write_dns ( dns_fd , q , enc -> name , strlen ( enc -> name ) , users [ userid ] . downenc ) ;
 break ;
 case 26 : enc = get_base64u_encoder ( ) ;
 user_switch_codec ( userid , enc ) ;
 write_dns ( dns_fd , q , enc -> name , strlen ( enc -> name ) , users [ userid ] . downenc ) ;
 break ;
 case 7 : enc = get_base128_encoder ( ) ;
 user_switch_codec ( userid , enc ) ;
 write_dns ( dns_fd , q , enc -> name , strlen ( enc -> name ) , users [ userid ] . downenc ) ;
 break ;
 default : write_dns ( dns_fd , q , "BADCODEC" , 8 , users [ userid ] . downenc ) ;
 break ;
 }
 return ;
 }
 else if ( in [ 0 ] == 'O' || in [ 0 ] == 'o' ) {
 if ( domain_len < 3 ) {
 write_dns ( dns_fd , q , "BADLEN" , 6 , 'T' ) ;
 return ;
 }
 userid = b32_8to5 ( in [ 1 ] ) ;
 if ( check_authenticated_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 return ;
 }
 switch ( in [ 2 ] ) {
 case 'T' : case 't' : users [ userid ] . downenc = 'T' ;
 write_dns ( dns_fd , q , "Base32" , 6 , users [ userid ] . downenc ) ;
 break ;
 case 'S' : case 's' : users [ userid ] . downenc = 'S' ;
 write_dns ( dns_fd , q , "Base64" , 6 , users [ userid ] . downenc ) ;
 break ;
 case 'U' : case 'u' : users [ userid ] . downenc = 'U' ;
 write_dns ( dns_fd , q , "Base64u" , 7 , users [ userid ] . downenc ) ;
 break ;
 case 'V' : case 'v' : users [ userid ] . downenc = 'V' ;
 write_dns ( dns_fd , q , "Base128" , 7 , users [ userid ] . downenc ) ;
 break ;
 case 'R' : case 'r' : users [ userid ] . downenc = 'R' ;
 write_dns ( dns_fd , q , "Raw" , 3 , users [ userid ] . downenc ) ;
 break ;
 case 'L' : case 'l' : users [ userid ] . lazy = 1 ;
 write_dns ( dns_fd , q , "Lazy" , 4 , users [ userid ] . downenc ) ;
 break ;
 case 'I' : case 'i' : users [ userid ] . lazy = 0 ;
 write_dns ( dns_fd , q , "Immediate" , 9 , users [ userid ] . downenc ) ;
 break ;
 default : write_dns ( dns_fd , q , "BADCODEC" , 8 , users [ userid ] . downenc ) ;
 break ;
 }
 return ;
 }
 else if ( in [ 0 ] == 'Y' || in [ 0 ] == 'y' ) {
 int i ;
 char * datap ;
 int datalen ;
 if ( domain_len < 6 ) {
 write_dns ( dns_fd , q , "BADLEN" , 6 , 'T' ) ;
 return ;
 }
 i = b32_8to5 ( in [ 2 ] ) ;
 switch ( i ) {
 case 1 : datap = DOWNCODECCHECK1 ;
 datalen = DOWNCODECCHECK1_LEN ;
 break ;
 default : write_dns ( dns_fd , q , "BADLEN" , 6 , 'T' ) ;
 return ;
 }
 switch ( in [ 1 ] ) {
 case 'T' : case 't' : if ( q -> type == T_TXT || q -> type == T_SRV || q -> type == T_MX || q -> type == T_CNAME || q -> type == T_A ) {
 write_dns ( dns_fd , q , datap , datalen , 'T' ) ;
 return ;
 }
 break ;
 case 'S' : case 's' : if ( q -> type == T_TXT || q -> type == T_SRV || q -> type == T_MX || q -> type == T_CNAME || q -> type == T_A ) {
 write_dns ( dns_fd , q , datap , datalen , 'S' ) ;
 return ;
 }
 break ;
 case 'U' : case 'u' : if ( q -> type == T_TXT || q -> type == T_SRV || q -> type == T_MX || q -> type == T_CNAME || q -> type == T_A ) {
 write_dns ( dns_fd , q , datap , datalen , 'U' ) ;
 return ;
 }
 break ;
 case 'V' : case 'v' : if ( q -> type == T_TXT || q -> type == T_SRV || q -> type == T_MX || q -> type == T_CNAME || q -> type == T_A ) {
 write_dns ( dns_fd , q , datap , datalen , 'V' ) ;
 return ;
 }
 break ;
 case 'R' : case 'r' : if ( q -> type == T_NULL || q -> type == T_TXT ) {
 write_dns ( dns_fd , q , datap , datalen , 'R' ) ;
 return ;
 }
 break ;
 }
 write_dns ( dns_fd , q , "BADCODEC" , 8 , 'T' ) ;
 return ;
 }
 else if ( in [ 0 ] == 'R' || in [ 0 ] == 'r' ) {
 int req_frag_size ;
 if ( domain_len < 16 ) {
 write_dns ( dns_fd , q , "BADLEN" , 6 , 'T' ) ;
 return ;
 }
 userid = ( b32_8to5 ( in [ 1 ] ) >> 1 ) & 15 ;
 if ( check_authenticated_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 return ;
 }
 req_frag_size = ( ( b32_8to5 ( in [ 1 ] ) & 1 ) << 10 ) | ( ( b32_8to5 ( in [ 2 ] ) & 31 ) << 5 ) | ( b32_8to5 ( in [ 3 ] ) & 31 ) ;
 if ( req_frag_size < 2 || req_frag_size > 2047 ) {
 write_dns ( dns_fd , q , "BADFRAG" , 7 , users [ userid ] . downenc ) ;
 }
 else {
 char buf [ 2048 ] ;
 int i ;
 unsigned int v = ( ( unsigned int ) rand ( ) ) & 0xff ;
 memset ( buf , 0 , sizeof ( buf ) ) ;
 buf [ 0 ] = ( req_frag_size >> 8 ) & 0xff ;
 buf [ 1 ] = req_frag_size & 0xff ;
 buf [ 2 ] = 107 ;
 for ( i = 3 ;
 i < 2048 ;
 i ++ , v = ( v + 107 ) & 0xff ) buf [ i ] = v ;
 write_dns ( dns_fd , q , buf , req_frag_size , users [ userid ] . downenc ) ;
 }
 return ;
 }
 else if ( in [ 0 ] == 'N' || in [ 0 ] == 'n' ) {
 int max_frag_size ;
 read = unpack_data ( unpacked , sizeof ( unpacked ) , & ( in [ 1 ] ) , domain_len - 1 , b32 ) ;
 if ( read < 3 ) {
 write_dns ( dns_fd , q , "BADLEN" , 6 , 'T' ) ;
 return ;
 }
 userid = unpacked [ 0 ] ;
 if ( check_authenticated_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 return ;
 }
 max_frag_size = ( ( unpacked [ 1 ] & 0xff ) << 8 ) | ( unpacked [ 2 ] & 0xff ) ;
 if ( max_frag_size < 2 ) {
 write_dns ( dns_fd , q , "BADFRAG" , 7 , users [ userid ] . downenc ) ;
 }
 else {
 users [ userid ] . fragsize = max_frag_size ;
 write_dns ( dns_fd , q , & unpacked [ 1 ] , 2 , users [ userid ] . downenc ) ;
 }
 return ;
 }
 else if ( in [ 0 ] == 'P' || in [ 0 ] == 'p' ) {
 int dn_seq ;
 int dn_frag ;
 int didsend = 0 ;
 if ( q -> id == 0 ) return ;
 read = unpack_data ( unpacked , sizeof ( unpacked ) , & ( in [ 1 ] ) , domain_len - 1 , b32 ) ;
 if ( read < 4 ) return ;
 userid = unpacked [ 0 ] ;
 if ( check_authenticated_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 return ;
 }


 if ( users [ userid ] . q . id != 0 && q -> type == users [ userid ] . q . type && ! strcmp ( q -> name , users [ userid ] . q . name ) && users [ userid ] . lazy ) {
 if ( debug >= 2 ) {
 fprintf ( stderr , "PING pkt from user %d = dupe from impatient DNS server, remembering\n" , userid ) ;
 }
 users [ userid ] . q . id2 = q -> id ;
 users [ userid ] . q . fromlen2 = q -> fromlen ;
 memcpy ( & ( users [ userid ] . q . from2 ) , & ( q -> from ) , q -> fromlen ) ;
 return ;
 }
 if ( users [ userid ] . q_sendrealsoon . id != 0 && q -> type == users [ userid ] . q_sendrealsoon . type && ! strcmp ( q -> name , users [ userid ] . q_sendrealsoon . name ) ) {
 if ( debug >= 2 ) {
 fprintf ( stderr , "PING pkt from user %d = dupe from impatient DNS server, remembering\n" , userid ) ;
 }
 users [ userid ] . q_sendrealsoon . id2 = q -> id ;
 users [ userid ] . q_sendrealsoon . fromlen2 = q -> fromlen ;
 memcpy ( & ( users [ userid ] . q_sendrealsoon . from2 ) , & ( q -> from ) , q -> fromlen ) ;
 return ;
 }
 dn_seq = unpacked [ 1 ] >> 4 ;
 dn_frag = unpacked [ 1 ] & 15 ;
 if ( debug >= 1 ) {
 fprintf ( stderr , "PING pkt from user %d, ack for downstream %d/%d\n" , userid , dn_seq , dn_frag ) ;
 }
 process_downstream_ack ( userid , dn_seq , dn_frag ) ;
 if ( debug >= 3 ) {
 fprintf ( stderr , "PINGret (if any) will ack upstream %d/%d\n" , users [ userid ] . inpacket . seqno , users [ userid ] . inpacket . fragment ) ;
 }
 if ( users [ userid ] . q_sendrealsoon . id != 0 ) {
 send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q_sendrealsoon ) ;
 }
 if ( users [ userid ] . q . id != 0 ) {
 didsend = 1 ;
 if ( send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q ) == 1 ) didsend = 0 ;
 }
 memcpy ( & ( users [ userid ] . q ) , q , sizeof ( struct query ) ) ;
 users [ userid ] . last_pkt = time ( NULL ) ;
 if ( ( ! didsend && users [ userid ] . outpacket . len > 0 ) || ! users [ userid ] . lazy ) send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q ) ;
 }
 else if ( ( in [ 0 ] >= '0' && in [ 0 ] <= '9' ) || ( in [ 0 ] >= 'a' && in [ 0 ] <= 'f' ) || ( in [ 0 ] >= 'A' && in [ 0 ] <= 'F' ) ) {
 int up_seq , up_frag , dn_seq , dn_frag , lastfrag ;
 int upstream_ok = 1 ;
 int didsend = 0 ;
 int code = - 1 ;
 if ( domain_len < 6 ) return ;
 if ( q -> id == 0 ) return ;
 if ( ( in [ 0 ] >= '0' && in [ 0 ] <= '9' ) ) code = in [ 0 ] - '0' ;
 if ( ( in [ 0 ] >= 'a' && in [ 0 ] <= 'f' ) ) code = in [ 0 ] - 'a' + 10 ;
 if ( ( in [ 0 ] >= 'A' && in [ 0 ] <= 'F' ) ) code = in [ 0 ] - 'A' + 10 ;
 userid = code ;
 if ( check_authenticated_user_and_ip ( userid , q ) != 0 ) {
 write_dns ( dns_fd , q , "BADIP" , 5 , 'T' ) ;
 return ;
 }


 if ( users [ userid ] . q . id != 0 && q -> type == users [ userid ] . q . type && ! strcmp ( q -> name , users [ userid ] . q . name ) && users [ userid ] . lazy ) {
 if ( debug >= 2 ) {
 fprintf ( stderr , "IN pkt from user %d = dupe from impatient DNS server, remembering\n" , userid ) ;
 }
 users [ userid ] . q . id2 = q -> id ;
 users [ userid ] . q . fromlen2 = q -> fromlen ;
 memcpy ( & ( users [ userid ] . q . from2 ) , & ( q -> from ) , q -> fromlen ) ;
 return ;
 }
 if ( users [ userid ] . q_sendrealsoon . id != 0 && q -> type == users [ userid ] . q_sendrealsoon . type && ! strcmp ( q -> name , users [ userid ] . q_sendrealsoon . name ) ) {
 if ( debug >= 2 ) {
 fprintf ( stderr , "IN pkt from user %d = dupe from impatient DNS server, remembering\n" , userid ) ;
 }
 users [ userid ] . q_sendrealsoon . id2 = q -> id ;
 users [ userid ] . q_sendrealsoon . fromlen2 = q -> fromlen ;
 memcpy ( & ( users [ userid ] . q_sendrealsoon . from2 ) , & ( q -> from ) , q -> fromlen ) ;
 return ;
 }
 up_seq = ( b32_8to5 ( in [ 1 ] ) >> 2 ) & 7 ;
 up_frag = ( ( b32_8to5 ( in [ 1 ] ) & 3 ) << 2 ) | ( ( b32_8to5 ( in [ 2 ] ) >> 3 ) & 3 ) ;
 dn_seq = ( b32_8to5 ( in [ 2 ] ) & 7 ) ;
 dn_frag = b32_8to5 ( in [ 3 ] ) >> 1 ;
 lastfrag = b32_8to5 ( in [ 3 ] ) & 1 ;
 process_downstream_ack ( userid , dn_seq , dn_frag ) ;
 if ( up_seq == users [ userid ] . inpacket . seqno && up_frag <= users [ userid ] . inpacket . fragment ) {
 if ( debug >= 1 ) {
 fprintf ( stderr , "IN pkt seq# %d, frag %d, dropped duplicate frag\n" , up_seq , up_frag ) ;
 }
 upstream_ok = 0 ;
 }
 else if ( up_seq != users [ userid ] . inpacket . seqno && recent_seqno ( users [ userid ] . inpacket . seqno , up_seq ) ) {
 if ( debug >= 1 ) {
 fprintf ( stderr , "IN pkt seq# %d, frag %d, dropped duplicate recent seqno\n" , up_seq , up_frag ) ;
 }
 upstream_ok = 0 ;
 }
 else if ( up_seq != users [ userid ] . inpacket . seqno ) {
 users [ userid ] . inpacket . seqno = up_seq ;
 users [ userid ] . inpacket . fragment = up_frag ;
 users [ userid ] . inpacket . len = 0 ;
 users [ userid ] . inpacket . offset = 0 ;
 }
 else {
 users [ userid ] . inpacket . fragment = up_frag ;
 }
 if ( debug >= 3 ) {
 fprintf ( stderr , "INpack with upstream %d/%d, we are going to ack upstream %d/%d\n" , up_seq , up_frag , users [ userid ] . inpacket . seqno , users [ userid ] . inpacket . fragment ) ;
 }
 if ( upstream_ok ) {
 read = unpack_data ( unpacked , sizeof ( unpacked ) , & ( in [ 5 ] ) , domain_len - 5 , users [ userid ] . encoder ) ;
 read = MIN ( read , sizeof ( users [ userid ] . inpacket . data ) - users [ userid ] . inpacket . offset ) ;
 memcpy ( users [ userid ] . inpacket . data + users [ userid ] . inpacket . offset , unpacked , read ) ;
 users [ userid ] . inpacket . len += read ;
 users [ userid ] . inpacket . offset += read ;
 if ( debug >= 1 ) {
 fprintf ( stderr , "IN pkt seq# %d, frag %d (last=%d), fragsize %d, total %d, from user %d\n" , up_seq , up_frag , lastfrag , read , users [ userid ] . inpacket . len , userid ) ;
 }
 }
 if ( upstream_ok && lastfrag ) {
 handle_full_packet ( tun_fd , dns_fd , userid ) ;
 }
 if ( users [ userid ] . q_sendrealsoon . id != 0 ) {
 didsend = 1 ;
 if ( send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q_sendrealsoon ) == 1 ) didsend = 0 ;
 }
 if ( users [ userid ] . q . id != 0 ) {
 if ( ( users [ userid ] . outpacket . len > 0 && ! didsend ) || ( upstream_ok && ! lastfrag && ! didsend ) || ( ! upstream_ok && ! didsend ) || ! users [ userid ] . lazy ) {
 didsend = 1 ;
 if ( send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q ) == 1 ) didsend = 0 ;
 }
 else {
 memcpy ( & ( users [ userid ] . q_sendrealsoon ) , & ( users [ userid ] . q ) , sizeof ( struct query ) ) ;
 users [ userid ] . q_sendrealsoon_new = 1 ;
 users [ userid ] . q . id = 0 ;
 didsend = 1 ;
 }
 }
 memcpy ( & ( users [ userid ] . q ) , q , sizeof ( struct query ) ) ;
 users [ userid ] . last_pkt = time ( NULL ) ;
 if ( users [ userid ] . outpacket . len > 0 && ! didsend ) send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q ) ;
 else if ( ! didsend || ! users [ userid ] . lazy ) {
 if ( upstream_ok && lastfrag ) {
 memcpy ( & ( users [ userid ] . q_sendrealsoon ) , & ( users [ userid ] . q ) , sizeof ( struct query ) ) ;
 users [ userid ] . q_sendrealsoon_new = 1 ;
 users [ userid ] . q . id = 0 ;
 }
 else {
 send_chunk_or_dataless ( dns_fd , userid , & users [ userid ] . q ) ;
 }
 }
 }
 }