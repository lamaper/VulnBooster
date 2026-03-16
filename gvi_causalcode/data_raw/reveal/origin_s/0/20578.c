static void selinux_inet_csk_clone ( struct sock * newsk , const struct request_sock * req ) {
 struct sk_security_struct * newsksec = newsk -> sk_security ;
 newsksec -> sid = req -> secid ;
 newsksec -> peer_sid = req -> peer_secid ;
 selinux_netlbl_inet_csk_clone ( newsk , req -> rsk_ops -> family ) ;
 }