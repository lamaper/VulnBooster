static void selinux_inet_conn_established ( struct sock * sk , struct sk_buff * skb ) {
 u16 family = sk -> sk_family ;
 struct sk_security_struct * sksec = sk -> sk_security ;
 if ( family == PF_INET6 && skb -> protocol == htons ( ETH_P_IP ) ) family = PF_INET ;
 selinux_skb_peerlbl_sid ( skb , family , & sksec -> peer_sid ) ;
 }