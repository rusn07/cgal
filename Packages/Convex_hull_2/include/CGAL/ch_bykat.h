// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
// release       : 
// release_date  : 
//
// file          : include/CGAL/ch_bykat.h
// package       : Convex_hull_2
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// ======================================================================


#ifndef CGAL_CH_BYKAT_H
#define CGAL_CH_BYKAT_H

#include <CGAL/basic.h>
#include <iterator>

CGAL_BEGIN_NAMESPACE

// same as |convex_hull_2(first,last,result)|. {\sc traits}: 
// uses |Traits::Point_2|, |Traits::Less_signed_distance_to_line_2|,
// |Traits::Left_turn_2|, and |Traits::Less_xy_2|.
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_bykat(InputIterator first, InputIterator last, 
         OutputIterator  result,
         const Traits& ch_traits);

template <class InputIterator, class OutputIterator>
inline
OutputIterator
ch_bykat(InputIterator first, InputIterator last, OutputIterator  result)
{
    typedef std::iterator_traits<InputIterator>   ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return ch_bykat( first, last, result, Kernel());
}


template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_bykat_with_threshold(InputIterator first, InputIterator last, 
                             OutputIterator  result,
                             const Traits& ch_traits);

template <class InputIterator, class OutputIterator>
inline
OutputIterator
ch_bykat_with_threshold(InputIterator first, InputIterator last, 
                        OutputIterator  result)
{
    typedef std::iterator_traits<InputIterator>   ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return ch_bykat_with_threshold( first, last, result, Kernel());
}

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_bykat.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_BYKAT_H

