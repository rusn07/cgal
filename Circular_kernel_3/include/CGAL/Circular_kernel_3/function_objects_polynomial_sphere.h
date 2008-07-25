// Copyright (c) 2008  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
// Author(s) : Monique Teillaud, Sylvain Pion, Pedro Machado

// Partially supported by the IST Programme of the EU as a 
// STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_SPHERICAL_KERNEL_FUNCTION_OBJECTS_POLYNOMIAL_SPHERE_H
#define CGAL_SPHERICAL_KERNEL_FUNCTION_OBJECTS_POLYNOMIAL_SPHERE_H

#include <CGAL/kernel_basic.h>

#include <CGAL/Circular_kernel_3/internal_functions_on_intersection_3.h>
#include <CGAL/Circular_kernel_3/internal_functions_on_circular_arc_point_3.h>
#include <CGAL/Circular_kernel_3/internal_functions_on_sphere_3.h>
#include <CGAL/Circular_kernel_3/internal_functions_on_line_3.h>
#include <CGAL/Circular_kernel_3/internal_functions_on_plane_3.h>
#include <CGAL/Circular_kernel_3/internal_functions_on_circle_3.h>
#include <CGAL/Circular_kernel_3/internal_functions_on_line_arc_3.h>
#include <CGAL/Circular_kernel_3/internal_functions_on_circular_arc_3.h>
#include <CGAL/Circular_kernel_3/internal_function_has_on_spherical_kernel.h>
#include <CGAL/Circular_kernel_3/internal_function_compare_spherical_kernel.h>
#include <CGAL/Object.h>


namespace CGAL {
	
namespace SphericalFunctors {

#define CGAL_SPHERICAL_KERNEL_MACRO_FUNCTOR_COMPARE_(V)\
template < class SK > \
  class Compare_ ##V## _3: public SK::Linear_kernel::Compare_ ##V## _3{\
    typedef typename SK::Circular_arc_point_3 Circular_arc_point_3;\
    typedef typename SK::Point_3 Point_3;\
  public:\
    typedef  typename SK::Linear_kernel::Compare_ ##V## _3::result_type result_type;\
    using SK::Linear_kernel::Compare_ ##V## _3::operator();\
    result_type\
    operator() (const Circular_arc_point_3 &p0,\
                const Circular_arc_point_3 &p1) const\
    { return compare_ ##V <SK>(p0, p1); }\
    result_type\
    operator() (const Circular_arc_point_3 &p0,\
                const Point_3 &p1) const\
    { return compare_ ##V <SK>(p0, p1); }\
    result_type\
    operator() (const Point_3 &p0,\
                const Circular_arc_point_3 &p1) const\
    { return compare_ ##V <SK>(p0, p1); }\
  };\
  
  CGAL_SPHERICAL_KERNEL_MACRO_FUNCTOR_COMPARE_(x)
  CGAL_SPHERICAL_KERNEL_MACRO_FUNCTOR_COMPARE_(y)
  CGAL_SPHERICAL_KERNEL_MACRO_FUNCTOR_COMPARE_(z)
  CGAL_SPHERICAL_KERNEL_MACRO_FUNCTOR_COMPARE_(xy)
  CGAL_SPHERICAL_KERNEL_MACRO_FUNCTOR_COMPARE_(xyz)

  template <class SK>
  class Compute_circular_x_3: Has_qrt
  {
    typedef typename SK::Circular_arc_point_3   Circular_arc_point_3;
    typedef typename SK::Root_of_2                 Root_of_2;

  public:

    typedef  Root_of_2  result_type;
    typedef const result_type &        qualified_result_type;

    qualified_result_type operator() (const Circular_arc_point_3 & a) const
    { return (a.rep().x()); }
  };

  template <class SK>
  class Compute_circular_y_3: Has_qrt
  {
    typedef typename SK::Circular_arc_point_3   Circular_arc_point_3;
    typedef typename SK::Root_of_2                 Root_of_2;

  public:

    typedef  Root_of_2  result_type;
    typedef const result_type &        qualified_result_type;

    qualified_result_type operator() (const Circular_arc_point_3 & a) const
    { return (a.rep().y()); }
  };

  template <class SK>
  class Compute_circular_z_3: Has_qrt
  {
    typedef typename SK::Circular_arc_point_3   Circular_arc_point_3;
    typedef typename SK::Root_of_2                 Root_of_2;

  public:

    typedef  Root_of_2  result_type;
    typedef const result_type &        qualified_result_type;

    qualified_result_type operator() (const Circular_arc_point_3 & a) const
    { return (a.rep().z()); }
  };

  template < class SK >
  class Equal_3
 #ifndef CGAL_CFG_MATCHING_BUG_6
    : public SK::Linear_kernel::Equal_3
#endif
  {
    typedef typename SK::Linear_kernel LK;
    typedef typename LK::Equal_3 LK_Equal_3;

    typedef typename SK::Point_3 Point_3;
    typedef typename SK::Direction_3 Direction_3;
    typedef typename SK::Line_3 Line_3;

    typedef typename SK::Circular_arc_point_3     Circular_arc_point_3;
    typedef typename SK::Circle_3                 Circle_3;
    typedef typename SK::Line_arc_3               Line_arc_3;
    typedef typename SK::Circular_arc_3           Circular_arc_3;

  public:

		typedef typename SK::Linear_kernel::Equal_3::result_type result_type;    

#ifndef CGAL_CFG_MATCHING_BUG_6
    using SK::Linear_kernel::Equal_3::operator();
#else  
    typedef bool result_type;

    result_type
    operator() (const Point_3 &p0,
                const Point_3 &p1) const
    { return LK_Equal_3()(p0,p1); }

    result_type
    operator() (const Direction_3 &d0,
                const Direction_3 &d1) const
    { return LK_Equal_3()(d0,d1); }

    result_type
    operator() (const Line_3 &l0,
                const Line_3 &l1) const
    { return LK_Equal_3()(l0,l1); }

#endif

    // Our Circle_3 dont have orientation
    result_type
    operator() (const Circle_3 &c0,
                const Circle_3 &c1) const
    { return equal<SK>(c0, c1); }

    result_type
    operator() (const Circular_arc_point_3 &c0,
                const Circular_arc_point_3 &c1) const
    { return equal<SK>(c0, c1); }
    
    result_type
    operator() (const Circular_arc_point_3 &c0,
                const Point_3 &c1) const
    { return equal<SK>(c0, Circular_arc_point_3(c1)); }

    result_type
    operator() (const Point_3 &c0,
                const Circular_arc_point_3 &c1) const
    { return equal<SK>(Circular_arc_point_3(c0), c1); }    

    // Our Line_arc_3 dont have orientation
    result_type
    operator() (const Line_arc_3 &l0,
                const Line_arc_3 &l1) const
    { return equal<SK>(l0, l1); }

    // Our Circular_arc_3 dont have orientation (as parameter)
    result_type
    operator() (const Circular_arc_3 &c0,
                const Circular_arc_3 &c1) const
    { return equal<SK>(c0, c1); }
    
  };

  template < class SK >
  class Construct_circular_arc_point_3
  {
    typedef typename SK::Point_3                            Point_3;
    typedef typename SK::Plane_3                            Plane_3;
    typedef typename SK::Line_3                             Line_3;
    typedef typename SK::Circle_3                           Circle_3;
    typedef typename SK::Sphere_3                           Sphere_3;
    typedef typename SK::Circular_arc_point_3               Circular_arc_point_3;
    typedef typename SK::Kernel_base::Circular_arc_point_3  RCircular_arc_point_3;
    typedef typename SK::Root_of_2                          Root_of_2;
    typedef typename Circular_arc_point_3::Rep              Rep;
    typedef typename Circular_arc_point_3::Root_for_spheres_2_3  Root_for_spheres_2_3;

  public:
    typedef  Circular_arc_point_3 result_type;


    result_type
    operator()(void) 
    { return Rep(); }
    
    result_type
      operator()(const Root_of_2 & x,
		 const Root_of_2 & y,
		 const Root_of_2 & z
		 ) const
    { return Rep(x,y,z); }
    
    result_type
    operator()(const Root_for_spheres_2_3 & np) const
    { return Rep(np); }

    result_type
    operator()(const Point_3 & p) const
    { return Rep(p); }

    result_type
    operator()(const Sphere_3 & s1,
               const Sphere_3 & s2,
               const Sphere_3 & s3,
               const bool less_xyz = true) const
    { return Rep(s1,s2,s3,less_xyz); }

    result_type
    operator()(const Plane_3 & p,
               const Sphere_3 & s1,
               const Sphere_3 & s2,
               const bool less_xyz = true) const
    { return Rep(p,s1,s2,less_xyz); }

    result_type
    operator()(const Sphere_3 & s1,
               const Plane_3 & p,
               const Sphere_3 & s2,
               const bool less_xyz = true) const
    { return Rep(p,s1,s2,less_xyz); }

    result_type
    operator()(const Sphere_3 & s1,
               const Sphere_3 & s2,
               const Plane_3 & p,
               const bool less_xyz = true) const
    { return Rep(p,s1,s2,less_xyz); }

    result_type
    operator()(const Plane_3 & p1,
               const Plane_3 & p2,
               const Sphere_3 & s,
               const bool less_xyz = true) const
    { return Rep(p1,p2,s,less_xyz); }

    result_type
    operator()(const Plane_3 & p1,
               const Sphere_3 & s,
               const Plane_3 & p2,
               const bool less_xyz = true) const
    { return Rep(p1,p2,s,less_xyz); }

    result_type
    operator()(const Sphere_3 & s,
               const Plane_3 & p1,
               const Plane_3 & p2,
               const bool less_xyz = true) const
    { return Rep(p1,p2,s,less_xyz); }

    result_type
    operator()(const Line_3 & l,
               const Sphere_3 & s,
               const bool less_xyz = true) const
    { return Rep(l,s,less_xyz); }

    result_type
    operator()(const Sphere_3 & s,
               const Line_3 & l,
               const bool less_xyz = true) const
    { return Rep(l,s,less_xyz); }

    result_type
    operator()(const Circle_3 & c,
               const Sphere_3 & s,
               const bool less_xyz = true) const
    { return Rep(c,s,less_xyz); }

    result_type
    operator()(const Sphere_3 & s,
               const Circle_3 & c,
               const bool less_xyz = true) const
    { return Rep(c,s,less_xyz); }

    result_type
    operator()(const Circle_3 & c,
               const Plane_3 & p,
               const bool less_xyz = true) const
    { return Rep(c,p,less_xyz); }

    result_type
    operator()(const Plane_3 & p,
               const Circle_3 & c,
               const bool less_xyz = true) const
    { return Rep(c,p,less_xyz); }

  };

  template < class SK >
  class Construct_sphere_3 : public  SK::Linear_kernel::Construct_sphere_3
  {
  public:
    
		typedef typename SK::Linear_kernel::Construct_sphere_3::result_type result_type; 

    using SK::Linear_kernel::Construct_sphere_3::operator();

    result_type
    operator() ( const typename SK::Polynomial_for_spheres_2_3 &eq )
    { return construct_sphere_3<SK>(eq); }
  };

  template < class SK >
  class Construct_plane_3 : public  SK::Linear_kernel::Construct_plane_3
  {
  public:
    
		typedef typename SK::Linear_kernel::Construct_plane_3::result_type result_type;

    using SK::Linear_kernel::Construct_plane_3::operator();

    result_type
    operator() ( const typename SK::Polynomial_1_3 &eq )
    { return construct_plane_3<SK>(eq); }
  };

  template < class SK >
  class Construct_line_3 : public  SK::Linear_kernel::Construct_line_3
  {
  public:
    
		typedef typename SK::Linear_kernel::Construct_line_3::result_type result_type;

    using SK::Linear_kernel::Construct_line_3::operator();

    result_type
    operator() ( const typename SK::Polynomials_for_line_3 &eq )
    { return construct_line_3<SK>(eq); }
  };

  template < class SK >
  class Construct_circle_3 : public  SK::Linear_kernel::Construct_circle_3
  {
  public:

    typedef typename SK::FT FT;
    typedef typename SK::Point_3 Point_3;
    typedef typename SK::Plane_3 Plane_3;
    typedef typename SK::Sphere_3 Sphere_3;
    typedef typename SK::Circle_3 Circle_3;
    typedef typename SK::Vector_3    Vector_3;
    typedef typename SK::Direction_3 Direction_3;
    typedef typename SK::Kernel_base::Circle_3  RCircle_3;
    typedef typename Circle_3::Rep              Rep;

		typedef typename SK::Linear_kernel::Construct_circle_3::result_type result_type;

    using SK::Linear_kernel::Construct_circle_3::operator();

    result_type
    operator() ( const typename SK::Polynomials_for_circle_3 &eq )
    { return Rep(construct_circle_3<SK>(eq)); }

  };

  template <class SK>
  class Construct_supporting_plane_3 : public  SK::Linear_kernel::Construct_supporting_plane_3
  {
    typedef typename SK::Plane_3        Plane_3;
    typedef typename SK::Circle_3       Circle_3;
    typedef typename SK::Circular_arc_3 Circular_arc_3;

  public:

		typedef typename SK::Linear_kernel::Construct_supporting_plane_3::result_type result_type;
    
    using SK::Linear_kernel::Construct_supporting_plane_3::operator();

    result_type operator() (const Circular_arc_3 & c) const
    { return c.rep().supporting_plane(); }
  };
  
  template <class SK>
  class Construct_supporting_sphere_3: Has_qrt
  {
    typedef typename SK::Sphere_3 Sphere_3;
    typedef typename SK::Circle_3 Circle_3;
  public:

    typedef Sphere_3        result_type;
    typedef const result_type& qualified_result_type;
    
    qualified_result_type operator() (const Circle_3 & c) const
    { return c.rep().supporting_sphere(); }

  };  

  template <class SK>
  class Construct_diametral_sphere_3 : public  SK::Linear_kernel::Construct_diametral_sphere_3
  {
    typedef typename SK::Sphere_3       Sphere_3;
    typedef typename SK::Circle_3       Circle_3;
    typedef typename SK::Circular_arc_3 Circular_arc_3;

  public:

		typedef typename SK::Linear_kernel::Construct_diametral_sphere_3::result_type result_type;
    
    using SK::Linear_kernel::Construct_diametral_sphere_3::operator();

    result_type operator() (const Circular_arc_3 & c) const
    { return c.rep().diametral_sphere(); }

  };

  template < class SK >
  class Construct_line_arc_3
  {

    typedef typename SK::Line_3                    Line_3;
    typedef typename SK::Point_3                   Point_3;
    typedef typename SK::Segment_3                 Segment_3;
    typedef typename SK::Sphere_3                  Sphere_3;
    typedef typename SK::Plane_3                   Plane_3;
    typedef typename SK::Circular_arc_point_3      Circular_arc_point_3;
    typedef typename SK::Line_arc_3                Line_arc_3;
    typedef typename SK::Kernel_base::Line_arc_3   RLine_arc_3;
    typedef typename Line_arc_3::Rep               Rep;

  public:
    typedef Line_arc_3   result_type;
                                // 3 operands, maybe we should remove this
    
    result_type
    operator()(void) const
    { return Rep(); }

    result_type
    operator()(const Line_3 &l,
	       const Circular_arc_point_3 &s,
	       const Circular_arc_point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Line_3 &l,
	       const Point_3 &s,
	       const Circular_arc_point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Line_3 &l,
	       const Circular_arc_point_3 &s,
	       const Point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Line_3 &l,
	       const Point_3 &s,
	       const Point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Segment_3 &s) const
    { return Rep(s); }

    result_type
    operator()(const Line_3 &l,
               const Sphere_3 &s,
               bool less_xyz_first = true) const
    { return Rep(l,s,less_xyz_first); }

    result_type
    operator()(const Sphere_3 &s,
               const Line_3 &l,
               bool less_xyz_first = true) const
    { return Rep(l,s,less_xyz_first); }

    result_type
    operator()(const Line_3 &l, 
               const Sphere_3 &s1, bool less_xyz_s1,
               const Sphere_3 &s2, bool less_xyz_s2) const
    { return Rep(l,s1,less_xyz_s1,
                   s2,less_xyz_s2); }

    result_type
    operator()(const Sphere_3 &s1, bool less_xyz_s1,
               const Sphere_3 &s2, bool less_xyz_s2,
               const Line_3 &l) const
    { return Rep(l,s1,less_xyz_s1,
                   s2,less_xyz_s2); }

    result_type
    operator()(const Line_3 &l,
	       const Plane_3 &p1,
	       const Plane_3 &p2) const
    { return Rep(l,p1,p2); }

    result_type
    operator()(const Plane_3 &p1,
	       const Plane_3 &p2,
               const Line_3 &l) const
    { return Rep(l,p1,p2); }

  };

  template < class SK >
  class Construct_circular_arc_3
  {

    typedef typename SK::Line_3                        Line_3;
    typedef typename SK::Point_3                       Point_3;
    typedef typename SK::Segment_3                     Segment_3;
    typedef typename SK::Sphere_3                      Sphere_3;
    typedef typename SK::Plane_3                       Plane_3;
    typedef typename SK::Line_arc_3                    Line_arc_3;
    
    typedef typename SK::Circular_arc_point_3          Circular_arc_point_3;
    typedef typename SK::Circle_3                      Circle_3;
    typedef typename SK::Circular_arc_3                Circular_arc_3;
    typedef typename SK::Kernel_base::Circular_arc_3   RCircular_arc_3;
    typedef typename Circular_arc_3::Rep               Rep;
  public:
    typedef Circular_arc_3   result_type;
                                // 3 operands, maybe we should remove this

    result_type
    operator()(void) const
    { return Rep(); }

    result_type
    operator()(const Circle_3 &c) const
    { return Rep(c); }

    result_type
    operator()(const Circle_3 &l,
	       const Circular_arc_point_3 &s,
	       const Circular_arc_point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Circle_3 &l,
	       const Point_3 &s,
	       const Circular_arc_point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Circle_3 &l,
	       const Circular_arc_point_3 &s,
	       const Point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Circle_3 &l,
	       const Point_3 &s,
	       const Point_3 &t) const
    { return Rep(l,s,t); }

    result_type
    operator()(const Circle_3 &c, 
               const Sphere_3 &s1, bool less_xyz_s1,
               const Sphere_3 &s2, bool less_xyz_s2) const
    { return Rep(c,s1,less_xyz_s1,s2,less_xyz_s2); }

    result_type
    operator()(const Sphere_3 &s1, bool less_xyz_s1,
               const Sphere_3 &s2, bool less_xyz_s2,
               const Circle_3 &c) const
    { return Rep(c,s1,less_xyz_s1,s2,less_xyz_s2); }

    result_type
    operator()(const Circle_3 &c, 
               const Plane_3 &p1, bool less_xyz_p1,
               const Plane_3 &p2, bool less_xyz_p2) const
    { return Rep(c,p1,less_xyz_p1,p2,less_xyz_p2); }

    result_type
    operator()(const Plane_3 &p1, bool less_xyz_p1,
               const Plane_3 &p2, bool less_xyz_p2,
               const Circle_3 &c) const
    { return Rep(c,p1,less_xyz_p1,p2,less_xyz_p2); }
   
  };

  template <class SK>
  class Construct_circular_min_vertex_3 : Has_qrt
  {
    typedef typename SK::Line_arc_3                Line_arc_3;
    typedef typename SK::Circular_arc_point_3      Circular_arc_point_3;

  public:

    typedef Circular_arc_point_3 result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Line_arc_3 & a) const
    { return (a.rep().lower_xyz_extremity()); }

  };

  template <class SK>
  class Construct_circular_max_vertex_3 : Has_qrt
  {
    typedef typename SK::Line_arc_3                Line_arc_3;
    typedef typename SK::Circular_arc_point_3      Circular_arc_point_3;

  public:

    typedef Circular_arc_point_3 result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Line_arc_3 & a) const
    { return (a.rep().higher_xyz_extremity()); }

  };

  template <class SK>
  class Construct_circular_source_vertex_3 : Has_qrt
  {
    typedef typename SK::Line_arc_3                Line_arc_3;
    typedef typename SK::Circular_arc_3            Circular_arc_3;
    typedef typename SK::Circular_arc_point_3      Circular_arc_point_3;

  public:

    typedef Circular_arc_point_3 result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Line_arc_3 & a) const
    { return (a.rep().source()); }

    qualified_result_type operator() (const Circular_arc_3 & a) const
    { return (a.rep().source()); }

  };

  template <class SK>
  class Construct_circular_target_vertex_3 : Has_qrt
  {
    typedef typename SK::Line_arc_3                Line_arc_3;
    typedef typename SK::Circular_arc_point_3      Circular_arc_point_3;
    typedef typename SK::Circular_arc_3            Circular_arc_3;

  public:

    typedef Circular_arc_point_3 result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Line_arc_3 & a) const
    { return (a.rep().target()); }

    qualified_result_type operator() (const Circular_arc_3 & a) const
    { return (a.rep().target()); }

  };

  template <class SK>
  class Construct_supporting_line_3 : Has_qrt
  {
    typedef typename SK::Line_arc_3                Line_arc_3;
    typedef typename SK::Line_3                    Line_3;

  public:

    typedef Line_3 result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Line_arc_3 & a) const
    { return (a.rep().supporting_line()); }

  };

  template <class SK>
  class Construct_supporting_circle_3 : Has_qrt
  {
    typedef typename SK::Circular_arc_3            Circular_arc_3;
    typedef typename SK::Circle_3                  Circle_3;

  public:

    typedef Circle_3 result_type;
    typedef const result_type &  qualified_result_type;

    qualified_result_type operator() (const Circular_arc_3 & a) const
    { return (a.rep().supporting_circle()); }

  };

  template < class SK >
  class Has_on_3 
    : public SK::Linear_kernel::Has_on_3
  {
    typedef typename SK::Point_3                 Point_3;
    typedef typename SK::Sphere_3                Sphere_3;
    typedef typename SK::Plane_3                 Plane_3;
    typedef typename SK::Line_3                  Line_3;
    typedef typename SK::Line_arc_3              Line_arc_3;
    typedef typename SK::Circular_arc_point_3    Circular_arc_point_3;
    typedef typename SK::Circular_arc_3          Circular_arc_3;
    typedef typename SK::Circle_3                Circle_3;
    

  public:
		typedef typename SK::Linear_kernel::Has_on_3::result_type result_type;
    
    using SK::Linear_kernel::Has_on_3::operator();

    result_type
    operator()(const Sphere_3 &a, const Circular_arc_point_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Circular_arc_point_3 &p, const Sphere_3 &a) const
    { return false; }

    result_type
    operator()(const Plane_3 &a, const Circular_arc_point_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Circular_arc_point_3 &p, const Plane_3 &a) const
    { return false; }

    result_type
    operator()(const Line_3 &a, const Circular_arc_point_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Circular_arc_point_3 &p, const Line_3 &a) const
    { return false; }

    result_type
    operator()(const Circle_3 &a, const Circular_arc_point_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Line_arc_3 &a, const Circular_arc_point_3 &p,
               const bool already_know_point_on_line = false) const
    { return has_on<SK>(a, p, already_know_point_on_line); }

    result_type
    operator()(const Circular_arc_point_3 &a, const Line_arc_3 &p) const
    { return false; }

    result_type
    operator()(const Line_arc_3 &a, const Point_3 &p,
               const bool already_know_point_on_line = false) const
    { return has_on<SK>(a, p, already_know_point_on_line); }

    result_type
    operator()(const Plane_3 &p, const Line_arc_3 &a) const
    { return has_on<SK>(p, a); }

    result_type
    operator()(const Line_arc_3 &p, const Plane_3 &a) const
    { return false; }

    result_type
    operator()(const Sphere_3 &a, const Line_arc_3 &p) const
    { return false; }

    result_type
    operator()(const Line_arc_3 &a, const Sphere_3 &p) const
    { return false; }

    result_type
    operator()(const Circle_3 &a, const Line_arc_3 &p) const
    { return false; }

    result_type
    operator()(const Line_arc_3 &a, const Circle_3 &p) const
    { return false; }

    result_type
    operator()(const Line_3 &a, const Line_arc_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Line_arc_3 &a, const Line_3 &p) const
    { return false; }

    result_type
    operator()(const Circular_arc_3 &a, const Point_3 &p,
               const bool has_on_supporting_circle = false) const
    { return has_on<SK>(a, p, has_on_supporting_circle); }

    result_type
    operator()(const Point_3 &p, const Circular_arc_3 &a) const
    { return false; }

    result_type
    operator()(const Circular_arc_3 &a, const Circular_arc_point_3 &p,
               const bool has_on_supporting_circle = false) const
    { return has_on<SK>(a, p, has_on_supporting_circle); }

    result_type
    operator()(const Sphere_3 &a, const Circular_arc_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Plane_3 &a, const Circular_arc_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Circle_3 &a, const Circular_arc_3 &p) const
    { return has_on<SK>(a, p); }

    result_type
    operator()(const Circular_arc_3 &p, const Circle_3 &a) const
    { return has_on<SK>(p, a); }
    
  };

  template < class SK >
  class Do_intersect_3
    : public SK::Linear_kernel::Do_intersect_3
  {
  
    typedef typename SK::Sphere_3                 Sphere_3;
    typedef typename SK::Line_3                   Line_3;
    typedef typename SK::Line_arc_3               Line_arc_3;
    typedef typename SK::Circular_arc_3           Circular_arc_3;
    typedef typename SK::Plane_3                  Plane_3;
    typedef typename SK::Circle_3                 Circle_3;
  
  public:

	  typedef typename SK::Linear_kernel::Do_intersect_3::result_type result_type;
  
    using SK::Linear_kernel::Do_intersect_3::operator();

#define CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(A,B) \
  result_type \
  operator()(const A & c1, const B & c2) const \
  { std::vector< Object > res; \
    typename SK::Intersect_3()(c1,c2,std::back_inserter(res)); \
	  return res.size() != 0; }
	
#define CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_3(A,B,C) \
  result_type \
  operator()(const A & c1, const B & c2, const C & c3) const \
  { std::vector< Object > res; \
    typename SK::Intersect_3()(c1,c2,c3,std::back_inserter(res)); \
	  return res.size() != 0; }

	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Sphere_3, Line_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_3, Sphere_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_3(Sphere_3, Sphere_3, Sphere_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_3(Sphere_3, Sphere_3, Plane_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_3(Plane_3, Sphere_3, Sphere_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_3(Plane_3, Plane_3, Sphere_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_3(Sphere_3, Plane_3, Plane_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circle_3, Plane_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Plane_3, Circle_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circle_3, Sphere_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Sphere_3, Circle_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circle_3, Circle_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circle_3, Line_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_3, Circle_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_arc_3, Line_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_3, Line_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_arc_3, Line_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circle_3, Line_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_arc_3, Circle_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Sphere_3, Line_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_arc_3, Sphere_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Plane_3, Line_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_arc_3, Plane_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circular_arc_3, Circular_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_3, Circular_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circular_arc_3, Line_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circle_3, Circular_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circular_arc_3, Circle_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Sphere_3, Circular_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circular_arc_3, Sphere_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Plane_3, Circular_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circular_arc_3, Plane_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Circular_arc_3, Line_arc_3)
	CGAL_SPHERICAL_KERNEL_MACRO_DO_INTERSECTION_3_2(Line_arc_3, Circular_arc_3)

  };

  template < class SK >
  class Intersect_3
    : public SK::Linear_kernel::Intersect_3
  {
  
    typedef typename SK::Sphere_3                 Sphere_3;
    typedef typename SK::Line_3                   Line_3;
    typedef typename SK::Line_arc_3               Line_arc_3;
    typedef typename SK::Circular_arc_3           Circular_arc_3;
    typedef typename SK::Plane_3                  Plane_3;
    typedef typename SK::Circle_3                 Circle_3;
    
    public:

		typedef typename SK::Linear_kernel::Intersect_3::result_type result_type;
                                
    typedef typename SK::Object_3 Object_3;
    
    using SK::Linear_kernel::Intersect_3::operator();

    template < class OutputIterator >
    OutputIterator
    operator()(const Sphere_3 & s, const Line_3 & l, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,l,res); }
    
     template < class OutputIterator >
    OutputIterator
      operator()(const Line_3 & l,const Sphere_3 & s, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Sphere_3 & s1, const Sphere_3 & s2, 
	       const Sphere_3 & s3, OutputIterator res) const
    { return intersect_3<SK> (s1,s2,s3,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Sphere_3 & s1, const Sphere_3 & s2, 
	       const Plane_3 & p, OutputIterator res) const
    { return intersect_3<SK> (p,s1,s2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Plane_3 & p, const Sphere_3 & s1,  
	       const Sphere_3 & s2, OutputIterator res) const
    { return intersect_3<SK> (p,s1,s2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Plane_3 & p1, const Plane_3 & p2,  
	       const Sphere_3 & s, OutputIterator res) const
    { return intersect_3<SK> (p1,p2,s,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Sphere_3 & s, const Plane_3 & p1, 
	       const Plane_3 & p2, OutputIterator res) const
    { return intersect_3<SK> (p1,p2,s,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle_3 & c, const Plane_3 & p, 
	       OutputIterator res) const
    { return intersect_3<SK> (c,p,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Plane_3 & p, const Circle_3 & c, 
	       OutputIterator res) const
    { return intersect_3<SK> (c,p,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle_3 & c, const Sphere_3 & s, 
	       OutputIterator res) const
    { return intersect_3<SK> (c,s,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Sphere_3 & s, const Circle_3 & c, 
	       OutputIterator res) const
    { return intersect_3<SK> (c,s,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle_3 & c1, const Circle_3 & c2, 
	       OutputIterator res) const
    { return intersect_3<SK> (c1,c2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle_3 & c, const Line_3 & l, 
	       OutputIterator res) const
    { return intersect_3<SK> (c,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_3 & l, const Circle_3 & c,
	       OutputIterator res) const
    { return intersect_3<SK> (c,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_3 & l1, const Line_arc_3 & l2, 
	       OutputIterator res) const
    { return intersect_3<SK> (l1,l2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_3 & l, const Line_arc_3 & la) const
    { return intersect_3<SK> (l,la); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_3 & la, const Line_3 & l) const
    { return intersect_3<SK> (l,la); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle_3 & c, const Line_arc_3 & l, 
	       OutputIterator res) const
    { return intersect_3<SK> (c,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_3 & l, const Circle_3 & c,
	       OutputIterator res) const
    { return intersect_3<SK> (c,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Sphere_3 & s, const Line_arc_3 & l, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,l,res); }
    
    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_3 & l,const Sphere_3 & s, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Plane_3 & s, const Line_arc_3 & l, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_3 & l,const Plane_3 & s, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,l,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_3 & c1, const Circular_arc_3 & c2, 
	       OutputIterator res) const
    { return intersect_3<SK> (c1,c2,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_3 & l, const Circular_arc_3 & ca) const
    { return intersect_3<SK> (l,ca); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_3 & ca, const Line_3 & l) const
    { return intersect_3<SK> (l,ca); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circle_3 & c, const Circular_arc_3 & ca, 
	       OutputIterator res) const
    { return intersect_3<SK> (c,ca,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_3 & ca, const Circle_3 & c,
	       OutputIterator res) const
    { return intersect_3<SK> (c,ca,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Sphere_3 & s, const Circular_arc_3 & ca, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,ca,res); }
    
    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_3 & ca,const Sphere_3 & s, 
	       OutputIterator res) const
    { return intersect_3<SK> (s,ca,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Plane_3 & p, const Circular_arc_3 & ca, 
	       OutputIterator res) const
    { return intersect_3<SK> (p,ca,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_3 & ca, const Plane_3 & p, 
	       OutputIterator res) const
    { return intersect_3<SK> (p,ca,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Circular_arc_3 & ca, const Line_arc_3 & la, 
	       OutputIterator res) const
    { return intersect_3<SK> (ca,la,res); }

    template < class OutputIterator >
    OutputIterator
    operator()(const Line_arc_3 & la, const Circular_arc_3 & ca,
	       OutputIterator res) const
    { return intersect_3<SK> (ca,la,res); }
    
  };

// If 2 line_arc have the same supporting line
// if they intersect only at a point
// even in this case we consider that the 2 line_arc overlap
  template < class SK >
  class Do_overlap_3
  {
    typedef typename SK::Line_arc_3     Line_arc_3;
    typedef typename SK::Circular_arc_3 Circular_arc_3;

  public:
    typedef bool         result_type;

    result_type
    operator() (const Line_arc_3 &l1, const Line_arc_3 &l2,
                const bool known_equal_supporting_line = false) const
    { return do_overlap<SK>(l1, l2, known_equal_supporting_line); }

    result_type
    operator() (const Circular_arc_3 &c1, const Circular_arc_3 &c2,
                const bool known_equal_supporting_circle = false) const
    { return do_overlap<SK>(c1, c2, known_equal_supporting_circle); }

    result_type
    operator() (const Circular_arc_3 &c, const Line_arc_3 &l) const
    { return false; }

    result_type
    operator() (const Line_arc_3 &l, const Circular_arc_3 &c) const
    { return false; }

  };

  template < class SK >
  class Split_3
  {
    typedef typename SK::Circular_arc_point_3    Circular_arc_point_3;
    typedef typename SK::Line_arc_3              Line_arc_3;
    typedef typename SK::Circular_arc_3          Circular_arc_3;

  public:

    typedef void         result_type;

    result_type
    operator()(const Line_arc_3 &l, 
	       const Circular_arc_point_3 &p,
	       Line_arc_3 &ca1, Line_arc_3 &ca2) const
    { return split<SK>(l, p, ca1, ca2); }

    result_type
    operator()(const Circular_arc_3 &c, 
	       const Circular_arc_point_3 &p,
	       Circular_arc_3 &ca1, Circular_arc_3 &ca2) const
    { return split<SK>(c, p, ca1, ca2); }

  };

  template <class SK>
  class Construct_bbox_3
    : public SK::Linear_kernel::Construct_bbox_3
  {
    typedef typename SK::Circular_arc_point_3      Circular_arc_point_3;
    typedef typename SK::Circular_arc_3            Circular_arc_3;
    typedef typename SK::Circle_3                  Circle_3;
    typedef typename SK::Line_arc_3                Line_arc_3;

  public:

		typedef typename SK::Linear_kernel::Construct_bbox_3::result_type result_type;

    using SK::Linear_kernel::Construct_bbox_3::operator();

    result_type operator() (const Circular_arc_point_3 & c) const
    { return c.rep().bbox(); }

    result_type operator() (const Line_arc_3 & l) const
    { return l.rep().bbox(); }

    result_type operator() (const Circular_arc_3 & c) const
    { return c.rep().bbox(); }

  };

  template <class SK>
  class Compute_area_divided_by_pi_3
  {
    typedef typename SK::Circle_3                  Circle_3;
    typedef typename SK::FT                        FT;

  public:

    typedef const FT result_type;

    result_type operator() (const Circle_3 & c) const
    { return c.rep().area_divided_by_pi(); }

  };

  template <class SK>
  class Compute_squared_length_divided_by_pi_square_3
  {
    typedef typename SK::Circle_3                  Circle_3;
    typedef typename SK::FT                        FT;

  public:

    typedef const FT result_type;

    result_type operator() (const Circle_3 & c) const
    { return c.rep().squared_length_divided_by_pi_square(); }

  };

  template <class SK>
  class Compute_approximate_area_3
  {
    typedef typename SK::Circle_3                  Circle_3;
    typedef typename SK::FT                        FT;

  public:

    typedef double result_type;

    result_type operator() (const Circle_3 & c) const
    { return c.rep().approximate_area(); }

  };

  template <class SK>
  class Compute_approximate_squared_length_3
  {
    typedef typename SK::Circle_3                  Circle_3;
    typedef typename SK::Circular_arc_3            Circular_arc_3;
    typedef typename SK::FT                        FT;

  public:

    typedef double result_type;

    result_type operator() (const Circle_3 & c) const
    { return c.rep().approximate_squared_length(); }

    result_type operator() (const Circular_arc_3 & c) const
    { return c.rep().approximate_squared_length(); }

  };

  template <class SK>
  class Compute_approximate_angle_3
  {
    typedef typename SK::Circular_arc_3            Circular_arc_3;

  public:

    typedef double result_type;

    result_type operator() (const Circular_arc_3 & c) const
    { return c.rep().approximate_angle(); }

  };

  // Maybe this one should be on the Linear Kernel
  template <class SK> 
  class Construct_radical_plane_3
  {
    typedef typename SK::Plane_3            Plane_3;
    typedef typename SK::Sphere_3           Sphere_3;

  public:

    typedef Plane_3 result_type;

    result_type operator() (const Sphere_3 & s1, const Sphere_3 & s2) const
    { return radical_plane<SK>(s1, s2); }
  };

  template <class SK>
  class Bounded_side_3
    : public SK::Linear_kernel::Bounded_side_3
  {
    typedef typename SK::Sphere_3              Sphere_3;
    typedef typename SK::Circle_3              Circle_3;
    typedef typename SK::Circular_arc_point_3  Circular_arc_point_3;
    typedef typename SK::Point_3               Point_3;

  public:
    typedef typename SK::Linear_kernel::Bounded_side_3::result_type    result_type;

    using SK::Linear_kernel::Bounded_side_3::operator();

    result_type
    operator()( const Sphere_3& s, const Circular_arc_point_3& p) const
    { return bounded_side<SK>(s,p); }

    result_type
    operator()( const Circle_3& c, const Circular_arc_point_3& p) const
    { return bounded_side<SK>(c,p); }

    // We can maybe optimize it doing the operator() for point_3 too

  };

  template <class SK>
  class Has_on_bounded_side_3
    : public SK::Linear_kernel::Has_on_bounded_side_3
  {
    typedef typename SK::Sphere_3              Sphere_3;
    typedef typename SK::Circle_3              Circle_3;
    typedef typename SK::Circular_arc_point_3  Circular_arc_point_3;
    typedef typename SK::Point_3               Point_3;

  public:
    typedef typename SK::Linear_kernel::Has_on_bounded_side_3::result_type    result_type;

    using SK::Linear_kernel::Has_on_bounded_side_3::operator();

    result_type
    operator()( const Sphere_3& s, const Circular_arc_point_3& p) const
    { return SK().bounded_side_3_object()(s,p) == ON_BOUNDED_SIDE; }

    result_type
    operator()( const Circle_3& c, const Circular_arc_point_3& p) const
    { return SK().bounded_side_3_object()(c,p) == ON_BOUNDED_SIDE; }

    // We can maybe optimize it doing the operator() for point_3 too

  };

  template <class SK>
  class Has_on_unbounded_side_3
    : public SK::Linear_kernel::Has_on_unbounded_side_3
  {
    typedef typename SK::Sphere_3              Sphere_3;
    typedef typename SK::Circle_3              Circle_3;
    typedef typename SK::Circular_arc_point_3  Circular_arc_point_3;
    typedef typename SK::Point_3               Point_3;

  public:
    typedef typename SK::Linear_kernel::Has_on_unbounded_side_3::result_type    result_type;

    using SK::Linear_kernel::Has_on_unbounded_side_3::operator();

    result_type
    operator()( const Sphere_3& s, const Circular_arc_point_3& p) const
    { return SK().bounded_side_3_object()(s,p) == ON_UNBOUNDED_SIDE; }

    result_type
    operator()( const Circle_3& c, const Circular_arc_point_3& p) const
    { return SK().bounded_side_3_object()(c,p) == ON_UNBOUNDED_SIDE; }

    // We can maybe optimize it doing the operator() for point_3 too

  };

} // namespace SphericalFunctors
} // namespace CGAL

#endif // CGAL_SPHERICAL_KERNEL_FUNCTION_OBJECTS_POLYNOMIAL_SPHERE_H
