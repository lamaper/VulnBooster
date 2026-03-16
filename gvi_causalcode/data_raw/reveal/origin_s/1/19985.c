int arm_cpu_caps ( void ) {
 int flags ;
 int mask ;
 if ( ! arm_cpu_env_flags ( & flags ) ) {
 return flags ;
 }
 mask = arm_cpu_env_mask ( ) ;




 }