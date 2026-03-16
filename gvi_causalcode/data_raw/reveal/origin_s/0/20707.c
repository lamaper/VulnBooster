void cpu_resume_from_signal ( CPUArchState * env1 , void * puc ) {







 env1 -> exception_index = - 1 ;
 siglongjmp ( env1 -> jmp_env , 1 ) ;
 }