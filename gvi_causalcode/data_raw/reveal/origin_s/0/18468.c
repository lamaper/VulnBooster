static void pcnet_rdte_poll ( PCNetState * s ) {
 s -> csr [ 28 ] = s -> csr [ 29 ] = 0 ;
 if ( s -> rdra ) {
 int bad = 0 ;

 hwaddr nrda = pcnet_rdra_addr ( s , - 1 + CSR_RCVRC ( s ) ) ;
 hwaddr nnrd = pcnet_rdra_addr ( s , - 2 + CSR_RCVRC ( s ) ) ;

 int nrdc = CSR_RCVRC ( s ) <= 1 ? CSR_RCVRL ( s ) : CSR_RCVRC ( s ) - 1 ;
 hwaddr nrda = s -> rdra + ( CSR_RCVRL ( s ) - nrdc ) * ( BCR_SWSTYLE ( s ) ? 16 : 8 ) ;
 int nnrc = nrdc <= 1 ? CSR_RCVRL ( s ) : nrdc - 1 ;
 hwaddr nnrd = s -> rdra + ( CSR_RCVRL ( s ) - nnrc ) * ( BCR_SWSTYLE ( s ) ? 16 : 8 ) ;

 if ( ! bad ) {
 CHECK_RMD ( nrda , bad ) ;
 if ( bad || ( nrda == crda ) ) nrda = 0 ;
 CHECK_RMD ( nnrd , bad ) ;
 if ( bad || ( nnrd == crda ) ) nnrd = 0 ;
 s -> csr [ 28 ] = crda & 0xffff ;
 s -> csr [ 29 ] = crda >> 16 ;
 s -> csr [ 26 ] = nrda & 0xffff ;
 s -> csr [ 27 ] = nrda >> 16 ;
 s -> csr [ 36 ] = nnrd & 0xffff ;
 s -> csr [ 37 ] = nnrd >> 16 ;

 printf ( "pcnet: BAD RMD RECORDS AFTER 0x" TARGET_FMT_plx "\n" , crda ) ;
 }
 }
 else {
 printf ( "pcnet: BAD RMD RDA=0x" TARGET_FMT_plx "\n" , crda ) ;

 }
 if ( CSR_CRDA ( s ) ) {
 struct pcnet_RMD rmd ;
 RMDLOAD ( & rmd , PHYSADDR ( s , CSR_CRDA ( s ) ) ) ;
 CSR_CRBC ( s ) = GET_FIELD ( rmd . buf_length , RMDL , BCNT ) ;
 CSR_CRST ( s ) = rmd . status ;

 PRINT_RMD ( & rmd ) ;

 else {
 CSR_CRBC ( s ) = CSR_CRST ( s ) = 0 ;
 }
 if ( CSR_NRDA ( s ) ) {
 struct pcnet_RMD rmd ;
 RMDLOAD ( & rmd , PHYSADDR ( s , CSR_NRDA ( s ) ) ) ;
 CSR_NRBC ( s ) = GET_FIELD ( rmd . buf_length , RMDL , BCNT ) ;
 CSR_NRST ( s ) = rmd . status ;
 }
 else {
 CSR_NRBC ( s ) = CSR_NRST ( s ) = 0 ;
 }
 }