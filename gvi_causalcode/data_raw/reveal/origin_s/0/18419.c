static int ipv6_raw_deliver ( struct sk_buff * skb , int nexthdr ) {
 struct in6_addr * saddr ;
 struct in6_addr * daddr ;
 struct sock * sk ;
 int delivered = 0 ;
 __u8 hash ;
 struct net * net ;
 saddr = & ipv6_hdr ( skb ) -> saddr ;
 daddr = saddr + 1 ;
 hash = nexthdr & ( MAX_INET_PROTOS - 1 ) ;
 read_lock ( & raw_v6_hashinfo . lock ) ;
 sk = sk_head ( & raw_v6_hashinfo . ht [ hash ] ) ;
 if ( sk == NULL ) goto out ;
 net = dev_net ( skb -> dev ) ;
 sk = __raw_v6_lookup ( net , sk , nexthdr , daddr , saddr , IP6CB ( skb ) -> iif ) ;
 while ( sk ) {
 int filtered ;
 delivered = 1 ;
 switch ( nexthdr ) {
 case IPPROTO_ICMPV6 : filtered = icmpv6_filter ( sk , skb ) ;
 break ;

 int ( * filter ) ( struct sock * sock , struct sk_buff * skb ) ;
 filter = rcu_dereference ( mh_filter ) ;
 filtered = filter ? filter ( sk , skb ) : 0 ;
 break ;
 }

 break ;
 }
 if ( filtered < 0 ) break ;
 if ( filtered == 0 ) {
 struct sk_buff * clone = skb_clone ( skb , GFP_ATOMIC ) ;
 if ( clone ) {
 nf_reset ( clone ) ;
 rawv6_rcv ( sk , clone ) ;
 }
 }
 sk = __raw_v6_lookup ( net , sk_next ( sk ) , nexthdr , daddr , saddr , IP6CB ( skb ) -> iif ) ;
 }
 out : read_unlock ( & raw_v6_hashinfo . lock ) ;
 return delivered ;
 }