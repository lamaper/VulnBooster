static int rawv6_send_hdrinc ( struct sock * sk , void * from , int length , struct flowi * fl , struct rt6_info * rt , unsigned int flags ) {
 struct ipv6_pinfo * np = inet6_sk ( sk ) ;
 struct ipv6hdr * iph ;
 struct sk_buff * skb ;
 int err ;
 if ( length > rt -> u . dst . dev -> mtu ) {
 ipv6_local_error ( sk , EMSGSIZE , fl , rt -> u . dst . dev -> mtu ) ;
 return - EMSGSIZE ;
 }
 if ( flags & MSG_PROBE ) goto out ;
 skb = sock_alloc_send_skb ( sk , length + LL_ALLOCATED_SPACE ( rt -> u . dst . dev ) + 15 , flags & MSG_DONTWAIT , & err ) ;
 if ( skb == NULL ) goto error ;
 skb_reserve ( skb , LL_RESERVED_SPACE ( rt -> u . dst . dev ) ) ;
 skb -> priority = sk -> sk_priority ;
 skb -> mark = sk -> sk_mark ;
 skb_dst_set ( skb , dst_clone ( & rt -> u . dst ) ) ;
 skb_put ( skb , length ) ;
 skb_reset_network_header ( skb ) ;
 iph = ipv6_hdr ( skb ) ;
 skb -> ip_summed = CHECKSUM_NONE ;
 skb -> transport_header = skb -> network_header ;
 err = memcpy_fromiovecend ( ( void * ) iph , from , 0 , length ) ;
 if ( err ) goto error_fault ;
 IP6_UPD_PO_STATS ( sock_net ( sk ) , rt -> rt6i_idev , IPSTATS_MIB_OUT , skb -> len ) ;
 err = NF_HOOK ( PF_INET6 , NF_INET_LOCAL_OUT , skb , NULL , rt -> u . dst . dev , dst_output ) ;
 if ( err > 0 ) err = net_xmit_errno ( err ) ;
 if ( err ) goto error ;
 out : return 0 ;
 error_fault : err = - EFAULT ;
 kfree_skb ( skb ) ;
 error : IP6_INC_STATS ( sock_net ( sk ) , rt -> rt6i_idev , IPSTATS_MIB_OUTDISCARDS ) ;
 if ( err == - ENOBUFS && ! np -> recverr ) err = 0 ;
 return err ;
 }