/* -*- c++ -*- */
/*
 * Copyright 2022 Signal Hound.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "iq_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace bb60 {

using output_type = gr_complex;
iq::sptr
iq::make(double center, double reflevel, int decimation, double bandwidth, bool purge)
{
    return gnuradio::make_block_sptr<iq_impl>(
        center, reflevel, decimation, bandwidth, purge);
}

void ERROR_CHECK(bbStatus status)
{
    if(status != bbNoError) {
        bool isWarning = status > bbNoError;
        std::cout << "** " << (isWarning ? "Warning: " : "Error: ") << bbGetErrorString(status) << " **" << "\n";
        if(!isWarning) abort();
    }
}

iq_impl::iq_impl(
    double center, double reflevel, int decimation, double bandwidth, bool purge)
    : gr::sync_block("iq",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(1, 1, sizeof(output_type))),
    _handle(-1),
    _center(center),
    _reflevel(reflevel),
    _decimation(decimation),
    _bandwidth(bandwidth),
    _purge(purge),
    _param_changed(true),
    _buffer(0),
    _len(0)
{
    std::cout << "\nAPI Version: " << bbGetAPIVersion() << "\n";

    // Open device
    ERROR_CHECK(bbOpenDevice(&_handle));

    uint32_t serial;
    ERROR_CHECK(bbGetSerialNumber(_handle, &serial));
    std::cout << "Serial Number: "<< serial << "\n";
}

iq_impl::~iq_impl() 
{
    bbAbort(_handle);
    bbCloseDevice(_handle);

    if(_buffer) delete [] _buffer;
}

void
iq_impl::set_center(double center) 
{
    gr::thread::scoped_lock lock(_mutex);
    _center = center;
    _param_changed = true;
}

void
iq_impl::set_reflevel(double reflevel) {
    gr::thread::scoped_lock lock(_mutex);
    _reflevel = reflevel;
    _param_changed = true;
}

void
iq_impl::set_decimation(int decimation) {
    gr::thread::scoped_lock lock(_mutex);
    _decimation = decimation;
    _param_changed = true;
}

void
iq_impl::set_bandwidth(double bandwidth) {
    gr::thread::scoped_lock lock(_mutex);
    _bandwidth = bandwidth;
    _param_changed = true;
}

void
iq_impl::set_purge(bool purge) {
    gr::thread::scoped_lock lock(_mutex);
    _purge = purge;
}

void
iq_impl::configure() {
    gr::thread::scoped_lock lock(_mutex);

    // Configure
    ERROR_CHECK(bbConfigureIQCenter(_handle, _center));
    ERROR_CHECK(bbConfigureRefLevel(_handle, _reflevel));
    ERROR_CHECK(bbConfigureIQ(_handle, _decimation, _bandwidth));
    ERROR_CHECK(bbConfigureIQDataType(_handle, bbDataType32fc));

    // Initiate for I/Q streaming
    ERROR_CHECK(bbInitiate(_handle, BB_STREAMING, BB_STREAM_IQ));

    // Get I/Q streaming info
    double sampleRate, actualBandwidth;
    ERROR_CHECK(bbQueryIQParameters(_handle, &sampleRate, &actualBandwidth));
    std::cout << "\nSample Rate: "<< sampleRate << "\n";
    std::cout << "Actual Bandwidth: "<< actualBandwidth << "\n";
}

int iq_impl::work(int noutput_items,
                  gr_vector_const_void_star& input_items,
                  gr_vector_void_star& output_items)
{
    auto out = static_cast<output_type*>(output_items[0]);

    // Initiate new configuration if necessary
    if(_param_changed) {
        configure();
        _param_changed = false;
    }

    // Allocate memory if necessary
    if(!_buffer || noutput_items != _len) {
        if(_buffer) delete [] _buffer;
        _buffer = new std::complex<float>[noutput_items];
        _len = noutput_items;
    }

    // Get I/Q
    ERROR_CHECK(bbGetIQUnpacked(_handle, (float *)_buffer, noutput_items, 0, 0, _purge ? BB_TRUE : BB_FALSE, 0, 0, 0, 0));

    // Move data to output array
    for(int i = 0; i < noutput_items; i++) {
        out[i] =  _buffer[i];
    }

    return noutput_items;
}

} /* namespace bb60 */
} /* namespace gr */
