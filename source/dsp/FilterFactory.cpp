#include "FilterFactory.h"

/*static*/ const uint8 FilterFactory::NUM_BANDS         = 31;
/*static*/ const float FilterFactory::MAX_BAND_DB_BOOST = 12.f;
/*static*/ const float FilterFactory::MAX_BAND_DB_CUT   = -12.f;
/*static*/ const float FilterFactory::DEFAULT_BAND_DB   = 0.f;
/*static*/ const float FilterFactory::DEFAULT_BAND_Q    = 2.f;

/*static*/ const juce::NormalisableRange< float > FilterFactory::BAND_DB_RANGE =
    juce::NormalisableRange< float >(MAX_BAND_DB_CUT, MAX_BAND_DB_BOOST, 0.5f, 1.f);

/*static*/ const int FilterFactory::PARAMETERS_VERSION_HINT = 1;

/*---------------------------------------------------------------------------
**
*/
FilterFactory::FilterFactory()
{
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::String
FilterFactory::getBandName(BAND_ID band_id)
{
    return juce::String("B") + juce::String(band_id + 1);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
FilterFactory::getBandHz(BAND_ID band_id)
{
    switch (band_id) {
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
/*static*/ float
FilterFactory::getBandTestDb(BAND_ID band_id)
{
    switch (band_id) {
    case B1:
    case B2:
    case B3:
    case B4:
    case B5:
    case B6:
    case B7:
    case B8:
    case B9:
    case B10:
    case B11:
    case B12:
    case B13:
    case B14:
    case B15:
    case B16:
    case B17:
    case B18:
    case B19:
    case B20:
    case B21:
    case B22:
    case B23:
    case B24:
    case B25:
    case B26:
    case B27:
    case B28:
    case B29:
    case B30:
    case B31:
        return 3.f;

    default:
        return 3.f;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
FilterFactory::getBandTargetDb(BAND_ID band_id)
{
    // TODO find the correct magnitude target for each band/frequency.
    switch (band_id) {
    case B1:
    case B2:
    case B3:
    case B4:
    case B5:
    case B6:
    case B7:
    case B8:
    case B9:
    case B10:
    case B11:
    case B12:
    case B13:
    case B14:
    case B15:
    case B16:
    case B17:
    case B18:
    case B19:
    case B20:
    case B21:
    case B22:
    case B23:
    case B24:
    case B25:
    case B26:
    case B27:
    case B28:
    case B29:
    case B30:
    case B31:
        return 0.f;

    default:
        return 0.f;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
FilterFactory::addBandToParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& pl, BAND_ID band_id)
{
    pl.add(std::make_unique< juce::AudioParameterFloat >(getVersionedParameterId(band_id),
                                                         getBandName(band_id),
                                                         BAND_DB_RANGE,
                                                         DEFAULT_BAND_DB));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
FilterFactory::updateBandCoefficients(MonoChain& chain, const BAND_ID& band_id, float gain, double sample_rate)
{
    auto cf = juce::dsp::IIR::Coefficients< float >::makePeakFilter(sample_rate, getBandHz(band_id), DEFAULT_BAND_Q, gain);

    switch (band_id) {
    case BAND_ID::B1:
        *chain.get< BAND_ID::B1 >().coefficients = *cf;
        break;

    case BAND_ID::B2:
        *chain.get< BAND_ID::B2 >().coefficients = *cf;
        break;

    case BAND_ID::B3:
        *chain.get< BAND_ID::B3 >().coefficients = *cf;
        break;

    case BAND_ID::B4:
        *chain.get< BAND_ID::B4 >().coefficients = *cf;
        break;

    case BAND_ID::B5:
        *chain.get< BAND_ID::B5 >().coefficients = *cf;
        break;

    case BAND_ID::B6:
        *chain.get< BAND_ID::B6 >().coefficients = *cf;
        break;

    case BAND_ID::B7:
        *chain.get< BAND_ID::B7 >().coefficients = *cf;
        break;

    case BAND_ID::B8:
        *chain.get< BAND_ID::B8 >().coefficients = *cf;
        break;

    case BAND_ID::B9:
        *chain.get< BAND_ID::B9 >().coefficients = *cf;
        break;

    case BAND_ID::B10:
        *chain.get< BAND_ID::B10 >().coefficients = *cf;
        break;

    case BAND_ID::B11:
        *chain.get< BAND_ID::B11 >().coefficients = *cf;
        break;

    case BAND_ID::B12:
        *chain.get< BAND_ID::B12 >().coefficients = *cf;
        break;

    case BAND_ID::B13:
        *chain.get< BAND_ID::B13 >().coefficients = *cf;
        break;

    case BAND_ID::B14:
        *chain.get< BAND_ID::B14 >().coefficients = *cf;
        break;

    case BAND_ID::B15:
        *chain.get< BAND_ID::B15 >().coefficients = *cf;
        break;

    case BAND_ID::B16:
        *chain.get< BAND_ID::B16 >().coefficients = *cf;
        break;

    case BAND_ID::B17:
        *chain.get< BAND_ID::B17 >().coefficients = *cf;
        break;

    case BAND_ID::B18:
        *chain.get< BAND_ID::B18 >().coefficients = *cf;
        break;

    case BAND_ID::B19:
        *chain.get< BAND_ID::B19 >().coefficients = *cf;
        break;

    case BAND_ID::B20:
        *chain.get< BAND_ID::B20 >().coefficients = *cf;
        break;

    case BAND_ID::B21:
        *chain.get< BAND_ID::B21 >().coefficients = *cf;
        break;

    case BAND_ID::B22:
        *chain.get< BAND_ID::B22 >().coefficients = *cf;
        break;

    case BAND_ID::B23:
        *chain.get< BAND_ID::B23 >().coefficients = *cf;
        break;

    case BAND_ID::B24:
        *chain.get< BAND_ID::B24 >().coefficients = *cf;
        break;

    case BAND_ID::B25:
        *chain.get< BAND_ID::B25 >().coefficients = *cf;
        break;

    case BAND_ID::B26:
        *chain.get< BAND_ID::B26 >().coefficients = *cf;
        break;

    case BAND_ID::B27:
        *chain.get< BAND_ID::B27 >().coefficients = *cf;
        break;

    case BAND_ID::B28:
        *chain.get< BAND_ID::B28 >().coefficients = *cf;
        break;

    case BAND_ID::B29:
        *chain.get< BAND_ID::B29 >().coefficients = *cf;
        break;

    case BAND_ID::B30:
        *chain.get< BAND_ID::B30 >().coefficients = *cf;
        break;

    case BAND_ID::B31:
        *chain.get< BAND_ID::B31 >().coefficients = *cf;
        break;

    default:
        break;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::ParameterID
FilterFactory::getVersionedParameterId(BAND_ID band_id)
{
    return juce::ParameterID(getBandName(band_id), PARAMETERS_VERSION_HINT);
}

/*---------------------------------------------------------------------------
** End of File
*/
