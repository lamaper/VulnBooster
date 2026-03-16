static int get_logical_cpus ( AVCodecContext * avctx ) {
 int ret , nb_cpus = 1 ;

 CPU_ZERO ( & cpuset ) ;
 ret = sched_getaffinity ( 0 , sizeof ( cpuset ) , & cpuset ) ;
 if ( ! ret ) {
 nb_cpus = CPU_COUNT ( & cpuset ) ;
 }

 ret = GetProcessAffinityMask ( GetCurrentProcess ( ) , & proc_aff , & sys_aff ) ;
 if ( ret ) nb_cpus = av_popcount64 ( proc_aff ) ;

 CTL_HW , HW_NCPU }
 ;
 size_t len = sizeof ( nb_cpus ) ;
 ret = sysctl ( mib , 2 , & nb_cpus , & len , NULL , 0 ) ;
 if ( ret == - 1 ) nb_cpus = 0 ;



 return nb_cpus ;
 }