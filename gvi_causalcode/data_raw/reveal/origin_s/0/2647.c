static int selinux_tun_dev_attach ( struct sock * sk , void * security ) {
 struct tun_security_struct * tunsec = security ;
 struct sk_security_struct * sksec = sk -> sk_security ;
 sksec -> sid = tunsec -> sid ;
 sksec -> sclass = SECCLASS_TUN_SOCKET ;
 return 0 ;
 }