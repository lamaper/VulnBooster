inline static void update_dns_info ( HttpTransact : : DNSLookupInfo * dns , HttpTransact : : CurrentInfo * from , int attempts , Arena * ) {
 dns -> looking_up = from -> request_to ;
 dns -> lookup_name = from -> server -> name ;
 dns -> attempts = attempts ;
 }