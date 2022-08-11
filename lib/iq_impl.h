/* -*- c++ -*- */
/*
 * Copyright 2022 Signal Hound.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_BB60_IQ_IMPL_H
#define INCLUDED_BB60_IQ_IMPL_H

#include <bb60/iq.h>
#include <bb60/bb_api.h>

namespace gr {
namespace bb60 {

class iq_impl : public iq
{
private:
      int _handle;

      double _center;
      double _reflevel;
      int _decimation;
      double _bandwidth;
      bool _purge;

      gr::thread::mutex _mutex;
      bool _param_changed;

      std::complex<float> *_buffer;
      int _len;

public:
    iq_impl(double center, double reflevel, int decimation, double bandwidth, bool purge);
    ~iq_impl();

    void set_center(double center);
    void set_reflevel(double reflevel);
    void set_decimation(int decimation);
    void set_bandwidth(double bandwidth);
    void set_purge(bool purge);

    void configure();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace bb60
} // namespace gr

#endif /* INCLUDED_BB60_IQ_IMPL_H */
