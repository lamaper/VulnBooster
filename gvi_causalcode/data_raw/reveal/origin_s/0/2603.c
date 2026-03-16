static void cpu_set_irq ( void * opaque , int irq , int level ) {
 SPARCCPU * cpu = opaque ;
 CPUSPARCState * env = & cpu -> env ;
 if ( level ) {
 trace_sun4m_cpu_set_irq_raise ( irq ) ;
 env -> pil_in |= 1 << irq ;
 cpu_kick_irq ( cpu ) ;
 }
 else {
 trace_sun4m_cpu_set_irq_lower ( irq ) ;
 env -> pil_in &= ~ ( 1 << irq ) ;
 cpu_check_irqs ( env ) ;
 }
 }