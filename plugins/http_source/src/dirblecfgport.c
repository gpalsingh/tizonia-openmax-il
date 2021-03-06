/**
 * Copyright (C) 2011-2017 Aratelia Limited - Juan A. Rubio
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
 * @file   dirblecfgport.c
 * @author Juan A. Rubio <juan.rubio@aratelia.com>
 *
 * @brief A specialised config port class for the Dirble source component
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <string.h>
#include <limits.h>

#include <tizplatform.h>

#include "dirblecfgport.h"
#include "dirblecfgport_decls.h"

#ifdef TIZ_LOG_CATEGORY_NAME
#undef TIZ_LOG_CATEGORY_NAME
#define TIZ_LOG_CATEGORY_NAME "tiz.http_source.cfgport.dirble"
#endif

/*
 * dirblecfgport class
 */

static void *
dirble_cfgport_ctor (void * ap_obj, va_list * app)
{
  dirble_cfgport_t * p_obj
    = super_ctor (typeOf (ap_obj, "dirblecfgport"), ap_obj, app);

  assert (p_obj);

  tiz_check_omx_ret_null (
    tiz_port_register_index (p_obj, OMX_TizoniaIndexParamAudioDirbleSession));
  tiz_check_omx_ret_null (
    tiz_port_register_index (p_obj, OMX_TizoniaIndexParamAudioDirblePlaylist));

  /* Initialize the OMX_TIZONIA_AUDIO_PARAM_DIRBLESESSIONTYPE structure */
  TIZ_INIT_OMX_STRUCT (p_obj->session_);
  snprintf ((char *) p_obj->session_.cApiKey, sizeof (p_obj->session_.cApiKey),
            "xyzxyzxyzxyzxyz");

  /* Initialize the OMX_TIZONIA_AUDIO_PARAM_DIRBLEPLAYLISTTYPE structure */
  TIZ_INIT_OMX_STRUCT (p_obj->playlist_);
  snprintf ((char *) p_obj->playlist_.cPlaylistName,
            sizeof (p_obj->playlist_.cPlaylistName), "playlist");
  p_obj->playlist_.ePlaylistType = OMX_AUDIO_DirblePlaylistTypeUnknown;
  p_obj->playlist_.bShuffle = OMX_FALSE;

  return p_obj;
}

static void *
dirble_cfgport_dtor (void * ap_obj)
{
  return super_dtor (typeOf (ap_obj, "dirblecfgport"), ap_obj);
}

/*
 * from tiz_api
 */

static OMX_ERRORTYPE
dirble_cfgport_GetParameter (const void * ap_obj, OMX_HANDLETYPE ap_hdl,
                             OMX_INDEXTYPE a_index, OMX_PTR ap_struct)
{
  const dirble_cfgport_t * p_obj = ap_obj;
  OMX_ERRORTYPE rc = OMX_ErrorNone;

  assert (p_obj);

  TIZ_TRACE (ap_hdl, "PORT [%d] GetParameter [%s]...", tiz_port_index (ap_obj),
             tiz_idx_to_str (a_index));

  if (OMX_TizoniaIndexParamAudioDirbleSession == a_index)
    {
      memcpy (ap_struct, &(p_obj->session_),
              sizeof (OMX_TIZONIA_AUDIO_PARAM_DIRBLESESSIONTYPE));
    }
  else if (OMX_TizoniaIndexParamAudioDirblePlaylist == a_index)
    {
      memcpy (ap_struct, &(p_obj->playlist_),
              sizeof (OMX_TIZONIA_AUDIO_PARAM_DIRBLEPLAYLISTTYPE));
    }
  else
    {
      /* Delegate to the base port */
      rc = super_GetParameter (typeOf (ap_obj, "dirblecfgport"), ap_obj, ap_hdl,
                               a_index, ap_struct);
    }

  return rc;
}

static OMX_ERRORTYPE
dirble_cfgport_SetParameter (const void * ap_obj, OMX_HANDLETYPE ap_hdl,
                             OMX_INDEXTYPE a_index, OMX_PTR ap_struct)
{
  dirble_cfgport_t * p_obj = (dirble_cfgport_t *) ap_obj;
  OMX_ERRORTYPE rc = OMX_ErrorNone;

  assert (p_obj);

  TIZ_TRACE (ap_hdl, "PORT [%d] GetParameter [%s]...", tiz_port_index (ap_obj),
             tiz_idx_to_str (a_index));

  if (OMX_TizoniaIndexParamAudioDirbleSession == a_index)
    {
      memcpy (&(p_obj->session_), ap_struct,
              sizeof (OMX_TIZONIA_AUDIO_PARAM_DIRBLESESSIONTYPE));
      p_obj->session_.cApiKey[OMX_MAX_STRINGNAME_SIZE - 1] = '\000';
      TIZ_TRACE (ap_hdl, "Dirble Api Key [%s]...", p_obj->session_.cApiKey);
    }
  else if (OMX_TizoniaIndexParamAudioDirblePlaylist == a_index)
    {
      memcpy (&(p_obj->playlist_), ap_struct,
              sizeof (OMX_TIZONIA_AUDIO_PARAM_DIRBLEPLAYLISTTYPE));
      p_obj->playlist_.cPlaylistName[OMX_MAX_STRINGNAME_SIZE - 1] = '\000';
      TIZ_TRACE (ap_hdl, "Dirble playlist [%s]...",
                 p_obj->playlist_.cPlaylistName);
    }
  else
    {
      /* Delegate to the base port */
      rc = super_SetParameter (typeOf (ap_obj, "dirblecfgport"), ap_obj, ap_hdl,
                               a_index, ap_struct);
    }

  return rc;
}

/*
 * dirble_cfgport_class
 */

static void *
dirble_cfgport_class_ctor (void * ap_obj, va_list * app)
{
  /* NOTE: Class methods might be added in the future. None for now. */
  return super_ctor (typeOf (ap_obj, "dirblecfgport_class"), ap_obj, app);
}

/*
 * initialization
 */

void *
dirble_cfgport_class_init (void * ap_tos, void * ap_hdl)
{
  void * tizconfigport = tiz_get_type (ap_hdl, "tizconfigport");
  void * dirblecfgport_class
    = factory_new (classOf (tizconfigport), "dirblecfgport_class",
                   classOf (tizconfigport), sizeof (dirble_cfgport_class_t),
                   ap_tos, ap_hdl, ctor, dirble_cfgport_class_ctor, 0);
  return dirblecfgport_class;
}

void *
dirble_cfgport_init (void * ap_tos, void * ap_hdl)
{
  void * tizconfigport = tiz_get_type (ap_hdl, "tizconfigport");
  void * dirblecfgport_class = tiz_get_type (ap_hdl, "dirblecfgport_class");
  TIZ_LOG_CLASS (dirblecfgport_class);
  void * dirblecfgport = factory_new
    /* TIZ_CLASS_COMMENT: class type, class name, parent, size */
    (dirblecfgport_class, "dirblecfgport", tizconfigport,
     sizeof (dirble_cfgport_t),
     /* TIZ_CLASS_COMMENT: class constructor */
     ap_tos, ap_hdl,
     /* TIZ_CLASS_COMMENT: class constructor */
     ctor, dirble_cfgport_ctor,
     /* TIZ_CLASS_COMMENT: class destructor */
     dtor, dirble_cfgport_dtor,
     /* TIZ_CLASS_COMMENT: */
     tiz_api_GetParameter, dirble_cfgport_GetParameter,
     /* TIZ_CLASS_COMMENT: */
     tiz_api_SetParameter, dirble_cfgport_SetParameter,
     /* TIZ_CLASS_COMMENT: stop value*/
     0);

  return dirblecfgport;
}
