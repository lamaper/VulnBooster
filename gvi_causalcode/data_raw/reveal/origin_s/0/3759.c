static struct sock * __raw_v6_lookup ( struct net * net , struct sock * sk , unsigned short num , struct in6_addr * loc_addr , struct in6_addr * rmt_addr , int dif ) {
 struct hlist_node * node ;
 int is_multicast = ipv6_addr_is_multicast ( loc_addr ) ;
 sk_for_each_from ( sk , node ) if ( inet_sk ( sk ) -> inet_num == num ) {
 struct ipv6_pinfo * np = inet6_sk ( sk ) ;
 if ( ! net_eq ( sock_net ( sk ) , net ) ) continue ;
 if ( ! ipv6_addr_any ( & np -> daddr ) && ! ipv6_addr_equal ( & np -> daddr , rmt_addr ) ) continue ;
 if ( sk -> sk_bound_dev_if && sk -> sk_bound_dev_if != dif ) continue ;
 if ( ! ipv6_addr_any ( & np -> rcv_saddr ) ) {
 if ( ipv6_addr_equal ( & np -> rcv_saddr , loc_addr ) ) goto found ;
 if ( is_multicast && inet6_mc_check ( sk , loc_addr , rmt_addr ) ) goto found ;
 continue ;
 }
 goto found ;
 }
 sk = NULL ;
 found : return sk ;
 }