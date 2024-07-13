#include "Equalizer.h"
#include "../utility/GlobalConstants.h"

/*static*/ const float Equalizer::DEFAULT_BAND_DB = 0.f;
/*static*/ const float Equalizer::DEFAULT_BAND_Q  = 2.f;

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::String
Equalizer::getBandName(BAND_ID band_id)
{
    switch (band_id) {
    case B1:
        return "B1";
    case B2:
        return "B2";
    case B3:
        return "B3";
    case B4:
        return "B4";
    case B5:
        return "B5";
    case B6:
        return "B6";
    case B7:
        return "B7";
    case B8:
        return "B8";
    case B9:
        return "B9";
    case B10:
        return "B10";
    case B11:
        return "B11";
    case B12:
        return "B12";
    case B13:
        return "B13";
    case B14:
        return "B14";
    case B15:
        return "B15";
    case B16:
        return "B16";
    case B17:
        return "B17";
    case B18:
        return "B18";
    case B19:
        return "B19";
    case B20:
        return "B20";
    case B21:
        return "B21";
    case B22:
        return "B22";
    case B23:
        return "B23";
    case B24:
        return "B24";
    case B25:
        return "B25";
    case B26:
        return "B26";
    case B27:
        return "B27";
    case B28:
        return "B28";
    case B29:
        return "B29";
    case B30:
        return "B30";
    case B31:
        return "B31";

    default:
        return "";
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
Equalizer::getBandHz(BAND_ID band_id)
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
Equalizer::getBandTestDb(BAND_ID band_id)
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
Equalizer::getBandTargetDb(BAND_ID band_id)
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
        return -18.f;

    default:
        return -18.f;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
Equalizer::updateBandCoefficients(MonoChain& chain, const BAND_ID& band_id, float gain, double sample_rate)
{
    auto cf = juce::dsp::IIR::Coefficients< float >::makePeakFilter(sample_rate, getBandHz(band_id), DEFAULT_BAND_Q, gain);

    switch (band_id) {
    case B1:
        *chain.get< B1 >().coefficients = *cf;
        break;

    case B2:
        *chain.get< B2 >().coefficients = *cf;
        break;

    case B3:
        *chain.get< B3 >().coefficients = *cf;
        break;

    case B4:
        *chain.get< B4 >().coefficients = *cf;
        break;

    case B5:
        *chain.get< B5 >().coefficients = *cf;
        break;

    case B6:
        *chain.get< B6 >().coefficients = *cf;
        break;

    case B7:
        *chain.get< B7 >().coefficients = *cf;
        break;

    case B8:
        *chain.get< B8 >().coefficients = *cf;
        break;

    case B9:
        *chain.get< B9 >().coefficients = *cf;
        break;

    case B10:
        *chain.get< B10 >().coefficients = *cf;
        break;

    case B11:
        *chain.get< B11 >().coefficients = *cf;
        break;

    case B12:
        *chain.get< B12 >().coefficients = *cf;
        break;

    case B13:
        *chain.get< B13 >().coefficients = *cf;
        break;

    case B14:
        *chain.get< B14 >().coefficients = *cf;
        break;

    case B15:
        *chain.get< B15 >().coefficients = *cf;
        break;

    case B16:
        *chain.get< B16 >().coefficients = *cf;
        break;

    case B17:
        *chain.get< B17 >().coefficients = *cf;
        break;

    case B18:
        *chain.get< B18 >().coefficients = *cf;
        break;

    case B19:
        *chain.get< B19 >().coefficients = *cf;
        break;

    case B20:
        *chain.get< B20 >().coefficients = *cf;
        break;

    case B21:
        *chain.get< B21 >().coefficients = *cf;
        break;

    case B22:
        *chain.get< B22 >().coefficients = *cf;
        break;

    case B23:
        *chain.get< B23 >().coefficients = *cf;
        break;

    case B24:
        *chain.get< B24 >().coefficients = *cf;
        break;

    case B25:
        *chain.get< B25 >().coefficients = *cf;
        break;

    case B26:
        *chain.get< B26 >().coefficients = *cf;
        break;

    case B27:
        *chain.get< B27 >().coefficients = *cf;
        break;

    case B28:
        *chain.get< B28 >().coefficients = *cf;
        break;

    case B29:
        *chain.get< B29 >().coefficients = *cf;
        break;

    case B30:
        *chain.get< B30 >().coefficients = *cf;
        break;

    case B31:
        *chain.get< B31 >().coefficients = *cf;
        break;

    default:
        break;
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
