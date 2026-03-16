TEST ( WinUtils , IsReparsePoint ) {
 using sandbox : : IsReparsePoint ;
 wchar_t temp_directory [ MAX_PATH ] ;
 wchar_t my_folder [ MAX_PATH ] ;
 ASSERT_NE ( : : GetTempPath ( MAX_PATH , temp_directory ) , 0u ) ;
 ASSERT_NE ( : : GetTempFileName ( temp_directory , L"test" , 0 , my_folder ) , 0u ) ;
 ASSERT_TRUE ( : : DeleteFile ( my_folder ) ) ;
 ASSERT_TRUE ( : : CreateDirectory ( my_folder , NULL ) ) ;
 bool result = true ;
 EXPECT_EQ ( ERROR_SUCCESS , IsReparsePoint ( my_folder , & result ) ) ;
 EXPECT_FALSE ( result ) ;
 base : : string16 not_found = base : : string16 ( my_folder ) + L"\\foo\\bar" ;
 base : : string16 new_file = base : : string16 ( my_folder ) + L"\\foo" ;
 EXPECT_EQ ( ERROR_SUCCESS , IsReparsePoint ( new_file , & result ) ) ;
 EXPECT_FALSE ( result ) ;
 HANDLE dir = : : CreateFile ( my_folder , FILE_ALL_ACCESS , FILE_SHARE_READ | FILE_SHARE_WRITE , NULL , OPEN_EXISTING , FILE_FLAG_BACKUP_SEMANTICS , NULL ) ;
 EXPECT_NE ( INVALID_HANDLE_VALUE , dir ) ;
 base : : string16 temp_dir_nt = base : : string16 ( L"\\??\\" ) + temp_directory ;
 EXPECT_TRUE ( SetReparsePoint ( dir , temp_dir_nt . c_str ( ) ) ) ;
 EXPECT_EQ ( ERROR_SUCCESS , IsReparsePoint ( new_file , & result ) ) ;
 EXPECT_TRUE ( result ) ;
 EXPECT_TRUE ( DeleteReparsePoint ( dir ) ) ;
 EXPECT_TRUE ( : : CloseHandle ( dir ) ) ;
 EXPECT_TRUE ( : : RemoveDirectory ( my_folder ) ) ;
 }