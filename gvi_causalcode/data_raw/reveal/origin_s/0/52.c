static int main_recompress_output ( main_file * ofile ) {
 pid_t recomp_id ;
 int pipefd [ 2 ] ;
 int output_fd = - 1 ;
 int ret ;
 const main_extcomp * recomp = ofile -> compressor ;
 pipefd [ 0 ] = pipefd [ 1 ] = - 1 ;
 if ( pipe ( pipefd ) ) {
 XPR ( NT "pipe failed: %s\n" , xd3_mainerror ( ret = get_errno ( ) ) ) ;
 goto pipe_cleanup ;
 }
 if ( ( recomp_id = fork ( ) ) < 0 ) {
 XPR ( NT "fork failed: %s\n" , xd3_mainerror ( ret = get_errno ( ) ) ) ;
 goto pipe_cleanup ;
 }
 if ( recomp_id == 0 ) {
 if ( option_verbose > 2 ) {
 XPR ( NT "external recompression pid %d\n" , getpid ( ) ) ;
 }
 if ( dup2 ( XFNO ( ofile ) , STDOUT_FILENO ) < 0 || dup2 ( pipefd [ PIPE_READ_FD ] , STDIN_FILENO ) < 0 || close ( pipefd [ PIPE_READ_FD ] ) || close ( pipefd [ PIPE_WRITE_FD ] ) || execlp ( recomp -> recomp_cmdname , recomp -> recomp_cmdname , recomp -> recomp_options , option_force2 ? "-f" : NULL , NULL ) ) {
 XPR ( NT "child process %s failed to execute: %s\n" , recomp -> recomp_cmdname , xd3_mainerror ( get_errno ( ) ) ) ;
 }
 _exit ( 127 ) ;
 }
 XD3_ASSERT ( num_subprocs < MAX_SUBPROCS ) ;
 ext_subprocs [ num_subprocs ++ ] = recomp_id ;
 output_fd = dup ( pipefd [ PIPE_WRITE_FD ] ) ;
 if ( output_fd < 0 || main_file_close ( ofile ) || close ( pipefd [ PIPE_READ_FD ] ) || close ( pipefd [ PIPE_WRITE_FD ] ) ) {
 XPR ( NT "close failed: %s\n" , xd3_mainerror ( ret = get_errno ( ) ) ) ;
 goto pipe_cleanup ;
 }

 XPR ( NT "fdopen failed: %s\n" , xd3_mainerror ( ret = get_errno ( ) ) ) ;
 goto pipe_cleanup ;
 }


 pipe_cleanup : close ( output_fd ) ;
 close ( pipefd [ PIPE_READ_FD ] ) ;
 close ( pipefd [ PIPE_WRITE_FD ] ) ;
 return ret ;
 }