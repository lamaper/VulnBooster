TEST ( WinUtils , SameObject ) {
 using sandbox : : SameObject ;
 wchar_t temp_directory [ MAX_PATH ] ;
 wchar_t my_folder [ MAX_PATH ] ;
 ASSERT_NE ( : : GetTempPath ( MAX_PATH , temp_directory ) , 0u ) ;
 ASSERT_NE ( : : GetTempFileName ( temp_directory , L"test" , 0 , my_folder ) , 0u ) ;
 ASSERT_TRUE ( : : DeleteFile ( my_folder ) ) ;
 ASSERT_TRUE ( : : CreateDirectory ( my_folder , NULL ) ) ;
 base : : string16 folder ( my_folder ) ;
 base : : string16 file_name = folder + L"\\foo.txt" ;
 const ULONG kSharing = FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE ;
 base : : win : : ScopedHandle file ( CreateFile ( file_name . c_str ( ) , GENERIC_WRITE , kSharing , NULL , CREATE_ALWAYS , FILE_FLAG_DELETE_ON_CLOSE , NULL ) ) ;
 EXPECT_TRUE ( file . IsValid ( ) ) ;
 base : : string16 file_name_nt1 = base : : string16 ( L"\\??\\" ) + file_name ;
 base : : string16 file_name_nt2 = base : : string16 ( L"\\??\\" ) + folder + L"\\FOO.txT" ;
 EXPECT_TRUE ( SameObject ( file . Get ( ) , file_name_nt1 . c_str ( ) ) ) ;
 EXPECT_TRUE ( SameObject ( file . Get ( ) , file_name_nt2 . c_str ( ) ) ) ;
 file . Close ( ) ;
 EXPECT_TRUE ( : : RemoveDirectory ( my_folder ) ) ;
 }