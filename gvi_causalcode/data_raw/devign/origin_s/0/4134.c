static void gic_dist_writeb(void *opaque, hwaddr offset,

                            uint32_t value, MemTxAttrs attrs)

{

    GICState *s = (GICState *)opaque;

    int irq;

    int i;

    int cpu;



    cpu = gic_get_current_cpu(s);

    if (offset < 0x100) {

        if (offset == 0) {

            s->enabled = (value & 1);

            DPRINTF("Distribution %sabled\n", s->enabled ? "En" : "Dis");

        } else if (offset < 4) {

             

        } else if (offset >= 0x80) {

             

        } else {

            goto bad_reg;

        }

    } else if (offset < 0x180) {

         

        irq = (offset - 0x100) * 8 + GIC_BASE_IRQ;

        if (irq >= s->num_irq)

            goto bad_reg;

        if (irq < GIC_NR_SGIS) {

            value = 0xff;

        }



        for (i = 0; i < 8; i++) {

            if (value & (1 << i)) {

                int mask =

                    (irq < GIC_INTERNAL) ? (1 << cpu) : GIC_TARGET(irq + i);

                int cm = (irq < GIC_INTERNAL) ? (1 << cpu) : ALL_CPU_MASK;



                if (!GIC_TEST_ENABLED(irq + i, cm)) {

                    DPRINTF("Enabled IRQ %d\n", irq + i);

                }

                GIC_SET_ENABLED(irq + i, cm);

                 

                if (GIC_TEST_LEVEL(irq + i, mask)

                        && !GIC_TEST_EDGE_TRIGGER(irq + i)) {

                    DPRINTF("Set %d pending mask %x\n", irq + i, mask);

                    GIC_SET_PENDING(irq + i, mask);

                }

            }

        }

    } else if (offset < 0x200) {

         

        irq = (offset - 0x180) * 8 + GIC_BASE_IRQ;

        if (irq >= s->num_irq)

            goto bad_reg;

        if (irq < GIC_NR_SGIS) {

            value = 0;

        }



        for (i = 0; i < 8; i++) {

            if (value & (1 << i)) {

                int cm = (irq < GIC_INTERNAL) ? (1 << cpu) : ALL_CPU_MASK;



                if (GIC_TEST_ENABLED(irq + i, cm)) {

                    DPRINTF("Disabled IRQ %d\n", irq + i);

                }

                GIC_CLEAR_ENABLED(irq + i, cm);

            }

        }

    } else if (offset < 0x280) {

         

        irq = (offset - 0x200) * 8 + GIC_BASE_IRQ;

        if (irq >= s->num_irq)

            goto bad_reg;

        if (irq < GIC_NR_SGIS) {

            value = 0;

        }



        for (i = 0; i < 8; i++) {

            if (value & (1 << i)) {

                GIC_SET_PENDING(irq + i, GIC_TARGET(irq + i));

            }

        }

    } else if (offset < 0x300) {

         

        irq = (offset - 0x280) * 8 + GIC_BASE_IRQ;

        if (irq >= s->num_irq)

            goto bad_reg;

        if (irq < GIC_NR_SGIS) {

            value = 0;

        }



        for (i = 0; i < 8; i++) {

             

            if (value & (1 << i)) {

                GIC_CLEAR_PENDING(irq + i, ALL_CPU_MASK);

            }

        }

    } else if (offset < 0x400) {

         

        goto bad_reg;

    } else if (offset < 0x800) {

         

        irq = (offset - 0x400) + GIC_BASE_IRQ;

        if (irq >= s->num_irq)

            goto bad_reg;

        gic_set_priority(s, cpu, irq, value);

    } else if (offset < 0xc00) {

         

        if (s->num_cpu != 1 || s->revision == REV_11MPCORE) {

            irq = (offset - 0x800) + GIC_BASE_IRQ;

            if (irq >= s->num_irq) {

                goto bad_reg;

            }

            if (irq < 29) {

                value = 0;

            } else if (irq < GIC_INTERNAL) {

                value = ALL_CPU_MASK;

            }

            s->irq_target[irq] = value & ALL_CPU_MASK;

        }

    } else if (offset < 0xf00) {

         

        irq = (offset - 0xc00) * 4 + GIC_BASE_IRQ;

        if (irq >= s->num_irq)

            goto bad_reg;

        if (irq < GIC_NR_SGIS)

            value |= 0xaa;

        for (i = 0; i < 4; i++) {

            if (s->revision == REV_11MPCORE || s->revision == REV_NVIC) {

                if (value & (1 << (i * 2))) {

                    GIC_SET_MODEL(irq + i);

                } else {

                    GIC_CLEAR_MODEL(irq + i);

                }

            }

            if (value & (2 << (i * 2))) {

                GIC_SET_EDGE_TRIGGER(irq + i);

            } else {

                GIC_CLEAR_EDGE_TRIGGER(irq + i);

            }

        }

    } else if (offset < 0xf10) {

         

        goto bad_reg;

    } else if (offset < 0xf20) {

         

        if (s->revision == REV_11MPCORE || s->revision == REV_NVIC) {

            goto bad_reg;

        }

        irq = (offset - 0xf10);



        s->sgi_pending[irq][cpu] &= ~value;

        if (s->sgi_pending[irq][cpu] == 0) {

            GIC_CLEAR_PENDING(irq, 1 << cpu);

        }

    } else if (offset < 0xf30) {

         

        if (s->revision == REV_11MPCORE || s->revision == REV_NVIC) {

            goto bad_reg;

        }

        irq = (offset - 0xf20);



        GIC_SET_PENDING(irq, 1 << cpu);

        s->sgi_pending[irq][cpu] |= value;

    } else {

        goto bad_reg;

    }

    gic_update(s);

    return;

bad_reg:

    qemu_log_mask(LOG_GUEST_ERROR,

                  "gic_dist_writeb: Bad offset %x\n", (int)offset);

}
