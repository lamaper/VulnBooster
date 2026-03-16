static void fsl_common_init ( OpenPICState * opp ) {
 int i ;
 int virq = OPENPIC_MAX_SRC ;
 opp -> vid = VID_REVISION_1_2 ;
 opp -> vir = VIR_GENERIC ;
 opp -> vector_mask = 0xFFFF ;
 opp -> tfrr_reset = 0 ;
 opp -> ivpr_reset = IVPR_MASK_MASK ;
 opp -> idr_reset = 1 << 0 ;
 opp -> max_irq = OPENPIC_MAX_IRQ ;
 opp -> irq_ipi0 = virq ;
 virq += OPENPIC_MAX_IPI ;
 opp -> irq_tim0 = virq ;
 virq += OPENPIC_MAX_TMR ;
 assert ( virq <= OPENPIC_MAX_IRQ ) ;
 opp -> irq_msi = 224 ;
 msi_supported = true ;
 for ( i = 0 ;
 i < opp -> fsl -> max_ext ;
 i ++ ) {
 opp -> src [ i ] . level = false ;
 }
 for ( i = 16 ;
 i < OPENPIC_MAX_SRC ;
 i ++ ) {
 opp -> src [ i ] . type = IRQ_TYPE_FSLINT ;
 opp -> src [ i ] . level = true ;
 }
 for ( i = OPENPIC_MAX_SRC ;
 i < virq ;
 i ++ ) {
 opp -> src [ i ] . type = IRQ_TYPE_FSLSPECIAL ;
 opp -> src [ i ] . level = false ;
 }
 }