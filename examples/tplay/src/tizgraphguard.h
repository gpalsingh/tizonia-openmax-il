/* -*-Mode: c++; -*- */
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
 * @file   tizgraphguard.h
 * @author Juan A. Rubio <juan.rubio@aratelia.com>
 *
 * @brief  Graph fsm guard conditions
 *
 */

#ifndef TIZGRAPHGUARD_H
#define TIZGRAPHGUARD_H

#include <tizosal.h>

#ifdef TIZ_LOG_CATEGORY_NAME
#undef TIZ_LOG_CATEGORY_NAME
#define TIZ_LOG_CATEGORY_NAME "tiz.play.graph.guard"
#endif

#define G_GUARD_LOG(bool_result)                                              \
  do                                                                          \
  {                                                                           \
    TIZ_LOG (TIZ_PRIORITY_TRACE, "GUARD [%s] -> [%s]", typeid(*this).name (), \
             bool_result ? "YES" : "NO");                                     \
  } while (0)

namespace tiz
{
  namespace graph
  {

    // guard conditions
    struct is_port_disabling_complete
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState& source,
                      TargetState& target)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = (*(fsm.pp_ops_))
                   ->is_port_disabling_complete (evt.handle_, evt.port_);
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct is_port_enabling_complete
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState& source,
                      TargetState& target)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = (*(fsm.pp_ops_))
                   ->is_port_enabling_complete (evt.handle_, evt.port_);
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct is_disabled_evt_required
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState& source,
                      TargetState& target)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = (*(fsm.pp_ops_))->is_disabled_evt_required ();
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct is_port_settings_evt_required
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState& source,
                      TargetState& target)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = (*(fsm.pp_ops_))->is_port_settings_evt_required ();
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct last_op_succeeded
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState& source,
                      TargetState& target)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = (*(fsm.pp_ops_))->last_op_succeeded ();
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct is_trans_complete
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState& source,
                      TargetState& target)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          if ((*(fsm.pp_ops_))->is_trans_complete (evt.handle_, evt.state_))
          {
            TIZ_LOG (TIZ_PRIORITY_NOTICE,
                     "evt.state_ [%s] target state [%s]...",
                     tiz_state_to_str (evt.state_),
                     tiz_state_to_str (source.target_omx_state ()));
            assert (evt.state_ == source.target_omx_state ());
            rc = true;
          }
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct is_last_eos
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState&, TargetState&)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = (*(fsm.pp_ops_))->is_last_component (evt.handle_);
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct is_fatal_error
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState&, TargetState&)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = !(*(fsm.pp_ops_))->last_op_succeeded ();
        }
        // TODO: decide what else is a fatal error
        G_GUARD_LOG (rc);
        return rc;
      }
    };

    struct is_end_of_play
    {
      template < class EVT, class FSM, class SourceState, class TargetState >
      bool operator()(EVT const& evt, FSM& fsm, SourceState&, TargetState&)
      {
        bool rc = false;
        if (fsm.pp_ops_ && *(fsm.pp_ops_))
        {
          rc = (*(fsm.pp_ops_))->is_end_of_play ();
        }
        G_GUARD_LOG (rc);
        return rc;
      }
    };

  }  // namespace graph
}  // namespace tiz

#endif  // TIZGRAPHGUARD_H