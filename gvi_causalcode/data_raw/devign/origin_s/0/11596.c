tcp_input(struct mbuf *m, int iphlen, struct socket *inso)

{

  	struct ip save_ip, *ip;

	register struct tcpiphdr *ti;

	caddr_t optp = NULL;

	int optlen = 0;

	int len, tlen, off;

        register struct tcpcb *tp = NULL;

	register int tiflags;

        struct socket *so = NULL;

	int todrop, acked, ourfinisacked, needoutput = 0;

	int iss = 0;

	u_long tiwin;

	int ret;

    struct ex_list *ex_ptr;

    Slirp *slirp;



	DEBUG_CALL("tcp_input");

	DEBUG_ARGS((dfd, " m = %8lx  iphlen = %2d  inso = %lx\n",

		    (long )m, iphlen, (long )inso ));



	 

	if (m == NULL) {

		so = inso;

		slirp = so->slirp;



		 

		tp = sototcpcb(so);

		m = so->so_m;

                so->so_m = NULL;

		ti = so->so_ti;

		tiwin = ti->ti_win;

		tiflags = ti->ti_flags;



		goto cont_conn;

	}

	slirp = m->slirp;



	 

	ti = mtod(m, struct tcpiphdr *);

	if (iphlen > sizeof(struct ip )) {

	  ip_stripoptions(m, (struct mbuf *)0);

	  iphlen=sizeof(struct ip );

	}

	 





	 

	ip=mtod(m, struct ip *);

	save_ip = *ip;

	save_ip.ip_len+= iphlen;



	 

	tlen = ((struct ip *)ti)->ip_len;

        tcpiphdr2qlink(ti)->next = tcpiphdr2qlink(ti)->prev = NULL;

        memset(&ti->ti_i.ih_mbuf, 0 , sizeof(struct mbuf_ptr));

	ti->ti_x1 = 0;

	ti->ti_len = htons((uint16_t)tlen);

	len = sizeof(struct ip ) + tlen;

	if(cksum(m, len)) {

	  goto drop;

	}



	 

	off = ti->ti_off << 2;

	if (off < sizeof (struct tcphdr) || off > tlen) {

	  goto drop;

	}

	tlen -= off;

	ti->ti_len = tlen;

	if (off > sizeof (struct tcphdr)) {

	  optlen = off - sizeof (struct tcphdr);

	  optp = mtod(m, caddr_t) + sizeof (struct tcpiphdr);

	}

	tiflags = ti->ti_flags;



	 

	NTOHL(ti->ti_seq);

	NTOHL(ti->ti_ack);

	NTOHS(ti->ti_win);

	NTOHS(ti->ti_urp);



	 

	m->m_data += sizeof(struct tcpiphdr)+off-sizeof(struct tcphdr);

	m->m_len  -= sizeof(struct tcpiphdr)+off-sizeof(struct tcphdr);



    if (slirp->restricted) {

        for (ex_ptr = slirp->exec_list; ex_ptr; ex_ptr = ex_ptr->ex_next) {

            if (ex_ptr->ex_fport == ti->ti_dport &&

                ti->ti_dst.s_addr == ex_ptr->ex_addr.s_addr) {

                break;

            }

        }

        if (!ex_ptr)

            goto drop;

    }

	 

findso:

	so = slirp->tcp_last_so;

	if (so->so_fport != ti->ti_dport ||

	    so->so_lport != ti->ti_sport ||

	    so->so_laddr.s_addr != ti->ti_src.s_addr ||

	    so->so_faddr.s_addr != ti->ti_dst.s_addr) {

		so = solookup(&slirp->tcb, ti->ti_src, ti->ti_sport,

			       ti->ti_dst, ti->ti_dport);

		if (so)

			slirp->tcp_last_so = so;

	}



	 

        if (so == NULL) {

	  if ((tiflags & (TH_SYN|TH_FIN|TH_RST|TH_URG|TH_ACK)) != TH_SYN)

	    goto dropwithreset;



	  if ((so = socreate(slirp)) == NULL)

	    goto dropwithreset;

	  if (tcp_attach(so) < 0) {

	    free(so);  

	    goto dropwithreset;

	  }



	  sbreserve(&so->so_snd, TCP_SNDSPACE);

	  sbreserve(&so->so_rcv, TCP_RCVSPACE);



	  so->so_laddr = ti->ti_src;

	  so->so_lport = ti->ti_sport;

	  so->so_faddr = ti->ti_dst;

	  so->so_fport = ti->ti_dport;



	  if ((so->so_iptos = tcp_tos(so)) == 0)

	    so->so_iptos = ((struct ip *)ti)->ip_tos;



	  tp = sototcpcb(so);

	  tp->t_state = TCPS_LISTEN;

	}



         

        if (so->so_state & SS_ISFCONNECTING)

                goto drop;



	tp = sototcpcb(so);



	 

        if (tp == NULL)

		goto dropwithreset;

	if (tp->t_state == TCPS_CLOSED)

		goto drop;



	tiwin = ti->ti_win;



	 

	tp->t_idle = 0;

	if (SO_OPTIONS)

	   tp->t_timer[TCPT_KEEP] = TCPTV_KEEPINTVL;

	else

	   tp->t_timer[TCPT_KEEP] = TCPTV_KEEP_IDLE;



	 

	if (optp && tp->t_state != TCPS_LISTEN)

		tcp_dooptions(tp, (u_char *)optp, optlen, ti);



	 

	if (tp->t_state == TCPS_ESTABLISHED &&

	    (tiflags & (TH_SYN|TH_FIN|TH_RST|TH_URG|TH_ACK)) == TH_ACK &&

	    ti->ti_seq == tp->rcv_nxt &&

	    tiwin && tiwin == tp->snd_wnd &&

	    tp->snd_nxt == tp->snd_max) {

		if (ti->ti_len == 0) {

			if (SEQ_GT(ti->ti_ack, tp->snd_una) &&

			    SEQ_LEQ(ti->ti_ack, tp->snd_max) &&

			    tp->snd_cwnd >= tp->snd_wnd) {

				 

				if (tp->t_rtt &&

				    SEQ_GT(ti->ti_ack, tp->t_rtseq))

					tcp_xmit_timer(tp, tp->t_rtt);

				acked = ti->ti_ack - tp->snd_una;

				sbdrop(&so->so_snd, acked);

				tp->snd_una = ti->ti_ack;

				m_free(m);



				 

				if (tp->snd_una == tp->snd_max)

					tp->t_timer[TCPT_REXMT] = 0;

				else if (tp->t_timer[TCPT_PERSIST] == 0)

					tp->t_timer[TCPT_REXMT] = tp->t_rxtcur;



				 

				if (so->so_snd.sb_cc)

					(void) tcp_output(tp);



				return;

			}

		} else if (ti->ti_ack == tp->snd_una &&

		    tcpfrag_list_empty(tp) &&

		    ti->ti_len <= sbspace(&so->so_rcv)) {

			 

			tp->rcv_nxt += ti->ti_len;

			 

			if (so->so_emu) {

				if (tcp_emu(so,m)) sbappend(so, m);

			} else

				sbappend(so, m);



			 

			tp->t_flags |= TF_ACKNOW;

			tcp_output(tp);

			return;

		}

	}  

	 

	{ int win;

          win = sbspace(&so->so_rcv);

	  if (win < 0)

	    win = 0;

	  tp->rcv_wnd = max(win, (int)(tp->rcv_adv - tp->rcv_nxt));

	}



	switch (tp->t_state) {



	 

	case TCPS_LISTEN: {



	  if (tiflags & TH_RST)

	    goto drop;

	  if (tiflags & TH_ACK)

	    goto dropwithreset;

	  if ((tiflags & TH_SYN) == 0)

	    goto drop;



	   



	   

	  if ((so->so_faddr.s_addr & slirp->vnetwork_mask.s_addr) ==

	      slirp->vnetwork_addr.s_addr) {

	    if (so->so_faddr.s_addr != slirp->vhost_addr.s_addr &&

		so->so_faddr.s_addr != slirp->vnameserver_addr.s_addr) {

		 

		for (ex_ptr = slirp->exec_list; ex_ptr;

		     ex_ptr = ex_ptr->ex_next) {

		  if(ex_ptr->ex_fport == so->so_fport &&

		     so->so_faddr.s_addr == ex_ptr->ex_addr.s_addr) {

		    so->so_state |= SS_CTL;

		    break;

		  }

		}

		if (so->so_state & SS_CTL) {

		    goto cont_input;

		}

	    }

	     

	  }



	  if (so->so_emu & EMU_NOCONNECT) {

	    so->so_emu &= ~EMU_NOCONNECT;

	    goto cont_input;

	  }



	  if((tcp_fconnect(so) == -1) && (errno != EINPROGRESS) && (errno != EWOULDBLOCK)) {

	    u_char code=ICMP_UNREACH_NET;

	    DEBUG_MISC((dfd, " tcp fconnect errno = %d-%s\n",

			errno,strerror(errno)));

	    if(errno == ECONNREFUSED) {

	       

	      tcp_respond(tp, ti, m, ti->ti_seq+1, (tcp_seq)0,

			  TH_RST|TH_ACK);

	    } else {

	      if(errno == EHOSTUNREACH) code=ICMP_UNREACH_HOST;

	      HTONL(ti->ti_seq);              

	      HTONL(ti->ti_ack);

	      HTONS(ti->ti_win);

	      HTONS(ti->ti_urp);

	      m->m_data -= sizeof(struct tcpiphdr)+off-sizeof(struct tcphdr);

	      m->m_len  += sizeof(struct tcpiphdr)+off-sizeof(struct tcphdr);

	      *ip=save_ip;

	      icmp_error(m, ICMP_UNREACH,code, 0,strerror(errno));

	    }

            tcp_close(tp);

	    m_free(m);

	  } else {

	     

	    so->so_m = m;

	    so->so_ti = ti;

	    tp->t_timer[TCPT_KEEP] = TCPTV_KEEP_INIT;

	    tp->t_state = TCPS_SYN_RECEIVED;

	    tcp_template(tp);

	  }

	  return;



	cont_conn:

	   

	  if (so->so_state & SS_NOFDREF) {

	    tp = tcp_close(tp);

	    goto dropwithreset;

	  }

	cont_input:

	  tcp_template(tp);



	  if (optp)

	    tcp_dooptions(tp, (u_char *)optp, optlen, ti);



	  if (iss)

	    tp->iss = iss;

	  else

	    tp->iss = slirp->tcp_iss;

	  slirp->tcp_iss += TCP_ISSINCR/2;

	  tp->irs = ti->ti_seq;

	  tcp_sendseqinit(tp);

	  tcp_rcvseqinit(tp);

	  tp->t_flags |= TF_ACKNOW;

	  tp->t_state = TCPS_SYN_RECEIVED;

	  tp->t_timer[TCPT_KEEP] = TCPTV_KEEP_INIT;

	  goto trimthenstep6;

	}  



	 

	case TCPS_SYN_SENT:

		if ((tiflags & TH_ACK) &&

		    (SEQ_LEQ(ti->ti_ack, tp->iss) ||

		     SEQ_GT(ti->ti_ack, tp->snd_max)))

			goto dropwithreset;



		if (tiflags & TH_RST) {

                        if (tiflags & TH_ACK) {

                                tcp_drop(tp, 0);  

                        }

			goto drop;

		}



		if ((tiflags & TH_SYN) == 0)

			goto drop;

		if (tiflags & TH_ACK) {

			tp->snd_una = ti->ti_ack;

			if (SEQ_LT(tp->snd_nxt, tp->snd_una))

				tp->snd_nxt = tp->snd_una;

		}



		tp->t_timer[TCPT_REXMT] = 0;

		tp->irs = ti->ti_seq;

		tcp_rcvseqinit(tp);

		tp->t_flags |= TF_ACKNOW;

		if (tiflags & TH_ACK && SEQ_GT(tp->snd_una, tp->iss)) {

			soisfconnected(so);

			tp->t_state = TCPS_ESTABLISHED;



			(void) tcp_reass(tp, (struct tcpiphdr *)0,

				(struct mbuf *)0);

			 

			if (tp->t_rtt)

				tcp_xmit_timer(tp, tp->t_rtt);

		} else

			tp->t_state = TCPS_SYN_RECEIVED;



trimthenstep6:

		 

		ti->ti_seq++;

		if (ti->ti_len > tp->rcv_wnd) {

			todrop = ti->ti_len - tp->rcv_wnd;

			m_adj(m, -todrop);

			ti->ti_len = tp->rcv_wnd;

			tiflags &= ~TH_FIN;

		}

		tp->snd_wl1 = ti->ti_seq - 1;

		tp->rcv_up = ti->ti_seq;

		goto step6;

	}  

	 

	todrop = tp->rcv_nxt - ti->ti_seq;

	if (todrop > 0) {

		if (tiflags & TH_SYN) {

			tiflags &= ~TH_SYN;

			ti->ti_seq++;

			if (ti->ti_urp > 1)

				ti->ti_urp--;

			else

				tiflags &= ~TH_URG;

			todrop--;

		}

		 

		if (todrop > ti->ti_len

		    || (todrop == ti->ti_len && (tiflags & TH_FIN) == 0)) {

			 

			tiflags &= ~TH_FIN;



			 

			tp->t_flags |= TF_ACKNOW;

			todrop = ti->ti_len;

		}

		m_adj(m, todrop);

		ti->ti_seq += todrop;

		ti->ti_len -= todrop;

		if (ti->ti_urp > todrop)

			ti->ti_urp -= todrop;

		else {

			tiflags &= ~TH_URG;

			ti->ti_urp = 0;

		}

	}

	 

	if ((so->so_state & SS_NOFDREF) &&

	    tp->t_state > TCPS_CLOSE_WAIT && ti->ti_len) {

		tp = tcp_close(tp);

		goto dropwithreset;

	}



	 

	todrop = (ti->ti_seq+ti->ti_len) - (tp->rcv_nxt+tp->rcv_wnd);

	if (todrop > 0) {

		if (todrop >= ti->ti_len) {

			 

			if (tiflags & TH_SYN &&

			    tp->t_state == TCPS_TIME_WAIT &&

			    SEQ_GT(ti->ti_seq, tp->rcv_nxt)) {

				iss = tp->rcv_nxt + TCP_ISSINCR;

				tp = tcp_close(tp);

				goto findso;

			}

			 

			if (tp->rcv_wnd == 0 && ti->ti_seq == tp->rcv_nxt) {

				tp->t_flags |= TF_ACKNOW;

			} else {

				goto dropafterack;

			}

		}

		m_adj(m, -todrop);

		ti->ti_len -= todrop;

		tiflags &= ~(TH_PUSH|TH_FIN);

	}



	 

	if (tiflags&TH_RST) switch (tp->t_state) {



	case TCPS_SYN_RECEIVED:

	case TCPS_ESTABLISHED:

	case TCPS_FIN_WAIT_1:

	case TCPS_FIN_WAIT_2:

	case TCPS_CLOSE_WAIT:

		tp->t_state = TCPS_CLOSED;

                tcp_close(tp);

		goto drop;



	case TCPS_CLOSING:

	case TCPS_LAST_ACK:

	case TCPS_TIME_WAIT:

                tcp_close(tp);

		goto drop;

	}



	 

	if (tiflags & TH_SYN) {

		tp = tcp_drop(tp,0);

		goto dropwithreset;

	}



	 

	if ((tiflags & TH_ACK) == 0) goto drop;



	 

	switch (tp->t_state) {

	 

	case TCPS_SYN_RECEIVED:



		if (SEQ_GT(tp->snd_una, ti->ti_ack) ||

		    SEQ_GT(ti->ti_ack, tp->snd_max))

			goto dropwithreset;

		tp->t_state = TCPS_ESTABLISHED;

		 

		tp->snd_una=ti->ti_ack;

		if (so->so_state & SS_CTL) {

		   

		  ret = tcp_ctl(so);

		  if (ret == 1) {

		    soisfconnected(so);

		    so->so_state &= ~SS_CTL;    

		  } else if (ret == 2) {

		    so->so_state &= SS_PERSISTENT_MASK;

		    so->so_state |= SS_NOFDREF;  

		  } else {

		    needoutput = 1;

		    tp->t_state = TCPS_FIN_WAIT_1;

		  }

		} else {

		  soisfconnected(so);

		}



		(void) tcp_reass(tp, (struct tcpiphdr *)0, (struct mbuf *)0);

		tp->snd_wl1 = ti->ti_seq - 1;

		 

		goto synrx_to_est;

		 



	 

	case TCPS_ESTABLISHED:

	case TCPS_FIN_WAIT_1:

	case TCPS_FIN_WAIT_2:

	case TCPS_CLOSE_WAIT:

	case TCPS_CLOSING:

	case TCPS_LAST_ACK:

	case TCPS_TIME_WAIT:



		if (SEQ_LEQ(ti->ti_ack, tp->snd_una)) {

			if (ti->ti_len == 0 && tiwin == tp->snd_wnd) {

			  DEBUG_MISC((dfd, " dup ack  m = %lx  so = %lx\n",

				      (long )m, (long )so));

				 

				if (tp->t_timer[TCPT_REXMT] == 0 ||

				    ti->ti_ack != tp->snd_una)

					tp->t_dupacks = 0;

				else if (++tp->t_dupacks == TCPREXMTTHRESH) {

					tcp_seq onxt = tp->snd_nxt;

					u_int win =

					    min(tp->snd_wnd, tp->snd_cwnd) / 2 /

						tp->t_maxseg;



					if (win < 2)

						win = 2;

					tp->snd_ssthresh = win * tp->t_maxseg;

					tp->t_timer[TCPT_REXMT] = 0;

					tp->t_rtt = 0;

					tp->snd_nxt = ti->ti_ack;

					tp->snd_cwnd = tp->t_maxseg;

					(void) tcp_output(tp);

					tp->snd_cwnd = tp->snd_ssthresh +

					       tp->t_maxseg * tp->t_dupacks;

					if (SEQ_GT(onxt, tp->snd_nxt))

						tp->snd_nxt = onxt;

					goto drop;

				} else if (tp->t_dupacks > TCPREXMTTHRESH) {

					tp->snd_cwnd += tp->t_maxseg;

					(void) tcp_output(tp);

					goto drop;

				}

			} else

				tp->t_dupacks = 0;

			break;

		}

	synrx_to_est:

		 

		if (tp->t_dupacks > TCPREXMTTHRESH &&

		    tp->snd_cwnd > tp->snd_ssthresh)

			tp->snd_cwnd = tp->snd_ssthresh;

		tp->t_dupacks = 0;

		if (SEQ_GT(ti->ti_ack, tp->snd_max)) {

			goto dropafterack;

		}

		acked = ti->ti_ack - tp->snd_una;



		 

		if (tp->t_rtt && SEQ_GT(ti->ti_ack, tp->t_rtseq))

			tcp_xmit_timer(tp,tp->t_rtt);



		 

		if (ti->ti_ack == tp->snd_max) {

			tp->t_timer[TCPT_REXMT] = 0;

			needoutput = 1;

		} else if (tp->t_timer[TCPT_PERSIST] == 0)

			tp->t_timer[TCPT_REXMT] = tp->t_rxtcur;

		 

		{

		  register u_int cw = tp->snd_cwnd;

		  register u_int incr = tp->t_maxseg;



		  if (cw > tp->snd_ssthresh)

		    incr = incr * incr / cw;

		  tp->snd_cwnd = min(cw + incr, TCP_MAXWIN<<tp->snd_scale);

		}

		if (acked > so->so_snd.sb_cc) {

			tp->snd_wnd -= so->so_snd.sb_cc;

			sbdrop(&so->so_snd, (int )so->so_snd.sb_cc);

			ourfinisacked = 1;

		} else {

			sbdrop(&so->so_snd, acked);

			tp->snd_wnd -= acked;

			ourfinisacked = 0;

		}

		tp->snd_una = ti->ti_ack;

		if (SEQ_LT(tp->snd_nxt, tp->snd_una))

			tp->snd_nxt = tp->snd_una;



		switch (tp->t_state) {



		 

		case TCPS_FIN_WAIT_1:

			if (ourfinisacked) {

				 

				if (so->so_state & SS_FCANTRCVMORE) {

					tp->t_timer[TCPT_2MSL] = TCP_MAXIDLE;

				}

				tp->t_state = TCPS_FIN_WAIT_2;

			}

			break;



	 	 

		case TCPS_CLOSING:

			if (ourfinisacked) {

				tp->t_state = TCPS_TIME_WAIT;

				tcp_canceltimers(tp);

				tp->t_timer[TCPT_2MSL] = 2 * TCPTV_MSL;

			}

			break;



		 

		case TCPS_LAST_ACK:

			if (ourfinisacked) {

                                tcp_close(tp);

				goto drop;

			}

			break;



		 

		case TCPS_TIME_WAIT:

			tp->t_timer[TCPT_2MSL] = 2 * TCPTV_MSL;

			goto dropafterack;

		}

	}  



step6:

	 

	if ((tiflags & TH_ACK) &&

	    (SEQ_LT(tp->snd_wl1, ti->ti_seq) ||

	    (tp->snd_wl1 == ti->ti_seq && (SEQ_LT(tp->snd_wl2, ti->ti_ack) ||

	    (tp->snd_wl2 == ti->ti_ack && tiwin > tp->snd_wnd))))) {

		tp->snd_wnd = tiwin;

		tp->snd_wl1 = ti->ti_seq;

		tp->snd_wl2 = ti->ti_ack;

		if (tp->snd_wnd > tp->max_sndwnd)

			tp->max_sndwnd = tp->snd_wnd;

		needoutput = 1;

	}



	 

	if ((tiflags & TH_URG) && ti->ti_urp &&

	    TCPS_HAVERCVDFIN(tp->t_state) == 0) {

		 

		if (ti->ti_urp + so->so_rcv.sb_cc > so->so_rcv.sb_datalen) {

			ti->ti_urp = 0;

			tiflags &= ~TH_URG;

			goto dodata;

		}

		 

		if (SEQ_GT(ti->ti_seq+ti->ti_urp, tp->rcv_up)) {

			tp->rcv_up = ti->ti_seq + ti->ti_urp;

			so->so_urgc =  so->so_rcv.sb_cc +

				(tp->rcv_up - tp->rcv_nxt);  

			tp->rcv_up = ti->ti_seq + ti->ti_urp;



		}

	} else

		 

		if (SEQ_GT(tp->rcv_nxt, tp->rcv_up))

			tp->rcv_up = tp->rcv_nxt;

dodata:



	 

	if (ti->ti_len && (unsigned)ti->ti_len <= 5 &&

	    ((struct tcpiphdr_2 *)ti)->first_char == (char)27) {

		tp->t_flags |= TF_ACKNOW;

	}



	 

	if ((ti->ti_len || (tiflags&TH_FIN)) &&

	    TCPS_HAVERCVDFIN(tp->t_state) == 0) {

		TCP_REASS(tp, ti, m, so, tiflags);

	} else {

		m_free(m);

		tiflags &= ~TH_FIN;

	}



	 

	if (tiflags & TH_FIN) {

		if (TCPS_HAVERCVDFIN(tp->t_state) == 0) {

			 

			sofwdrain(so);



			tp->t_flags |= TF_ACKNOW;

			tp->rcv_nxt++;

		}

		switch (tp->t_state) {



	 	 

		case TCPS_SYN_RECEIVED:

		case TCPS_ESTABLISHED:

		  if(so->so_emu == EMU_CTL)         

		    tp->t_state = TCPS_LAST_ACK;

		  else

		    tp->t_state = TCPS_CLOSE_WAIT;

		  break;



	 	 

		case TCPS_FIN_WAIT_1:

			tp->t_state = TCPS_CLOSING;

			break;



	 	 

		case TCPS_FIN_WAIT_2:

			tp->t_state = TCPS_TIME_WAIT;

			tcp_canceltimers(tp);

			tp->t_timer[TCPT_2MSL] = 2 * TCPTV_MSL;

			break;



		 

		case TCPS_TIME_WAIT:

			tp->t_timer[TCPT_2MSL] = 2 * TCPTV_MSL;

			break;

		}

	}



	 

	if (needoutput || (tp->t_flags & TF_ACKNOW)) {

		(void) tcp_output(tp);

	}

	return;



dropafterack:

	 

	if (tiflags & TH_RST)

		goto drop;

	m_free(m);

	tp->t_flags |= TF_ACKNOW;

	(void) tcp_output(tp);

	return;



dropwithreset:

	 

	if (tiflags & TH_ACK)

		tcp_respond(tp, ti, m, (tcp_seq)0, ti->ti_ack, TH_RST);

	else {

		if (tiflags & TH_SYN) ti->ti_len++;

		tcp_respond(tp, ti, m, ti->ti_seq+ti->ti_len, (tcp_seq)0,

		    TH_RST|TH_ACK);

	}



	return;



drop:

	 

	m_free(m);

}
