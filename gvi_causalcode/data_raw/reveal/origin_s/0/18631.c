REGRESSION_TEST ( SDK_API_TSfopen ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 char write_file_name [ PATH_NAME_MAX ] ;
 TSFile source_read_file ;
 TSFile write_file ;
 TSFile cmp_read_file ;
 char input_buffer [ BUFSIZ ] ;
 char cmp_buffer [ BUFSIZ ] ;
 struct stat stat_buffer_pre , stat_buffer_post , stat_buffer_input ;
 char * ret_val ;
 int read = 0 , wrote = 0 ;
 int64_t read_amount = 0 ;
 char INPUT_TEXT_FILE [ ] = "plugin.config" ;
 char input_file_full_path [ BUFSIZ ] ;
 if ( TSInstallDirGet ( ) == nullptr ) {
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 ink_filepath_make ( input_file_full_path , sizeof ( input_file_full_path ) , TSConfigDirGet ( ) , INPUT_TEXT_FILE ) ;
 if ( ! ( source_read_file = TSfopen ( input_file_full_path , "r" ) ) ) {
 SDK_RPRINT ( test , "TSfopen" , "TestCase1" , TC_FAIL , "can't open file for reading" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSfopen" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 snprintf ( write_file_name , PATH_NAME_MAX , "/tmp/%sXXXXXX" , PFX ) ;
 int write_file_fd ;
 if ( ( write_file_fd = mkstemp ( write_file_name ) ) <= 0 ) {
 SDK_RPRINT ( test , "mkstemp" , "std func" , TC_FAIL , "can't create file for writing" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 return ;
 }
 close ( write_file_fd ) ;
 if ( ! ( write_file = TSfopen ( write_file_name , "w" ) ) ) {
 SDK_RPRINT ( test , "TSfopen" , "TestCase2" , TC_FAIL , "can't open file for writing" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 return ;
 }
 SDK_RPRINT ( test , "TSfopen" , "TestCase2" , TC_PASS , "ok" ) ;
 memset ( input_buffer , '\0' , BUFSIZ ) ;
 if ( stat ( input_file_full_path , & stat_buffer_input ) != 0 ) {
 SDK_RPRINT ( test , "stat" , "std func" , TC_FAIL , "source file and input file messed up" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 read_amount = ( stat_buffer_input . st_size <= ( off_t ) sizeof ( input_buffer ) ) ? ( stat_buffer_input . st_size ) : ( sizeof ( input_buffer ) ) ;
 if ( ( ret_val = TSfgets ( source_read_file , input_buffer , read_amount ) ) == nullptr ) {
 SDK_RPRINT ( test , "TSfgets" , "TestCase1" , TC_FAIL , "can't read from file" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 else {
 if ( ret_val != input_buffer ) {
 SDK_RPRINT ( test , "TSfgets" , "TestCase2" , TC_FAIL , "reading error" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSfgets" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 wrote = TSfwrite ( write_file , input_buffer , read_amount ) ;
 if ( wrote != read_amount ) {
 SDK_RPRINT ( test , "TSfwrite" , "TestCase1" , TC_FAIL , "writing error" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 SDK_RPRINT ( test , "TSfwrite" , "TestCase1" , TC_PASS , "ok" ) ;
 if ( stat ( write_file_name , & stat_buffer_pre ) != 0 ) {
 SDK_RPRINT ( test , "stat" , "std func" , TC_FAIL , "TSfwrite error" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 TSfflush ( write_file ) ;
 if ( stat ( write_file_name , & stat_buffer_post ) != 0 ) {
 SDK_RPRINT ( test , "stat" , "std func" , TC_FAIL , "TSfflush error" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 if ( ( stat_buffer_pre . st_size == 0 ) && ( stat_buffer_post . st_size == read_amount ) ) {
 SDK_RPRINT ( test , "TSfflush" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSfflush" , "TestCase1" , TC_FAIL , "TSfflush error" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 cmp_read_file = TSfopen ( write_file_name , "r" ) ;
 if ( cmp_read_file == nullptr ) {
 SDK_RPRINT ( test , "TSfopen" , "TestCase3" , TC_FAIL , "can't open file for reading" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 return ;
 }
 read_amount = ( stat_buffer_input . st_size <= ( off_t ) sizeof ( cmp_buffer ) ) ? ( stat_buffer_input . st_size ) : ( sizeof ( cmp_buffer ) ) ;
 read = TSfread ( cmp_read_file , cmp_buffer , read_amount ) ;
 if ( read != read_amount ) {
 SDK_RPRINT ( test , "TSfread" , "TestCase1" , TC_FAIL , "can't reading" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 if ( cmp_read_file != nullptr ) {
 TSfclose ( cmp_read_file ) ;
 }
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSfread" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 if ( memcmp ( input_buffer , cmp_buffer , read_amount ) != 0 ) {
 SDK_RPRINT ( test , "TSfread" , "TestCase2" , TC_FAIL , "reading error" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 if ( source_read_file != nullptr ) {
 TSfclose ( source_read_file ) ;
 }
 if ( write_file != nullptr ) {
 TSfclose ( write_file ) ;
 }
 if ( cmp_read_file != nullptr ) {
 TSfclose ( cmp_read_file ) ;
 }
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSfread" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 if ( unlink ( write_file_name ) != 0 ) {
 SDK_RPRINT ( test , "unlink" , "std func" , TC_FAIL , "can't remove temp file" ) ;
 }
 TSfclose ( source_read_file ) ;
 SDK_RPRINT ( test , "TSfclose" , "TestCase1" , TC_PASS , "ok" ) ;
 TSfclose ( write_file ) ;
 SDK_RPRINT ( test , "TSfclose" , "TestCase2" , TC_PASS , "ok" ) ;
 * pstatus = REGRESSION_TEST_PASSED ;
 if ( cmp_read_file != nullptr ) {
 TSfclose ( cmp_read_file ) ;
 }
 }