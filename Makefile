# *******************************************************************************************
# * Copyright (c) 2006-7 Laboratorio di Sistemi di Elaborazione e Bioingegneria Informatica *
# *                      Universita' Campus BioMedico - Italy                               *
# *                                                                                         *
# * This program is free software; you can redistribute it and/or modify it under the terms *
# * of the GNU General Public License as published by the Free Software Foundation; either  *
# * version 2 of the License, or (at your option) any later version.                        *
# *                                                                                         *
# * This program is distributed in the hope that it will be useful, but WITHOUT ANY         *
# * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 	    *
# * PARTICULAR PURPOSE. See the GNU General Public License for more details.                *
# *                                                                                         *
# * You should have received a copy of the GNU General Public License along with this       *
# * program; if not, write to the:                                                          *
# * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,                    *
# * MA  02111-1307, USA.                                                                    *
# *                                                                                         *
# * In addition, as a special exception, the copyright holders give permission to link the  *
# * code of portions of this program with the OpenSSL library under certain conditions as   *
# * described in each individual source file, and distribute linked combinations including  * 
# * the two. You must obey the GNU General Public License in all respects for all of the    *
# * code used other than OpenSSL.  If you modify file(s) with this exception, you may       *
# * extend this exception to your version of the file(s), but you are not obligated to do   *
# * so.  If you do not wish to do so, delete this exception statement from your version.    *
# * If you delete this exception statement from all source files in the program, then also  *
# * delete it here.                                                                         *
# * 											    *
# * --------------------------------------------------------------------------------------- *
# * Project:  Capwap                                                                        *
# *                                                                                         *
# * Author :  Ludovico Rossi (ludo@bluepixysw.com)                                          *  
# *           Del Moro Andrea (andrea_delmoro@libero.it)                                    *
# *           Giovannini Federica (giovannini.federica@gmail.com)                           *
# *           Massimo Vellucci (m.vellucci@unicampus.it)                                    *
# *	      Donato Capitella (d.capitella@gmail.com)  	                            *
# *	      Elena Agostini (elena.ago@gmail.com)					    *
# *******************************************************************************************



# CC = gcc 
# RM = /bin/rm -f 

LDFLAGS = -lssl -lcrypto -lpthread -ldl -D_REENTRANT

#Elena Agostini: libnl
LDFLAGS += -lnl-genl-3 -lnl-3
LIB_PATH = ${STAGING_DIR}/usr/lib
INC_PATH = ${STAGING_DIR}/usr/include/libnl3

#LDFLAGS = /usr/lib/libefence.a ./static/libssl.a ./static/libcrypto.a -lpthread -ldl -D_REENTRANT
#LDFLAGS = ./static/libssl.a ./static/libcrypto.a -lpthread -ldl -D_REENTRANT

#CFLAGS =  -Wall -g -O0 -D_REENTRANT
CFLAGS += -DCW_NO_DTLS -DCW_NO_DTLSCWParseConfigurationUpdateRequest
#CFLAGS += -DSPLIT_MAC
CFLAGS += -fgnu89-inline
#DTLS Data Channel
#CFLAGS += -DCW_DTLS_DATA_CHANNEL

# Memory leak
#LDFLAGS += ../dmalloc-5.5.0/libdmallocth.a
#CFLAGS += -DDMALLOC

# Capwap Debugging
CFLAGS += -DCW_DEBUGGING
CFLAGS += -DWRITE_STD_OUTPUT
#CFLAGS += -DSOFTMAC
CFLAGS += -DOPENSSL_NO_KRB5

#OpenSSL inc files path
# OPENSSL_INCLUDE = -I./include/  #Openssl include files
OPENSSL_INCLUDE = -I${STAGING_DIR}/usr/include/openssl
CFLAGS += $(OPENSSL_INCLUDE)

CFLAGS += -I$(INC_PATH)
CFLAGS += -I./HostapdHeaders/utils/

# list of generated object files for AC. 
AC_OBJS = AC.o ACConfigFile.o ACMainLoop.o ACDiscoveryState.o ACJoinState.o \
	ACConfigureState.o ACDataCheckState.o ACRunState.o ACProtocol_User.o \
	ACRetransmission.o CWCommon.o CWConfigFile.o CWErrorHandling.o CWList.o \
	CWLog.o ACMultiHomedSocket.o ACProtocol.o CWSafeList.o CWNetwork.o CWProtocol.o \
	CWRandom.o CWSecurity.o CWOpenSSLBio.o CWStevens.o CWThread.o CWBinding.o CWVendorPayloadsAC.o \
	ACBinding.o ACInterface.o ACSettingsFile.o timerlib.o tap.o \
	ACIEEEConfigurationState.o CW80211InformationElements.o CWTunnel.o CWAVL.o \
	./HostapdHeaders/utils/os_unix.o \

# list of generated object files for WTP.
WTP_OBJS = WTP.o WTPFrameReceive.o WTPFreqStatsReceive.o WTPStatsReceive.o WTPConfigFile.o WTPProtocol.o WTPProtocol_User.o \
	WTPDiscoveryState.o WTPJoinState.o WTPConfigureState.o WTPDataCheckState.o WTPRunState.o WTPRunStateCheck.o \
	WTPRetransmission.o WTPSulkingState.o CWCommon.o CWConfigFile.o CWErrorHandling.o CWSafeList.o CWList.o CWLog.o CWNetwork.o \
	CWProtocol.o CWRandom.o CWSecurity.o CWOpenSSLBio.o CWStevens.o CWThread.o CWBinding.o CWVendorPayloadsWTP.o WTPBinding.o \
	WTPDriverInteraction.o WTPSettingsFile.o timerlib.o \
	WTPRadio.o WTPNL80211DriverCallback.o WTPNL80211Driver.o WTPNL80211Netlink.o WTPIEEEConfigurationState.o CW80211ManagementFrame.o CW80211InformationElements.o CWTunnel.o CWAVL.o \
	./HostapdHeaders/utils/os_unix.o \
	
WUA_OBJS = WUA.o
 
AC_SRCS = $(AC_OBJS:.o=.c) 
WTP_SRCS = $(WTP_OBJS:.o=.c)
WUA_SRCS = $(WUA:OBJS:.o=.c)

AC_DEPS := $(AC_OBJS:.o=.d)
WTP_DEPS := $(WTP_OBJS:.o=.d)
WUA_DEPS := $(WUA_OBJS:.o=.d)

# program executables. 
AC_NAME = AC 
WTP_NAME = WTP 
WUA_NAME = WUA

.PHONY: deps clean clean_libs libs

# top-level rule, to compile everything. 
all: $(AC_NAME) $(WTP_NAME) $(WUA_NAME)
# all: $(WTP_NAME)

$(AC_NAME): $(AC_OBJS) 
	$(CC) $(AC_OBJS) $(CFLAGS) $(OPENSSL_INCLUDE) $(LDFLAGS) -o $(AC_NAME) 
#-DSOFTMAC
$(WTP_NAME): $(WTP_OBJS) 
	$(CC) $(WTP_OBJS) $(CFLAGS) -L$(LIB_PATH) $(LDFLAGS) -o $(WTP_NAME) 

$(WUA_NAME): $(WUA_OBJS) 
	$(CC) $(WUA_OBJS) $(CFLAGS)  $(LDFLAGS) -o $(WUA_NAME) 

clean: 
	$(RM) $(AC_NAME) $(WTP_NAME) $(WUA_NAME) $(AC_OBJS) $(WTP_OBJS) $(WUA_OBJS) $(AC_DEPS) $(WTP_DEPS)

clean_deps:
	$(AC_DEPS) $(WTP_DEPS)
	
deps: $(AC_SRC) $(WTP_SRC)
	$(CC) -MD -E $(AC_SRCS) $(CFLAGS) >/dev/null
	$(CC) -MD -E $(WTP_SRCS) $(CFLAGS) >/dev/null

-include $(AC_DEPS)
-include $(WTP_DEPS)
