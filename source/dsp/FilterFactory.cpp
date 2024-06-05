#include "FilterFactory.h"

/*static*/ const uint8 FilterFactory::NUM_BANDS         = 31;
/*static*/ const float FilterFactory::MAX_BAND_DB_BOOST = 12.f;
/*static*/ const float FilterFactory::MAX_BAND_DB_CUT   = -12.f;

/*---------------------------------------------------------------------------
**
*/
FilterFactory::FilterFactory()
{
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
FilterFactory::getHzForBand(Band band)
{
    switch (band) {
    case B1:
        return 20.f;
    case B2:
        return 25.f;
    case B3:
        return 31.5f;
    case B4:
        return 40.f;
    case B5:
        return 50.f;
    case B6:
        return 63.f;
    case B7:
        return 80.f;
    case B8:
        return 100.f;
    case B9:
        return 125.f;
    case B10:
        return 160.f;
    case B11:
        return 200.f;
    case B12:
        return 250.f;
    case B13:
        return 315.f;
    case B14:
        return 400.f;
    case B15:
        return 500.f;
    case B16:
        return 630.f;
    case B17:
        return 800.f;
    case B18:
        return 1000.f;
    case B19:
        return 1250.f;
    case B20:
        return 1600.f;
    case B21:
        return 2000.f;
    case B22:
        return 2500.f;
    case B23:
        return 3150.f;
    case B24:
        return 4000.f;
    case B25:
        return 5000.f;
    case B26:
        return 6300.f;
    case B27:
        return 8000.f;
    case B28:
        return 10000.f;
    case B29:
        return 12500.f;
    case B30:
        return 16000.f;
    case B31:
        return 20000.f;

    default:
        return 0.f;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
FilterFactory::updatePeak(MonoChain& chain, const Band& band_id, PeakBand& params, double sample_rate)
{
    if (params.freq_ == nullptr || params.gain_ == nullptr || params.q_ == nullptr) {
        return;
    }

    auto coefficients = getPeakCoefficients(sample_rate, params);

    switch (band_id) {
    case Band::B1:
        *chain.get< Band::B1 >().coefficients = *coefficients;
        break;

    case Band::B2:
        *chain.get< Band::B2 >().coefficients = *coefficients;
        break;

    case Band::B3:
        *chain.get< Band::B3 >().coefficients = *coefficients;
        break;

    case Band::B4:
        *chain.get< Band::B4 >().coefficients = *coefficients;
        break;

    case Band::B5:
        *chain.get< Band::B5 >().coefficients = *coefficients;
        break;

    case Band::B6:
        *chain.get< Band::B6 >().coefficients = *coefficients;
        break;

    case Band::B7:
        *chain.get< Band::B7 >().coefficients = *coefficients;
        break;

    case Band::B8:
        *chain.get< Band::B8 >().coefficients = *coefficients;
        break;

    case Band::B9:
        *chain.get< Band::B9 >().coefficients = *coefficients;
        break;

    case Band::B10:
        *chain.get< Band::B10 >().coefficients = *coefficients;
        break;

    case Band::B11:
        *chain.get< Band::B11 >().coefficients = *coefficients;
        break;

    case Band::B12:
        *chain.get< Band::B12 >().coefficients = *coefficients;
        break;

    case Band::B13:
        *chain.get< Band::B13 >().coefficients = *coefficients;
        break;

    case Band::B14:
        *chain.get< Band::B14 >().coefficients = *coefficients;
        break;

    case Band::B15:
        *chain.get< Band::B15 >().coefficients = *coefficients;
        break;

    case Band::B16:
        *chain.get< Band::B16 >().coefficients = *coefficients;
        break;

    case Band::B17:
        *chain.get< Band::B17 >().coefficients = *coefficients;
        break;

    case Band::B18:
        *chain.get< Band::B18 >().coefficients = *coefficients;
        break;

    case Band::B19:
        *chain.get< Band::B19 >().coefficients = *coefficients;
        break;

    case Band::B20:
        *chain.get< Band::B20 >().coefficients = *coefficients;
        break;

    case Band::B21:
        *chain.get< Band::B21 >().coefficients = *coefficients;
        break;

    case Band::B22:
        *chain.get< Band::B22 >().coefficients = *coefficients;
        break;

    case Band::B23:
        *chain.get< Band::B23 >().coefficients = *coefficients;
        break;

    case Band::B24:
        *chain.get< Band::B24 >().coefficients = *coefficients;
        break;

    case Band::B25:
        *chain.get< Band::B25 >().coefficients = *coefficients;
        break;

    case Band::B26:
        *chain.get< Band::B26 >().coefficients = *coefficients;
        break;

    case Band::B27:
        *chain.get< Band::B27 >().coefficients = *coefficients;
        break;

    case Band::B28:
        *chain.get< Band::B28 >().coefficients = *coefficients;
        break;

    case Band::B29:
        *chain.get< Band::B29 >().coefficients = *coefficients;
        break;

    case Band::B30:
        *chain.get< Band::B30 >().coefficients = *coefficients;
        break;

    case Band::B31:
        *chain.get< Band::B31 >().coefficients = *coefficients;
        break;

    default:
        break;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ FilterFactory::BandCoefficients
FilterFactory::getPeakCoefficients(double sample_rate, PeakBand& params)
{
    return juce::dsp::IIR::Coefficients< float >::makePeakFilter(sample_rate,
                                                                 params.freq_->get(),
                                                                 params.q_->get(),
                                                                 juce::Decibels::decibelsToGain(params.gain_->get()));
}

/*---------------------------------------------------------------------------
** End of File
*/
