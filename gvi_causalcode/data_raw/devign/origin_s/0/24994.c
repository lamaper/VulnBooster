static void gic_reset(gic_state *s)

{

    int i;

    memset(s->irq_state, 0, GIC_NIRQ * sizeof(gic_irq_state));

    for (i = 0 ; i < NUM_CPU(s); i++) {

        s->priority_mask[i] = 0xf0;

        s->current_pending[i] = 1023;

        s->running_irq[i] = 1023;

        s->running_priority[i] = 0x100;


         

        s->cpu_enabled[i] = 1;


        s->cpu_enabled[i] = 0;


    }

    for (i = 0; i < 16; i++) {

        GIC_SET_ENABLED(i);

        GIC_SET_TRIGGER(i);

    }


     

    s->enabled = 1;


    s->enabled = 0;


}
