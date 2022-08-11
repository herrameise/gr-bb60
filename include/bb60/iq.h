/* -*- c++ -*- */
/*
 * Copyright 2022 Signal Hound.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BB60_IQ_H
#define INCLUDED_BB60_IQ_H

#include <gnuradio/sync_block.h>
#include <bb60/api.h>

namespace gr {
namespace bb60 {

/*!
 * \brief This block acquires I/Q data from the Signal Hound BB60 spectrum analyzer.
 * \ingroup bb60
 *
 */
class BB60_API iq : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<iq> sptr;

    static sptr make(double center = 1e9,
                     double reflevel = -20,
                     int decimation = 1,
                     double bandwidth = 27e6,                     
                     bool purge = false);

    virtual void set_center(double center) = 0;
    virtual void set_reflevel(double reflevel) = 0;
    virtual void set_decimation(int decimation) = 0;
    virtual void set_bandwidth(double bandwidth) = 0;
    virtual void set_purge(bool purge) = 0;
};

} // namespace bb60
} // namespace gr

#endif /* INCLUDED_BB60_IQ_H */
