static const char * calc_ip ( const char * ip , long * val , char end ) {
 long ip_val , tmp ;
 if ( ! ( ip = str2int ( ip , 10 , 0 , 255 , & ip_val ) ) || * ip != '.' ) return 0 ;
 ip_val <<= 24 ;
 if ( ! ( ip = str2int ( ip + 1 , 10 , 0 , 255 , & tmp ) ) || * ip != '.' ) return 0 ;
 ip_val += tmp << 16 ;
 if ( ! ( ip = str2int ( ip + 1 , 10 , 0 , 255 , & tmp ) ) || * ip != '.' ) return 0 ;
 ip_val += tmp << 8 ;
 if ( ! ( ip = str2int ( ip + 1 , 10 , 0 , 255 , & tmp ) ) || * ip != end ) return 0 ;
 * val = ip_val + tmp ;
 return ip ;
 }