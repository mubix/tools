/***************************************************************************
 * portreasons.h -- Verbose packet-level information on port states        *
 *                                                                         *
 ***********************IMPORTANT NMAP LICENSE TERMS************************
 *                                                                         *
 * The Nmap Security Scanner is (C) 1996-2012 Insecure.Com LLC. Nmap is    *
 * also a registered trademark of Insecure.Com LLC.  This program is free  *
 * software; you may redistribute and/or modify it under the terms of the  *
 * GNU General Public License as published by the Free Software            *
 * Foundation; Version 2 with the clarifications and exceptions described  *
 * below.  This guarantees your right to use, modify, and redistribute     *
 * this software under certain conditions.  If you wish to embed Nmap      *
 * technology into proprietary software, we sell alternative licenses      *
 * (contact sales@insecure.com).  Dozens of software vendors already       *
 * license Nmap technology such as host discovery, port scanning, OS       *
 * detection, version detection, and the Nmap Scripting Engine.            *
 *                                                                         *
 * Note that the GPL places important restrictions on "derived works", yet *
 * it does not provide a detailed definition of that term.  To avoid       *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * "derivative work" for the purpose of this license if it does any of the *
 * following:                                                              *
 * o Integrates source code from Nmap                                      *
 * o Reads or includes Nmap copyrighted data files, such as                *
 *   nmap-os-db or nmap-service-probes.                                    *
 * o Executes Nmap and parses the results (as opposed to typical shell or  *
 *   execution-menu apps, which simply display raw Nmap output and so are  *
 *   not derivative works.)                                                *
 * o Integrates/includes/aggregates Nmap into a proprietary executable     *
 *   installer, such as those produced by InstallShield.                   *
 * o Links to a library or executes a program that does any of the above   *
 *                                                                         *
 * The term "Nmap" should be taken to also include any portions or derived *
 * works of Nmap, as well as other software we distribute under this       *
 * license such as Zenmap, Ncat, and Nping.  This list is not exclusive,   *
 * but is meant to clarify our interpretation of derived works with some   *
 * common examples.  Our interpretation applies only to Nmap--we don't     *
 * speak for other people's GPL works.                                     *
 *                                                                         *
 * If you have any questions about the GPL licensing restrictions on using *
 * Nmap in non-GPL works, we would be happy to help.  As mentioned above,  *
 * we also offer alternative license to integrate Nmap into proprietary    *
 * applications and appliances.  These contracts have been sold to dozens  *
 * of software vendors, and generally include a perpetual license as well  *
 * as providing for priority support and updates.  They also fund the      *
 * continued development of Nmap.  Please email sales@insecure.com for     *
 * further information.                                                    *
 *                                                                         *
 * As a special exception to the GPL terms, Insecure.Com LLC grants        *
 * permission to link the code of this program with any version of the     *
 * OpenSSL library which is distributed under a license identical to that  *
 * listed in the included docs/licenses/OpenSSL.txt file, and distribute   *
 * linked combinations including the two. You must obey the GNU GPL in all *
 * respects for all of the code used other than OpenSSL.  If you modify    *
 * this file, you may extend this exception to your version of the file,   *
 * but you are not obligated to do so.                                     *
 *                                                                         *
 * If you received these files with a written license agreement or         *
 * contract stating terms other than the terms above, then that            *
 * alternative license agreement takes precedence over these comments.     *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes (none     *
 * have been found so far).                                                *
 *                                                                         *
 * Source code also allows you to port Nmap to new platforms, fix bugs,    *
 * and add new features.  You are highly encouraged to send your changes   *
 * to the dev@nmap.org mailing list for possible incorporation into the    *
 * main distribution.  By sending these changes to Fyodor or one of the    *
 * Insecure.Org development mailing lists, or checking them into the Nmap  *
 * source code repository, it is understood (unless you specify otherwise) *
 * that you are offering the Nmap Project (Insecure.Com LLC) the           *
 * unlimited, non-exclusive right to reuse, modify, and relicense the      *
 * code.  Nmap will always be available Open Source, but this is important *
 * because the inability to relicense code has caused devastating problems *
 * for other Free Software projects (such as KDE and NASM).  We also       *
 * occasionally relicense the code to third parties as discussed above.    *
 * If you wish to specify special license conditions of your               *
 * contributions, just say so when you send them.                          *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Nmap      *
 * license file for more details (it's in a COPYING file included with     *
 * Nmap, and also available from https://svn.nmap.org/nmap/COPYING         *
 *                                                                         *
 ***************************************************************************/

/*
 * Written by Eddie Bell <ejlbell@gmail.com> 2007
 * Modified by Colin Rice <dah4k0r@gmail.com> 2011
 */

#ifndef REASON_H
#define REASON_H

#include "nmap.h"

#ifdef WIN32
#include "winsock2.h"
#else
#include <netinet/in.h>
#endif

#include <sys/types.h>
#include <map>
class Target;
class PortList;

typedef unsigned short reason_t;

/* Holds various string outputs of a reason  *
 * Stored inside a map which maps enum_codes *
 * to reason_strings				     */
class reason_string {
public:
    //Required for map
    reason_string();
    reason_string(const char * singular, const char * plural);
    const char * singular;
    const char * plural;
};

/* stored inside a Port Object and describes
 * why a port is in a specific state */
typedef struct port_reason {
	reason_t reason_id;
	union {
		struct sockaddr_in in;
		struct sockaddr_in6 in6;
		struct sockaddr sockaddr;
	} ip_addr;
	unsigned short ttl;

	int set_ip_addr(const struct sockaddr_storage *ss);
} state_reason_t;

/* used to calculate state reason summaries.
 * I.E 10 ports filter because of 10 no-responses */
typedef struct port_reason_summary {
	reason_t reason_id;
	unsigned int count;
	struct port_reason_summary *next;
} state_reason_summary_t;


enum reason_codes {
	ER_RESETPEER, ER_CONREFUSED, ER_CONACCEPT, 
	ER_SYNACK, ER_SYN, ER_UDPRESPONSE, ER_PROTORESPONSE, ER_ACCES, 

	ER_NETUNREACH, ER_HOSTUNREACH, ER_PROTOUNREACH,
	ER_PORTUNREACH, ER_ECHOREPLY, 

	ER_DESTUNREACH, ER_SOURCEQUENCH, ER_NETPROHIBITED,
	ER_HOSTPROHIBITED, ER_ADMINPROHIBITED,
	ER_TIMEEXCEEDED, ER_TIMESTAMPREPLY,

	ER_ADDRESSMASKREPLY, ER_NOIPIDCHANGE, ER_IPIDCHANGE,
	ER_ARPRESPONSE, ER_NDRESPONSE, ER_TCPRESPONSE, ER_NORESPONSE,
	ER_INITACK, ER_ABORT,
	ER_LOCALHOST, ER_SCRIPT, ER_UNKNOWN, ER_USER,
	ER_NOROUTE, ER_BEYONDSCOPE, ER_REJECTROUTE, ER_PARAMPROBLEM,
};

/* A map of reason_codes to plural and singular *
 * versions of the error string                 */
class reason_map_type{
private:
    std::map<reason_codes,reason_string > reason_map;
public:
    reason_map_type();
    std::map<reason_codes,reason_string>::iterator find(const reason_codes& x){
        std::map<reason_codes,reason_string>::iterator itr = reason_map.find(x);
        if(itr == reason_map.end())
            return reason_map.find(ER_UNKNOWN);
        return itr;
    };
};

/* Function to translate ICMP code and typ to reason code */
reason_codes icmp_to_reason(u8 proto, int icmp_type, int icmp_code);

/* passed to the print_state_summary.
 * STATE_REASON_EMPTY will append to the current line, prefixed with " because of"
 * STATE_REASON_FULL will start a new line, prefixed with "Reason:" */
#define STATE_REASON_EMPTY 0
#define STATE_REASON_FULL 1

/* Passed to reason_str to determine if string should be in
 * plural of singular form */
#define SINGULAR 1
#define PLURAL 2

void state_reason_init(state_reason_t *reason);

/* converts a reason_id to a string. number represents the
 * amount ports in a given state. If there is more then one
 * port the plural is used, otherwise the singular is used. */
const char *reason_str(reason_t reason_id, unsigned int number);

/* Displays reason summary messages */
void print_state_summary(PortList *Ports, unsigned short type);
void print_xml_state_summary(PortList *Ports, int state);

/* Build an output string based on reason and source ip address.
 * Uses static return value so previous values will be over
 * written by subsequent calls */
char *port_reason_str(state_reason_t r);
char *target_reason_str(Target *t);

#endif

