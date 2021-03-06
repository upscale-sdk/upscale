/*--------------------------------------------------------------------
  (C) Copyright 2015-2015 Barcelona Supercomputing Center
                          Centro Nacional de Supercomputacion
  
  This file is part of Mercurium C/C++ source-to-source compiler.
  
  See AUTHORS file in the top level directory for information
  regarding developers and contributors.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  
  Mercurium C/C++ source-to-source compiler is distributed in the hope
  that it will be useful, but WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the GNU Lesser General Public License for more
  details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with Mercurium C/C++ source-to-source compiler; if
  not, write to the Free Software Foundation, Inc., 675 Mass Ave,
  Cambridge, MA 02139, USA.
--------------------------------------------------------------------*/


#include "tl-nanos6-lower.hpp"
#include "tl-source.hpp"
#include "cxx-cexpr.h"

namespace TL { namespace Nanos6 {

    void Lower::visit(const Nodecl::OpenMP::TaskwaitShallow& node)
    {
        TL::Symbol nanos_taskwait_sym =
            TL::Scope::get_global_scope().get_symbol_from_name("nanos_taskwait");
        ERROR_CONDITION(!nanos_taskwait_sym.is_valid()
                || !nanos_taskwait_sym.is_function(),
                "Invalid symbol", 0);

        const char* locus = locus_to_str(node.get_locus());

        Nodecl::NodeclBase taskwait_tree =
            Nodecl::ExpressionStatement::make(
                    Nodecl::FunctionCall::make(
                        nanos_taskwait_sym.make_nodecl(/* set_ref_type */ true, node.get_locus()),
                        /* args */ Nodecl::List::make(
                            const_value_to_nodecl(
                                const_value_make_string_null_ended(
                                    locus,
                                    strlen(locus)))),
                        /* alternate-name */ Nodecl::NodeclBase::null(),
                        /* function-form */ Nodecl::NodeclBase::null(),
                        TL::Type::get_void_type(),
                        node.get_locus()));

        node.replace(taskwait_tree);
    }

} }
