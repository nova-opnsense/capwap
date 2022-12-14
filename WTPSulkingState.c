/*******************************************************************************************
 * Copyright (c) 2006-7 Laboratorio di Sistemi di Elaborazione e Bioingegneria Informatica *
 *                      Universita' Campus BioMedico - Italy                               *
 *                                                                                         *
 * This program is free software; you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License as published by the Free Software Foundation; either  *
 * version 2 of the License, or (at your option) any later version.                        *
 *                                                                                         *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY         *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 	       *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.                *
 *                                                                                         *
 * You should have received a copy of the GNU General Public License along with this       *
 * program; if not, write to the:                                                          *
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,                    *
 * MA  02111-1307, USA.                                                                    *
 *                                                                                         *
 * In addition, as a special exception, the copyright holders give permission to link the  *
 * code of portions of this program with the OpenSSL library under certain conditions as   *
 * described in each individual source file, and distribute linked combinations including  *
 * the two. You must obey the GNU General Public License in all respects for all of the    *
 * code used other than OpenSSL.  If you modify file(s) with this exception, you may       *
 * extend this exception to your version of the file(s), but you are not obligated to do   *
 * so.  If you do not wish to do so, delete this exception statement from your version.    *
 * If you delete this exception statement from all source files in the program, then also  *
 * delete it here.                                                                         *
 *
 * --------------------------------------------------------------------------------------- *
 * Project:  Capwap                                                                        *
 *                                                                                         *
 * Author :  Ludovico Rossi (ludo@bluepixysw.com)                                          *
 *           Del Moro Andrea (andrea_delmoro@libero.it)                                    *
 *           Giovannini Federica (giovannini.federica@gmail.com)                           *
 *           Massimo Vellucci (m.vellucci@unicampus.it)                                    *
 *           Mauro Bisson (mauro.bis@gmail.com)                                            *
 *******************************************************************************************/

#include "CWWTP.h"

#ifdef DMALLOC
#include "../dmalloc-5.5.0/dmalloc.h"
#endif

#ifdef CW_DEBUGGING
int gCWSilentInterval = 5;
#else
int gCWSilentInterval = 30;
#endif

/*
 * WTP enters sulking when no AC is responding to Discovery Request.
 */
CWStateTransition CWWTPEnterSulking()
{
	struct timeval timeout, before, after, delta, newTimeout;

	log_debug("\n");
	log_debug("######### Sulking State #########");
	/*
	 * wait for Silent Interval and discard
	 * all the packets that are coming
	 */
	timeout.tv_sec = newTimeout.tv_sec = gCWSilentInterval;
	timeout.tv_usec = newTimeout.tv_usec = 0;

	gettimeofday(&before, NULL);

	log_debug("CW_REPEAT_FOREVER: CWWTPEnterSulking()");
	CW_REPEAT_FOREVER
	{

		/* check if something is available to read until newTimeout */
		if (CWNetworkTimedPollRead(gWTPSocket, &newTimeout))
		{
			/*
			 * success
			 * if there was no error, raise a "success error", so we can easily handle
			 * all the cases in the switch
			 */
			CWErrorRaise(CW_ERROR_SUCCESS, NULL);
		}

		switch (CWErrorGetLastErrorCode())
		{
		case CW_ERROR_TIME_EXPIRED:
			goto cw_sulk_time_over;
			break;
		case CW_ERROR_SUCCESS:
			/* there's something to read */
			{
				CWNetworkLev4Address addr;
				char buf[CW_BUFFER_SIZE];
				int readBytes;

				/* read and discard */
				if (!CWErr(CWNetworkReceiveUnsafe(gWTPSocket, buf, CW_BUFFER_SIZE, 0, &addr, &readBytes)))
				{
					return CW_QUIT;
				}
			}
		case CW_ERROR_INTERRUPTED:
			/*
			 *  something to read OR interrupted by the
			 *  system
			 *  wait for the remaining time (NetworkPoll
			 *  will be recalled with the remaining time)
			 */
			gettimeofday(&after, NULL);

			CWTimevalSubtract(&delta, &after, &before);
			if (CWTimevalSubtract(&newTimeout, &timeout, &delta) == 1)
			{
				/* negative delta: time is over */
				goto cw_sulk_time_over;
			}
			break;

		default:
			CWErrorHandleLast();
			goto cw_error;
			break;
		}
	}
cw_sulk_time_over:
	log_debug("End of Sulking Period");
cw_error:
	return CW_ENTER_DISCOVERY;
}
