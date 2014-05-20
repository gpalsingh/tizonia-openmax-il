/**
 * Copyright (C) 2011-2014 Aratelia Limited - Juan A. Rubio
 *
 * This file is part of Tizonia
 *
 * Tizonia is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Tizonia is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tizonia.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file   httpsrc.c
 * @author Juan A. Rubio <juan.rubio@aratelia.com>
 *
 * @brief  Tizonia OpenMAX IL - HTTP streaming client component
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <string.h>

#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OMX_Types.h>

#include <tizplatform.h>

#include <tizport.h>
#include <tizscheduler.h>

#include "httpsrcprc.h"
#include "httpsrc.h"

#ifdef TIZ_LOG_CATEGORY_NAME
#undef TIZ_LOG_CATEGORY_NAME
#define TIZ_LOG_CATEGORY_NAME "tiz.http_source"
#endif

static OMX_VERSIONTYPE http_source_version = { {1, 0, 0, 0} };

static OMX_PTR
instantiate_pcm_port (OMX_HANDLETYPE ap_hdl)
{
  OMX_AUDIO_PARAM_PCMMODETYPE pcmmode;
  OMX_AUDIO_CONFIG_VOLUMETYPE volume;
  OMX_AUDIO_CONFIG_MUTETYPE mute;
  OMX_AUDIO_CODINGTYPE encodings[] = {
    OMX_AUDIO_CodingPCM,
    OMX_AUDIO_CodingMax
  };
  tiz_port_options_t port_opts = {
    OMX_PortDomainAudio,
    OMX_DirInput,
    ARATELIA_HTTP_SOURCE_PORT_MIN_BUF_COUNT,
    ARATELIA_HTTP_SOURCE_PORT_MIN_BUF_SIZE,
    ARATELIA_HTTP_SOURCE_PORT_NONCONTIGUOUS,
    ARATELIA_HTTP_SOURCE_PORT_ALIGNMENT,
    ARATELIA_HTTP_SOURCE_PORT_SUPPLIERPREF,
    {ARATELIA_HTTP_SOURCE_PORT_INDEX, NULL, NULL, NULL},
    -1                          /* use -1 for now */
  };

  /* Instantiate the pcm port */
  pcmmode.nSize              = sizeof (OMX_AUDIO_PARAM_PCMMODETYPE);
  pcmmode.nVersion.nVersion  = OMX_VERSION;
  pcmmode.nPortIndex         = ARATELIA_HTTP_SOURCE_PORT_INDEX;
  pcmmode.nChannels          = 2;
  pcmmode.eNumData           = OMX_NumericalDataSigned;
  pcmmode.eEndian            = OMX_EndianLittle;
  pcmmode.bInterleaved       = OMX_TRUE;
  pcmmode.nBitPerSample      = 16;
  pcmmode.nSamplingRate      = 48000;
  pcmmode.ePCMMode           = OMX_AUDIO_PCMModeLinear;
  pcmmode.eChannelMapping[0] = OMX_AUDIO_ChannelLF;
  pcmmode.eChannelMapping[1] = OMX_AUDIO_ChannelRF;

  volume.nSize             = sizeof (OMX_AUDIO_CONFIG_VOLUMETYPE);
  volume.nVersion.nVersion = OMX_VERSION;
  volume.nPortIndex        = ARATELIA_HTTP_SOURCE_PORT_INDEX;
  volume.bLinear           = OMX_FALSE;
  volume.sVolume.nValue    = ARATELIA_HTTP_SOURCE_DEFAULT_VOLUME_VALUE;
  volume.sVolume.nMin      = ARATELIA_HTTP_SOURCE_MIN_VOLUME_VALUE;
  volume.sVolume.nMax      = ARATELIA_HTTP_SOURCE_MAX_VOLUME_VALUE;

  mute.nSize             = sizeof (OMX_AUDIO_CONFIG_MUTETYPE);
  mute.nVersion.nVersion = OMX_VERSION;
  mute.nPortIndex        = ARATELIA_HTTP_SOURCE_PORT_INDEX;
  mute.bMute             = OMX_FALSE;

  return factory_new (tiz_get_type (ap_hdl, "tizpcmport"), &port_opts,
                      &encodings, &pcmmode, &volume, &mute);
}

static OMX_PTR
instantiate_config_port (OMX_HANDLETYPE ap_hdl)
{
  return factory_new (tiz_get_type (ap_hdl, "tizconfigport"),
                      NULL,       /* this port does not take options */
                      ARATELIA_HTTP_SOURCE_COMPONENT_NAME,
                      http_source_version);
}

static OMX_PTR
instantiate_processor (OMX_HANDLETYPE ap_hdl)
{
  return factory_new (tiz_get_type (ap_hdl, "httpsrcprc"));
}

OMX_ERRORTYPE
OMX_ComponentInit (OMX_HANDLETYPE ap_hdl)
{
  tiz_role_factory_t role_factory;
  const tiz_role_factory_t *rf_list[] = { &role_factory };
  tiz_type_factory_t httpsrcprc_type;
  const tiz_type_factory_t *tf_list[] = { &httpsrcprc_type };

  strcpy ((OMX_STRING) role_factory.role, ARATELIA_HTTP_SOURCE_DEFAULT_ROLE);
  role_factory.pf_cport   = instantiate_config_port;
  role_factory.pf_port[0] = instantiate_pcm_port;
  role_factory.nports     = 1;
  role_factory.pf_proc    = instantiate_processor;

  strcpy ((OMX_STRING) httpsrcprc_type.class_name, "httpsrcprc_class");
  httpsrcprc_type.pf_class_init = httpsrc_prc_class_init;
  strcpy ((OMX_STRING) httpsrcprc_type.object_name, "httpsrcprc");
  httpsrcprc_type.pf_object_init = httpsrc_prc_init;

  /* Initialize the component infrastructure */
  tiz_check_omx_err (tiz_comp_init (ap_hdl, ARATELIA_HTTP_SOURCE_COMPONENT_NAME));

  /* Register the "httpsrcprc" class */
  tiz_check_omx_err (tiz_comp_register_types (ap_hdl, tf_list, 1));

  /* Register the component role(s) */
  tiz_check_omx_err (tiz_comp_register_roles (ap_hdl, rf_list, 1));

  return OMX_ErrorNone;
}