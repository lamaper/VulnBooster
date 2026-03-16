static void omap_prcm_write(void *opaque, target_phys_addr_t addr,

                            uint64_t value, unsigned size)

{

    struct omap_prcm_s *s = (struct omap_prcm_s *) opaque;



    if (size != 4) {

        return omap_badwidth_write32(opaque, addr, value);

    }



    switch (addr) {

    case 0x000:	 

    case 0x054:	 

    case 0x084:	 

    case 0x1e4:	 

    case 0x220:	 

    case 0x224:	 

    case 0x22c:	 

    case 0x2c8:	 

    case 0x2e4:	 

    case 0x320:	 

    case 0x3e4:	 

    case 0x420:	 

    case 0x520:	 

    case 0x820:	 

    case 0x8e4:	 

        OMAP_RO_REG(addr);

        return;



    case 0x010:	 

        s->sysconfig = value & 1;

        break;



    case 0x018:	 

        s->irqst[0] &= ~value;

        omap_prcm_int_update(s, 0);

        break;

    case 0x01c:	 

        s->irqen[0] = value & 0x3f;

        omap_prcm_int_update(s, 0);

        break;



    case 0x050:	 

        s->voltctrl = value & 0xf1c3;

        break;



    case 0x060:	 

        s->clksrc[0] = value & 0xdb;

         

        break;



    case 0x070:	 

        s->clkout[0] = value & 0xbbbb;

         

        break;



    case 0x078:	 

        s->clkemul[0] = value & 1;

         

        break;



    case 0x080:	 

        break;



    case 0x090:	 

        s->setuptime[0] = value & 0xffff;

        break;

    case 0x094:	 

        s->setuptime[1] = value & 0xffff;

        break;



    case 0x098:	 

        s->clkpol[0] = value & 0x701;

        break;



    case 0x0b0:	 

    case 0x0b4:	 

    case 0x0b8:	 

    case 0x0bc:	 

    case 0x0c0:	 

    case 0x0c4:	 

    case 0x0c8:	 

    case 0x0cc:	 

    case 0x0d0:	 

    case 0x0d4:	 

    case 0x0d8:	 

    case 0x0dc:	 

    case 0x0e0:	 

    case 0x0e4:	 

    case 0x0e8:	 

    case 0x0ec:	 

    case 0x0f0:	 

    case 0x0f4:	 

    case 0x0f8:	 

    case 0x0fc:	 

        s->scratch[(addr - 0xb0) >> 2] = value;

        break;



    case 0x140:	 

        s->clksel[0] = value & 0x1f;

         

        break;

    case 0x148:	 

        s->clkctrl[0] = value & 0x1f;

        break;



    case 0x158:	 

        s->rst[0] &= ~value;

        break;

    case 0x1c8:	 

        s->wkup[0] = value & 0x15;

        break;



    case 0x1d4:	 

        s->ev = value & 0x1f;

        break;

    case 0x1d8:	 

        s->evtime[0] = value;

        break;

    case 0x1dc:	 

        s->evtime[1] = value;

        break;



    case 0x1e0:	 

        s->power[0] = value & 0xc0f;

        break;



    case 0x200:	 

        s->clken[0] = value & 0xbfffffff;

         

         

        break;

    case 0x204:	 

        s->clken[1] = value & 0x00000007;

         

        break;

    case 0x210:	 

        s->clken[2] = value & 0xfffffff9;

         

         

        break;

    case 0x214:	 

        s->clken[3] = value & 0x00000007;

         

        break;

    case 0x21c:	 

        s->clken[4] = value & 0x0000001f;

         

        break;



    case 0x230:	 

        s->clkidle[0] = value & 0xfffffff9;

         

        break;

    case 0x234:	 

        s->clkidle[1] = value & 0x00000007;

         

        break;

    case 0x238:	 

        s->clkidle[2] = value & 0x00000007;

         

        break;

    case 0x23c:	 

        s->clkidle[3] = value & 0x0000001f;

         

        break;



    case 0x240:	 

        s->clksel[1] = value & 0x0fffbf7f;

         

        break;



    case 0x244:	 

        s->clksel[2] = value & 0x00fffffc;

         

        break;



    case 0x248:	 

        s->clkctrl[1] = value & 0x7;

        break;



    case 0x2a0:	 

        s->wken[0] = value & 0x04667ff8;

        break;

    case 0x2a4:	 

        s->wken[1] = value & 0x00000005;

        break;



    case 0x2b0:	 

        s->wkst[0] &= ~value;

        break;

    case 0x2b4:	 

        s->wkst[1] &= ~value;

        break;



    case 0x2e0:	 

        s->power[1] = (value & 0x00fc3f) | (1 << 2);

        break;



    case 0x300:	 

        s->clken[5] = value & 6;

         

        break;

    case 0x310:	 

        s->clken[6] = value & 1;

         

        break;

    case 0x340:	 

        s->clksel[3] = value & 7;

         

        break;

    case 0x348:	 

        s->clkctrl[2] = value & 1;

        break;

    case 0x350:	 

        s->rstctrl[0] = value & 1;

         

        break;

    case 0x358:	 

        s->rst[1] &= ~value;

        break;

    case 0x3c8:	 

        s->wkup[1] = value & 0x13;

        break;

    case 0x3e0:	 

        s->power[2] = (value & 0x00c0f) | (3 << 2);

        break;



    case 0x400:	 

        s->clken[7] = value & 0xd;

         

        break;

    case 0x410:	 

        s->clken[8] = value & 0x3f;

         

        break;

    case 0x430:	 

        s->clkidle[4] = value & 0x0000003f;

         

        break;

    case 0x440:	 

        s->clksel[4] = value & 3;

         

        break;

    case 0x450:	 

         

        if (value & 2)

            qemu_system_reset_request();

        break;

    case 0x454:	 

        s->rsttime_wkup = value & 0x1fff;

        break;

    case 0x458:	 

        s->rst[2] &= ~value;

        break;

    case 0x4a0:	 

        s->wken[2] = value & 0x00000005;

        break;

    case 0x4b0:	 

        s->wkst[2] &= ~value;

        break;



    case 0x500:	 

        if (value & 0xffffff30)

            fprintf(stderr, "%s: write 0s in CM_CLKEN_PLL for "

                            "future compatibility\n", __FUNCTION__);

        if ((s->clken[9] ^ value) & 0xcc) {

            s->clken[9] &= ~0xcc;

            s->clken[9] |= value & 0xcc;

            omap_prcm_apll_update(s);

        }

        if ((s->clken[9] ^ value) & 3) {

            s->clken[9] &= ~3;

            s->clken[9] |= value & 3;

            omap_prcm_dpll_update(s);

        }

        break;

    case 0x530:	 

        s->clkidle[5] = value & 0x000000cf;

         

        break;

    case 0x540:	 

        if (value & 0xfc4000d7)

            fprintf(stderr, "%s: write 0s in CM_CLKSEL1_PLL for "

                            "future compatibility\n", __FUNCTION__);

        if ((s->clksel[5] ^ value) & 0x003fff00) {

            s->clksel[5] = value & 0x03bfff28;

            omap_prcm_dpll_update(s);

        }

         



        s->clksel[5] = value & 0x03bfff28;

        break;

    case 0x544:	 

        if (value & ~3)

            fprintf(stderr, "%s: write 0s in CM_CLKSEL2_PLL[31:2] for "

                            "future compatibility\n", __FUNCTION__);

        if (s->clksel[6] != (value & 3)) {

            s->clksel[6] = value & 3;

            omap_prcm_dpll_update(s);

        }

        break;



    case 0x800:	 

        s->clken[10] = value & 0x501;

         

        break;

    case 0x810:	 

        s->clken[11] = value & 0x2;

         

        break;

    case 0x830:	 

        s->clkidle[6] = value & 0x2;

         

        break;

    case 0x840:	 

        s->clksel[7] = value & 0x3fff;

         

        break;

    case 0x848:	 

        s->clkctrl[3] = value & 0x101;

        break;

    case 0x850:	 

         

        break;

    case 0x858:	 

        s->rst[3] &= ~value;

        break;

    case 0x8c8:	 

        s->wkup[2] = value & 0x13;

        break;

    case 0x8e0:	 

        s->power[3] = (value & 0x03017) | (3 << 2);

        break;



    case 0x8f0:	 

        s->irqst[1] &= ~value;

        omap_prcm_int_update(s, 1);

        break;

    case 0x8f4:	 

        s->irqen[1] = value & 0x7;

        omap_prcm_int_update(s, 1);

        break;



    case 0x8f8:	 

        s->irqst[2] &= ~value;

        omap_prcm_int_update(s, 2);

        break;

    case 0x8fc:	 

        s->irqen[2] = value & 0x7;

        omap_prcm_int_update(s, 2);

        break;



    default:

        OMAP_BAD_REG(addr);

        return;

    }

}
