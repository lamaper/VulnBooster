static inline int sk_mc_loop ( struct sock * sk ) {
 if ( ! sk ) return 1 ;
 switch ( sk -> sk_family ) {
 case AF_INET : return inet_sk ( sk ) -> mc_loop ;


 WARN_ON ( 1 ) ;
 return 1 ;
 }