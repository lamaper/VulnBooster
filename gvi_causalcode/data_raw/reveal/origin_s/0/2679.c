static __inline__ int icmpv6_filter ( struct sock * sk , struct sk_buff * skb ) {
 struct icmp6hdr * icmph ;
 struct raw6_sock * rp = raw6_sk ( sk ) ;
 if ( pskb_may_pull ( skb , sizeof ( struct icmp6hdr ) ) ) {
 __u32 * data = & rp -> filter . data [ 0 ] ;
 int bit_nr ;
 icmph = ( struct icmp6hdr * ) skb -> data ;
 bit_nr = icmph -> icmp6_type ;
 return ( data [ bit_nr >> 5 ] & ( 1 << ( bit_nr & 31 ) ) ) != 0 ;
 }
 return 0 ;
 }