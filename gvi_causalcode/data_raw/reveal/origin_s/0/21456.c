static void armv7m_nvic_instance_init ( Object * obj ) {
 GICState * s = ARM_GIC_COMMON ( obj ) ;
 s -> num_irq = 64 ;
 }