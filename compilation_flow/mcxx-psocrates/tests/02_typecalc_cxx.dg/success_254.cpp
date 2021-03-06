/*--------------------------------------------------------------------
  (C) Copyright 2006-2012 Barcelona Supercomputing Center
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



/*
<testinfo>
test_generator=config/mercurium
</testinfo>
*/

template < typename T>
struct A
{

    template < typename S>
        struct B
        {
            void f(T,S);
        };
};

template <>
template <typename S1>
struct A<int>::B
{
    void f1(int, S1*);
};

template <>
template <typename S1>
void A<int>::B<S1>::f1(int, S1*) {}


template <>
struct A<float>
{
    template < typename S2>
        struct B1
        {
            void f2(int, S2**);
        };
};


template < typename S2>
void A<float>::B1<S2>::f2(int, S2**) {}

template<>
struct A<float>::B1<int>
{
    void h();
};

void A<float>::B1<int>::h() {}


template<>
template<>
struct A<int>::B<int>
{};
