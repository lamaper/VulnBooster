static inline void timerblock_update_irq ( TimerBlock * tb ) {
 qemu_set_irq ( tb -> irq , tb -> status ) ;
 }