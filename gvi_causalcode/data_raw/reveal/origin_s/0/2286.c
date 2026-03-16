static void usage ( ) {
 extern char * __progname ;
 fprintf ( stderr , "Usage: %s [-v] [-h] [-c] [-s] [-f] [-D] [-u user] " "[-t chrootdir] [-d device] [-m mtu] [-z context] " "[-l ip address to listen on] [-p port] [-n external ip] " "[-b dnsport] [-P password] [-F pidfile] [-i max idle time] " "tunnel_ip[etmask] topdomain\n" , __progname ) ;
 exit ( 2 ) ;
 }