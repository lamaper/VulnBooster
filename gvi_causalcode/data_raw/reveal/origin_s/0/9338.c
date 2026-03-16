static char * fieldflags2str ( uint f ) {
 static char buf [ 1024 ] ;
 char * s = buf ;
 * s = 0 ;

 s = strmov ( s , # X " " ) ;
 f &= ~ X ## _FLAG ;
 }
 ff2s_check_flag ( NOT_NULL ) ;
 ff2s_check_flag ( PRI_KEY ) ;
 ff2s_check_flag ( UNIQUE_KEY ) ;
 ff2s_check_flag ( MULTIPLE_KEY ) ;
 ff2s_check_flag ( BLOB ) ;
 ff2s_check_flag ( UNSIGNED ) ;
 ff2s_check_flag ( ZEROFILL ) ;
 ff2s_check_flag ( BINARY ) ;
 ff2s_check_flag ( ENUM ) ;
 ff2s_check_flag ( AUTO_INCREMENT ) ;
 ff2s_check_flag ( TIMESTAMP ) ;
 ff2s_check_flag ( SET ) ;
 ff2s_check_flag ( NO_DEFAULT_VALUE ) ;
 ff2s_check_flag ( NUM ) ;
 ff2s_check_flag ( PART_KEY ) ;
 ff2s_check_flag ( GROUP ) ;
 ff2s_check_flag ( UNIQUE ) ;
 ff2s_check_flag ( BINCMP ) ;
 ff2s_check_flag ( ON_UPDATE_NOW ) ;

 return buf ;
 }