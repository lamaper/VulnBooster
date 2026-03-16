static void fake_freeaddrinfo ( struct addrinfo * ai ) {
 free ( ai -> ai_addr ) ;
 }