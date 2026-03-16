TEST_F ( TransportSecurityPersisterTest , PublicKeyHashes ) {
 TransportSecurityState : : DomainState domain_state ;
 static const char kTestDomain [ ] = "example.com" ;
 EXPECT_FALSE ( state_ . GetDomainState ( kTestDomain , false , & domain_state ) ) ;
 net : : HashValueVector hashes ;
 std : : string failure_log ;
 EXPECT_FALSE ( domain_state . CheckPublicKeyPins ( hashes , & failure_log ) ) ;
 net : : HashValue sha1 ( net : : HASH_VALUE_SHA1 ) ;
 memset ( sha1 . data ( ) , '1' , sha1 . size ( ) ) ;
 domain_state . dynamic_spki_hashes . push_back ( sha1 ) ;
 EXPECT_FALSE ( domain_state . CheckPublicKeyPins ( hashes , & failure_log ) ) ;
 hashes . push_back ( sha1 ) ;
 EXPECT_TRUE ( domain_state . CheckPublicKeyPins ( hashes , & failure_log ) ) ;
 hashes [ 0 ] . data ( ) [ 0 ] = '2' ;
 EXPECT_FALSE ( domain_state . CheckPublicKeyPins ( hashes , & failure_log ) ) ;
 const base : : Time current_time ( base : : Time : : Now ( ) ) ;
 const base : : Time expiry = current_time + base : : TimeDelta : : FromSeconds ( 1000 ) ;
 bool include_subdomains = false ;
 state_ . AddHSTS ( kTestDomain , expiry , include_subdomains ) ;
 state_ . AddHPKP ( kTestDomain , expiry , include_subdomains , domain_state . dynamic_spki_hashes ) ;
 std : : string ser ;
 EXPECT_TRUE ( persister_ -> SerializeData ( & ser ) ) ;
 bool dirty ;
 EXPECT_TRUE ( persister_ -> LoadEntries ( ser , & dirty ) ) ;
 EXPECT_TRUE ( state_ . GetDomainState ( kTestDomain , false , & domain_state ) ) ;
 EXPECT_EQ ( 1u , domain_state . dynamic_spki_hashes . size ( ) ) ;
 EXPECT_EQ ( sha1 . tag , domain_state . dynamic_spki_hashes [ 0 ] . tag ) ;
 EXPECT_EQ ( 0 , memcmp ( domain_state . dynamic_spki_hashes [ 0 ] . data ( ) , sha1 . data ( ) , sha1 . size ( ) ) ) ;
 }