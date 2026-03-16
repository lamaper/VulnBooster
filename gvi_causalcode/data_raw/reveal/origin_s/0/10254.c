TEST_F ( TransportSecurityPersisterTest , SerializeData3 ) {
 net : : HashValue fp1 ( net : : HASH_VALUE_SHA1 ) ;
 memset ( fp1 . data ( ) , 0 , fp1 . size ( ) ) ;
 net : : HashValue fp2 ( net : : HASH_VALUE_SHA1 ) ;
 memset ( fp2 . data ( ) , 1 , fp2 . size ( ) ) ;
 base : : Time expiry = base : : Time : : Now ( ) + base : : TimeDelta : : FromSeconds ( 1000 ) ;
 net : : HashValueVector dynamic_spki_hashes ;
 dynamic_spki_hashes . push_back ( fp1 ) ;
 dynamic_spki_hashes . push_back ( fp2 ) ;
 bool include_subdomains = false ;
 state_ . AddHSTS ( "www.example.com" , expiry , include_subdomains ) ;
 state_ . AddHPKP ( "www.example.com" , expiry , include_subdomains , dynamic_spki_hashes ) ;
 memset ( fp1 . data ( ) , 2 , fp1 . size ( ) ) ;
 memset ( fp2 . data ( ) , 3 , fp2 . size ( ) ) ;
 expiry = base : : Time : : Now ( ) + base : : TimeDelta : : FromSeconds ( 3000 ) ;
 dynamic_spki_hashes . push_back ( fp1 ) ;
 dynamic_spki_hashes . push_back ( fp2 ) ;
 state_ . AddHSTS ( "www.example.net" , expiry , include_subdomains ) ;
 state_ . AddHPKP ( "www.example.net" , expiry , include_subdomains , dynamic_spki_hashes ) ;
 std : : map < std : : string , TransportSecurityState : : DomainState > saved ;
 TransportSecurityState : : Iterator i ( state_ ) ;
 while ( i . HasNext ( ) ) {
 saved [ i . hostname ( ) ] = i . domain_state ( ) ;
 i . Advance ( ) ;
 }
 std : : string serialized ;
 EXPECT_TRUE ( persister_ -> SerializeData ( & serialized ) ) ;
 base : : FilePath path = temp_dir_ . path ( ) . AppendASCII ( "TransportSecurityPersisterTest" ) ;
 EXPECT_TRUE ( base : : WriteFile ( path , serialized . c_str ( ) , serialized . size ( ) ) ) ;
 std : : string persisted ;
 EXPECT_TRUE ( base : : ReadFileToString ( path , & persisted ) ) ;
 EXPECT_EQ ( persisted , serialized ) ;
 bool dirty ;
 EXPECT_TRUE ( persister_ -> LoadEntries ( persisted , & dirty ) ) ;
 EXPECT_FALSE ( dirty ) ;
 size_t count = 0 ;
 TransportSecurityState : : Iterator j ( state_ ) ;
 while ( j . HasNext ( ) ) {
 count ++ ;
 j . Advance ( ) ;
 }
 EXPECT_EQ ( count , saved . size ( ) ) ;
 }