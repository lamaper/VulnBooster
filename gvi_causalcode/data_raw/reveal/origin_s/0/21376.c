static void help ( ) {
 extern char * __progname ;
 fprintf ( stderr , "iodine IP over DNS tunneling server\n" ) ;
 fprintf ( stderr , "Usage: %s [-v] [-h] [-c] [-s] [-f] [-D] [-u user] " "[-t chrootdir] [-d device] [-m mtu] [-z context] " "[-l ip address to listen on] [-p port] [-n external ip] [-b dnsport] [-P password] " "[-F pidfile] tunnel_ip[etmask] topdomain\n" , __progname ) ;
 fprintf ( stderr , " -v to print version info and exit\n" ) ;
 fprintf ( stderr , " -h to print this help and exit\n" ) ;
 fprintf ( stderr , " -c to disable check of client IP/port on each request\n" ) ;
 fprintf ( stderr , " -s to skip creating and configuring the tun device, " "which then has to be created manually\n" ) ;
 fprintf ( stderr , " -f to keep running in foreground\n" ) ;
 fprintf ( stderr , " -D to increase debug level\n" ) ;
 fprintf ( stderr , " (using -DD in UTF-8 terminal: \"LC_ALL=C luit iodined -DD ...\")\n" ) ;
 fprintf ( stderr , " -u name to drop privileges and run as user 'name'\n" ) ;
 fprintf ( stderr , " -t dir to chroot to directory dir\n" ) ;
 fprintf ( stderr , " -d device to set tunnel device name\n" ) ;
 fprintf ( stderr , " -m mtu to set tunnel device mtu\n" ) ;
 fprintf ( stderr , " -z context to apply SELinux context after initialization\n" ) ;
 fprintf ( stderr , " -l ip address to listen on for incoming dns traffic " "(default 0.0.0.0)\n" ) ;
 fprintf ( stderr , " -p port to listen on for incoming dns traffic (default 53)\n" ) ;
 fprintf ( stderr , " -n ip to respond with to NS queries\n" ) ;
 fprintf ( stderr , " -b port to forward normal DNS queries to (on localhost)\n" ) ;
 fprintf ( stderr , " -P password used for authentication (max 32 chars will be used)\n" ) ;
 fprintf ( stderr , " -F pidfile to write pid to a file\n" ) ;
 fprintf ( stderr , " -i maximum idle time before shutting down\n" ) ;
 fprintf ( stderr , "tunnel_ip is the IP number of the local tunnel interface.\n" ) ;
 fprintf ( stderr , " etmask sets the size of the tunnel network.\n" ) ;
 fprintf ( stderr , "topdomain is the FQDN that is delegated to this server.\n" ) ;
 exit ( 0 ) ;
 }