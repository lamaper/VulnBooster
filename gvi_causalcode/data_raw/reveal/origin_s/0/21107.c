static int rawv6_sendmsg ( struct kiocb * iocb , struct sock * sk , struct msghdr * msg , size_t len ) {
 struct ipv6_txoptions opt_space ;
 struct sockaddr_in6 * sin6 = ( struct sockaddr_in6 * ) msg -> msg_name ;
 struct in6_addr * daddr , * final_p = NULL , final ;
 struct inet_sock * inet = inet_sk ( sk ) ;
 struct ipv6_pinfo * np = inet6_sk ( sk ) ;
 struct raw6_sock * rp = raw6_sk ( sk ) ;
 struct ipv6_txoptions * opt = NULL ;
 struct ip6_flowlabel * flowlabel = NULL ;
 struct dst_entry * dst = NULL ;
 struct flowi fl ;
 int addr_len = msg -> msg_namelen ;
 int hlimit = - 1 ;
 int tclass = - 1 ;
 int dontfrag = - 1 ;
 u16 proto ;
 int err ;
 if ( len > INT_MAX ) return - EMSGSIZE ;
 if ( msg -> msg_flags & MSG_OOB ) return - EOPNOTSUPP ;
 memset ( & fl , 0 , sizeof ( fl ) ) ;
 fl . mark = sk -> sk_mark ;
 if ( sin6 ) {
 if ( addr_len < SIN6_LEN_RFC2133 ) return - EINVAL ;
 if ( sin6 -> sin6_family && sin6 -> sin6_family != AF_INET6 ) return ( - EAFNOSUPPORT ) ;
 proto = ntohs ( sin6 -> sin6_port ) ;
 if ( ! proto ) proto = inet -> inet_num ;
 else if ( proto != inet -> inet_num ) return ( - EINVAL ) ;
 if ( proto > 255 ) return ( - EINVAL ) ;
 daddr = & sin6 -> sin6_addr ;
 if ( np -> sndflow ) {
 fl . fl6_flowlabel = sin6 -> sin6_flowinfo & IPV6_FLOWINFO_MASK ;
 if ( fl . fl6_flowlabel & IPV6_FLOWLABEL_MASK ) {
 flowlabel = fl6_sock_lookup ( sk , fl . fl6_flowlabel ) ;
 if ( flowlabel == NULL ) return - EINVAL ;
 daddr = & flowlabel -> dst ;
 }
 }
 if ( sk -> sk_state == TCP_ESTABLISHED && ipv6_addr_equal ( daddr , & np -> daddr ) ) daddr = & np -> daddr ;
 if ( addr_len >= sizeof ( struct sockaddr_in6 ) && sin6 -> sin6_scope_id && ipv6_addr_type ( daddr ) & IPV6_ADDR_LINKLOCAL ) fl . oif = sin6 -> sin6_scope_id ;
 }
 else {
 if ( sk -> sk_state != TCP_ESTABLISHED ) return - EDESTADDRREQ ;
 proto = inet -> inet_num ;
 daddr = & np -> daddr ;
 fl . fl6_flowlabel = np -> flow_label ;
 }
 if ( fl . oif == 0 ) fl . oif = sk -> sk_bound_dev_if ;
 if ( msg -> msg_controllen ) {
 opt = & opt_space ;
 memset ( opt , 0 , sizeof ( struct ipv6_txoptions ) ) ;
 opt -> tot_len = sizeof ( struct ipv6_txoptions ) ;
 err = datagram_send_ctl ( sock_net ( sk ) , msg , & fl , opt , & hlimit , & tclass , & dontfrag ) ;
 if ( err < 0 ) {
 fl6_sock_release ( flowlabel ) ;
 return err ;
 }
 if ( ( fl . fl6_flowlabel & IPV6_FLOWLABEL_MASK ) && ! flowlabel ) {
 flowlabel = fl6_sock_lookup ( sk , fl . fl6_flowlabel ) ;
 if ( flowlabel == NULL ) return - EINVAL ;
 }
 if ( ! ( opt -> opt_nflen | opt -> opt_flen ) ) opt = NULL ;
 }
 if ( opt == NULL ) opt = np -> opt ;
 if ( flowlabel ) opt = fl6_merge_options ( & opt_space , flowlabel , opt ) ;
 opt = ipv6_fixup_options ( & opt_space , opt ) ;
 fl . proto = proto ;
 err = rawv6_probe_proto_opt ( & fl , msg ) ;
 if ( err ) goto out ;
 if ( ! ipv6_addr_any ( daddr ) ) ipv6_addr_copy ( & fl . fl6_dst , daddr ) ;
 else fl . fl6_dst . s6_addr [ 15 ] = 0x1 ;
 if ( ipv6_addr_any ( & fl . fl6_src ) && ! ipv6_addr_any ( & np -> saddr ) ) ipv6_addr_copy ( & fl . fl6_src , & np -> saddr ) ;
 if ( opt && opt -> srcrt ) {
 struct rt0_hdr * rt0 = ( struct rt0_hdr * ) opt -> srcrt ;
 ipv6_addr_copy ( & final , & fl . fl6_dst ) ;
 ipv6_addr_copy ( & fl . fl6_dst , rt0 -> addr ) ;
 final_p = & final ;
 }
 if ( ! fl . oif && ipv6_addr_is_multicast ( & fl . fl6_dst ) ) fl . oif = np -> mcast_oif ;
 security_sk_classify_flow ( sk , & fl ) ;
 err = ip6_dst_lookup ( sk , & dst , & fl ) ;
 if ( err ) goto out ;
 if ( final_p ) ipv6_addr_copy ( & fl . fl6_dst , final_p ) ;
 err = __xfrm_lookup ( sock_net ( sk ) , & dst , & fl , sk , XFRM_LOOKUP_WAIT ) ;
 if ( err < 0 ) {
 if ( err == - EREMOTE ) err = ip6_dst_blackhole ( sk , & dst , & fl ) ;
 if ( err < 0 ) goto out ;
 }
 if ( hlimit < 0 ) {
 if ( ipv6_addr_is_multicast ( & fl . fl6_dst ) ) hlimit = np -> mcast_hops ;
 else hlimit = np -> hop_limit ;
 if ( hlimit < 0 ) hlimit = ip6_dst_hoplimit ( dst ) ;
 }
 if ( tclass < 0 ) tclass = np -> tclass ;
 if ( dontfrag < 0 ) dontfrag = np -> dontfrag ;
 if ( msg -> msg_flags & MSG_CONFIRM ) goto do_confirm ;
 back_from_confirm : if ( inet -> hdrincl ) {
 err = rawv6_send_hdrinc ( sk , msg -> msg_iov , len , & fl , ( struct rt6_info * ) dst , msg -> msg_flags ) ;
 }
 else {
 lock_sock ( sk ) ;
 err = ip6_append_data ( sk , ip_generic_getfrag , msg -> msg_iov , len , 0 , hlimit , tclass , opt , & fl , ( struct rt6_info * ) dst , msg -> msg_flags , dontfrag ) ;
 if ( err ) ip6_flush_pending_frames ( sk ) ;
 else if ( ! ( msg -> msg_flags & MSG_MORE ) ) err = rawv6_push_pending_frames ( sk , & fl , rp ) ;
 release_sock ( sk ) ;
 }
 done : dst_release ( dst ) ;
 out : fl6_sock_release ( flowlabel ) ;
 return err < 0 ? err : len ;
 do_confirm : dst_confirm ( dst ) ;
 if ( ! ( msg -> msg_flags & MSG_PROBE ) || len ) goto back_from_confirm ;
 err = 0 ;
 goto done ;
 }