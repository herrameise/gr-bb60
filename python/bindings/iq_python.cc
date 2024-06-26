/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(iq.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(7804c89b3d599947763a13d2cefa7175)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <bb60/iq.h>
// pydoc.h is automatically generated in the build directory
#include <iq_pydoc.h>

void bind_iq(py::module& m)
{

    using iq    = ::gr::bb60::iq;


    py::class_<iq, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<iq>>(m, "iq", D(iq))

        .def(py::init(&iq::make),
           py::arg("center") = 1.0E+9,
           py::arg("reflevel") = -20,
           py::arg("decimation") = 1,
           py::arg("bandwidth") = 2.7E+7,
           py::arg("purge") = false,
           D(iq,make)
        )
        




        
        .def("set_center",&iq::set_center,       
            py::arg("center"),
            D(iq,set_center)
        )


        
        .def("set_reflevel",&iq::set_reflevel,       
            py::arg("reflevel"),
            D(iq,set_reflevel)
        )


        
        .def("set_decimation",&iq::set_decimation,       
            py::arg("decimation"),
            D(iq,set_decimation)
        )


        
        .def("set_bandwidth",&iq::set_bandwidth,       
            py::arg("bandwidth"),
            D(iq,set_bandwidth)
        )


        
        .def("set_purge",&iq::set_purge,       
            py::arg("purge"),
            D(iq,set_purge)
        )

        ;




}








