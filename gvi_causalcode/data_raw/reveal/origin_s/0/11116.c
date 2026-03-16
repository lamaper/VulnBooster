TEST ( WinUtils , IsPipe ) {
 using sandbox : : IsPipe ;
 base : : string16 pipe_name = L"\\??\\pipe\\mypipe" ;
 EXPECT_TRUE ( IsPipe ( pipe_name ) ) ;
 pipe_name = L"\\??\\PiPe\\mypipe" ;
 EXPECT_TRUE ( IsPipe ( pipe_name ) ) ;
 pipe_name = L"\\??\\pipe" ;
 EXPECT_FALSE ( IsPipe ( pipe_name ) ) ;
 pipe_name = L"\\??\\_pipe_\\mypipe" ;
 EXPECT_FALSE ( IsPipe ( pipe_name ) ) ;
 pipe_name = L"\\??\\ABCD\\mypipe" ;
 EXPECT_FALSE ( IsPipe ( pipe_name ) ) ;
 pipe_name = L"/??/pipe/mypipe" ;
 EXPECT_FALSE ( IsPipe ( pipe_name ) ) ;
 pipe_name = L"\\XX\\pipe\\mypipe" ;
 EXPECT_FALSE ( IsPipe ( pipe_name ) ) ;
 pipe_name = L"\\Device\\NamedPipe\\mypipe" ;
 EXPECT_FALSE ( IsPipe ( pipe_name ) ) ;
 }