/******************************************************************
*
*	CyberLink for C
*
*	Copyright (C) Satoshi Konno 2005
*
*       Copyright (C) 2006 Nokia Corporation. All rights reserved.
*
*       This is licensed under BSD-style license,
*       see file COPYING.
*
*	File: chttpmu_socket.c
*
*	Revision:
*
*	06/10/05
*		- first revision
*
******************************************************************/

#include "cssdp_server.h"
#include "clog.h"

/****************************************
* cg_upnp_httpu_socket_recv
****************************************/

int cg_upnp_httpu_socket_recv(CgUpnpHttpMuSocket *sock, CgUpnpSSDPPacket *ssdpPkt)
{
	CgDatagramPacket *dgmPkt;
	char *ssdpData;
	int recvLen;
	
	cg_log_debug_l4("Entering...\n");

	dgmPkt = cg_upnp_ssdp_packet_getdatagrampacket(ssdpPkt);
	recvLen = cg_socket_recv(sock, dgmPkt);
	
	if (recvLen <= 0)
		return recvLen;

	ssdpData = cg_socket_datagram_packet_getdata(dgmPkt);

#if defined(__rda_debug_log__) && defined(__rda_cust_httpu_recv_debug__)
	rdadebug_log_cg_upnp_httpu_socket_recv(ssdpPkt);
#endif

	cg_upnp_ssdp_packet_setheader(ssdpPkt, ssdpData);
	cg_socket_datagram_packet_setdata(dgmPkt, NULL);
	
	return recvLen;

	cg_log_debug_l4("Leaving...\n");
}
