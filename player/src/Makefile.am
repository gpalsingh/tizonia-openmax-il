# Copyright (C) 2011-2017 Aratelia Limited - Juan A. Rubio
#
# This file is part of Tizonia
#
# Tizonia is free software: you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# Tizonia is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Tizonia.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS = tizonia

noinst_HEADERS = \
	tizomxutil.hpp \
	tizplayapp.hpp \
	tizprogramopts.hpp \
	tizgraphutil.hpp \
	tizgraphutil.inl \
	tizgraphcback.hpp \
	tizdaemon.hpp \
	tizprobe.hpp \
	tizplaylist.hpp \
	tizgraphfactory.hpp \
	tizgraphtypes.hpp \
	tizgraphconfig.hpp \
	tizgraphmgrcmd.hpp \
	tizgraphmgrops.hpp \
	tizgraphmgrfsm.hpp \
	tizgraphmgr.hpp \
	tizgraphfsm.hpp \
	tizgraphevt.hpp \
	tizgraphguard.hpp \
	tizgraphaction.hpp \
	tizgraphstate.hpp \
	tizgraphcmd.hpp \
	tizgraphops.hpp \
	tizgraph.hpp \
	tizgraphmgrcaps.hpp \
	tizplaybackstatus.hpp \
	tizplaybackevents.hpp \
	decoders/tizdecgraphmgr.hpp \
	decoders/tizdecgraph.hpp \
	decoders/tizmp3graph.hpp \
	decoders/tizaacgraph.hpp \
	decoders/tizopusgraph.hpp \
	decoders/tizoggopusgraph.hpp \
	decoders/tizvorbisgraph.hpp \
	decoders/tizflacgraph.hpp \
	decoders/tizoggflacgraph.hpp \
	decoders/tizpcmgraph.hpp \
	decoders/tizmpeggraph.hpp \
	httpserv/tizhttpservconfig.hpp \
	httpserv/tizhttpservgraph.hpp \
	httpserv/tizhttpservgraphfsm.hpp \
	httpserv/tizhttpservgraphops.hpp \
	httpserv/tizhttpservmgr.hpp \
	httpclnt/tizhttpclntmgr.hpp \
	httpclnt/tizhttpclntgraph.hpp \
	httpclnt/tizhttpclntgraphfsm.hpp \
	httpclnt/tizhttpclntgraphops.hpp \
	services/tizservicegraph.hpp \
	services/tizservicegraphfsm.hpp \
	services/spotify/tizspotifygraph.hpp \
	services/spotify/tizspotifygraphfsm.hpp \
	services/spotify/tizspotifygraphops.hpp \
	services/spotify/tizspotifyconfig.hpp \
	services/spotify/tizspotifymgr.hpp \
	services/googlemusic/tizgmusicgraph.hpp \
	services/googlemusic/tizgmusicgraphops.hpp \
	services/googlemusic/tizgmusicconfig.hpp \
	services/googlemusic/tizgmusicmgr.hpp \
	services/soundcloud/tizscloudgraph.hpp \
	services/soundcloud/tizscloudgraphops.hpp \
	services/soundcloud/tizscloudconfig.hpp \
	services/soundcloud/tizscloudmgr.hpp \
	services/dirble/tizdirblegraph.hpp \
	services/dirble/tizdirblegraphfsm.hpp \
	services/dirble/tizdirblegraphops.hpp \
	services/dirble/tizdirbleconfig.hpp \
	services/dirble/tizdirblemgr.hpp \
	services/youtube/tizyoutubegraph.hpp \
	services/youtube/tizyoutubegraphfsm.hpp \
	services/youtube/tizyoutubegraphops.hpp \
	services/youtube/tizyoutubeconfig.hpp \
	services/youtube/tizyoutubemgr.hpp \
	mpris/tizmpriscbacks.hpp \
	mpris/tizmprisprops.hpp \
	mpris/tizmprisif.hpp \
	mpris/tizmprismgr.hpp


tizonia_SOURCES = \
	main.cpp \
	tizplayapp.cpp \
	tizprogramopts.cpp \
	tizomxutil.cpp \
	tizgraphutil.cpp \
	tizgraphcback.cpp \
	tizdaemon.cpp \
	tizprobe.cpp \
	tizplaylist.cpp \
	tizgraphfactory.cpp \
	tizgraphmgrcmd.cpp \
	tizgraphmgrops.cpp \
	tizgraphmgrfsm.cpp \
	tizgraphmgr.cpp \
	tizgraphfsm.cpp \
	tizgraphops.cpp \
	tizgraphcmd.cpp \
	tizgraph.cpp \
	decoders/tizdecgraphmgr.cpp \
	decoders/tizdecgraph.cpp \
	decoders/tizmp3graph.cpp \
	decoders/tizaacgraph.cpp \
	decoders/tizopusgraph.cpp \
	decoders/tizoggopusgraph.cpp \
	decoders/tizvorbisgraph.cpp \
	decoders/tizflacgraph.cpp \
	decoders/tizoggflacgraph.cpp \
	decoders/tizpcmgraph.cpp \
	decoders/tizmpeggraph.cpp \
	httpserv/tizhttpservmgr.cpp \
	httpserv/tizhttpservgraph.cpp \
	httpserv/tizhttpservgraphfsm.cpp \
	httpserv/tizhttpservgraphops.cpp \
	httpclnt/tizhttpclntmgr.cpp \
	httpclnt/tizhttpclntgraph.cpp \
	httpclnt/tizhttpclntgraphfsm.cpp \
	httpclnt/tizhttpclntgraphops.cpp \
	services/tizservicegraph.cpp \
	services/tizservicegraphfsm.cpp \
	services/spotify/tizspotifygraph.cpp \
	services/spotify/tizspotifygraphfsm.cpp \
	services/spotify/tizspotifygraphops.cpp \
	services/spotify/tizspotifymgr.cpp \
	services/googlemusic/tizgmusicgraph.cpp \
	services/googlemusic/tizgmusicgraphops.cpp \
	services/googlemusic/tizgmusicmgr.cpp \
	services/soundcloud/tizscloudgraph.cpp \
	services/soundcloud/tizscloudgraphops.cpp \
	services/soundcloud/tizscloudmgr.cpp \
	services/dirble/tizdirblegraph.cpp \
	services/dirble/tizdirblegraphfsm.cpp \
	services/dirble/tizdirblegraphops.cpp \
	services/dirble/tizdirblemgr.cpp \
	services/youtube/tizyoutubegraph.cpp \
	services/youtube/tizyoutubegraphfsm.cpp \
	services/youtube/tizyoutubegraphops.cpp \
	services/youtube/tizyoutubemgr.cpp \
	tizplaybackevents.cpp \
	mpris/tizmprismgr.cpp \
	mpris/tizmprisprops.cpp \
	mpris/tizmprisif.cpp

tizonia_CPPFLAGS = \
	@BOOST_CPPFLAGS@ \
	@TIZILHEADERS_CFLAGS@ \
	@TIZPLATFORM_CFLAGS@ \
	-I$(top_srcdir)/dbus \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/services \
	-I/usr/include/taglib \
	@LIBMEDIAINFO_CFLAGS@ \
	@DBUS_CFLAGS@ \
	-D__STDC_CONSTANT_MACROS

tizonia_LDADD = \
	@BOOST_PROGRAM_OPTIONS_LIB@ \
	@BOOST_SYSTEM_LIB@ \
	@BOOST_FILESYSTEM_LIB@ \
	@BOOST_THREAD_LIB@ \
	-ltag \
	@LIBMEDIAINFO_LIBS@ \
	@DBUS_LIBS@ \
	@TIZPLATFORM_LIBS@ \
	@TIZCORE_LIBS@
