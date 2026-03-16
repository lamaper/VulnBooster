TEST_F ( TransportSecurityPersisterTest , SerializeData2 ) {
 TransportSecurityState : : DomainState domain_state ;
 const base : : Time current_time ( base : : Time : : Now ( ) ) ;
 const base : : Time expiry = current_time + base : : TimeDelta : : FromSeconds ( 1000 ) ;
 static const char kYahooDomain [ ] = "yahoo.com" ;
 EXPECT_FALSE ( state_ . GetStaticDomainState ( kYahooDomain , true , & domain_state ) ) ;
 EXPECT_FALSE ( state_ . GetDynamicDomainState ( kYahooDomain , & domain_state ) ) ;
 bool include_subdomains = true ;
 state_ . AddHSTS ( kYahooDomain , expiry , include_subdomains ) ;
 std : : string output ;
 bool dirty ;
 EXPECT_TRUE ( persister_ -> SerializeData ( & output ) ) ;
 EXPECT_TRUE ( persister_ -> LoadEntries ( output , & dirty ) ) ;
 EXPECT_TRUE ( state_ . GetDynamicDomainState ( kYahooDomain , & domain_state ) ) ;
 EXPECT_EQ ( domain_state . sts . upgrade_mode , TransportSecurityState : : DomainState : : MODE_FORCE_HTTPS ) ;
 EXPECT_TRUE ( state_ . GetDynamicDomainState ( "foo.yahoo.com" , & domain_state ) ) ;
 EXPECT_EQ ( domain_state . sts . upgrade_mode , TransportSecurityState : : DomainState : : MODE_FORCE_HTTPS ) ;
 EXPECT_TRUE ( state_ . GetDynamicDomainState ( "foo.bar.yahoo.com" , & domain_state ) ) ;
 EXPECT_EQ ( domain_state . sts . upgrade_mode , TransportSecurityState : : DomainState : : MODE_FORCE_HTTPS ) ;
 EXPECT_TRUE ( state_ . GetDynamicDomainState ( "foo.bar.baz.yahoo.com" , & domain_state ) ) ;
 EXPECT_EQ ( domain_state . sts . upgrade_mode , TransportSecurityState : : DomainState : : MODE_FORCE_HTTPS ) ;
 EXPECT_FALSE ( state_ . GetStaticDomainState ( "com" , true , & domain_state ) ) ;
 }