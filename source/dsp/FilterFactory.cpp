#include "FilterFactory.h"

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
FilterFactory::updateLowCut(MonoChain& chain, CutBand& params, double sample_rate)
{
    if (params.freq_ == nullptr || params.slope_ == nullptr || params.enabled_ == nullptr) {
        return;
    }

    auto& cut_filter_chain = chain.get< ChainPosition::LOW_CUT >();

    cut_filter_chain.setBypassed< SLOPE_12 >(true);
    cut_filter_chain.setBypassed< SLOPE_24 >(true);
    cut_filter_chain.setBypassed< SLOPE_36 >(true);
    cut_filter_chain.setBypassed< SLOPE_48 >(true);

    auto coefficients = getLowCutCoefficients(sample_rate, params);

    switch (params.slope_->getIndex()) {
    case SLOPE_48:
        *cut_filter_chain.get< SLOPE_48 >().coefficients = *coefficients[SLOPE_48];
        cut_filter_chain.setBypassed< SLOPE_48 >(false);

    case SLOPE_36:
        *cut_filter_chain.get< SLOPE_36 >().coefficients = *coefficients[SLOPE_36];
        cut_filter_chain.setBypassed< SLOPE_36 >(false);

    case SLOPE_24:
        *cut_filter_chain.get< SLOPE_24 >().coefficients = *coefficients[SLOPE_24];
        cut_filter_chain.setBypassed< SLOPE_24 >(false);

    case SLOPE_12:
        *cut_filter_chain.get< SLOPE_12 >().coefficients = *coefficients[SLOPE_12];
        cut_filter_chain.setBypassed< SLOPE_12 >(false);
        break;

    default:
        break;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
FilterFactory::updateHighCut(MonoChain& chain, CutBand& params, double sample_rate)
{
    if (params.freq_ == nullptr || params.slope_ == nullptr || params.enabled_ == nullptr) {
        return;
    }

    auto& cut_filter_chain = chain.get< ChainPosition::HIGH_CUT >();

    cut_filter_chain.setBypassed< SLOPE_12 >(true);
    cut_filter_chain.setBypassed< SLOPE_24 >(true);
    cut_filter_chain.setBypassed< SLOPE_36 >(true);
    cut_filter_chain.setBypassed< SLOPE_48 >(true);

    auto coefficients = getHighCutCoefficients(sample_rate, params);

    switch (params.slope_->getIndex()) {
    case SLOPE_48:
        *cut_filter_chain.get< SLOPE_48 >().coefficients = *coefficients[SLOPE_48];
        cut_filter_chain.setBypassed< SLOPE_48 >(false);

    case SLOPE_36:
        *cut_filter_chain.get< SLOPE_36 >().coefficients = *coefficients[SLOPE_36];
        cut_filter_chain.setBypassed< SLOPE_36 >(false);

    case SLOPE_24:
        *cut_filter_chain.get< SLOPE_24 >().coefficients = *coefficients[SLOPE_24];
        cut_filter_chain.setBypassed< SLOPE_24 >(false);

    case SLOPE_12:
        *cut_filter_chain.get< SLOPE_12 >().coefficients = *coefficients[SLOPE_12];
        cut_filter_chain.setBypassed< SLOPE_12 >(false);
        break;

    default:
        break;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
FilterFactory::updateLowShelf(MonoChain& chain, ShelfBand& params, double sample_rate)
{
    if (params.freq_ == nullptr || params.gain_ == nullptr || params.q_ == nullptr) {
        return;
    }

    *chain.get< ChainPosition::LOW_SHELF >().coefficients = *getLowShelfCoefficients(sample_rate, params);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
FilterFactory::updateHighShelf(MonoChain& chain, ShelfBand& params, double sample_rate)
{
    if (params.freq_ == nullptr || params.gain_ == nullptr || params.q_ == nullptr) {
        return;
    }

    *chain.get< ChainPosition::HIGH_SHELF >().coefficients = *getHighShelfCoefficients(sample_rate, params);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ void
FilterFactory::updatePeak(MonoChain& chain, const ChainPosition& position, PeakBand& params, double sample_rate)
{
    if (params.freq_ == nullptr || params.gain_ == nullptr || params.q_ == nullptr) {
        return;
    }

    auto coefficients = getPeakCoefficients(sample_rate, params);

    switch (position) {
    case ChainPosition::PEAK_1:
        *chain.get< ChainPosition::PEAK_1 >().coefficients = *coefficients;
        break;

    case ChainPosition::PEAK_2:
        *chain.get< ChainPosition::PEAK_2 >().coefficients = *coefficients;
        break;

    case ChainPosition::PEAK_3:
        *chain.get< ChainPosition::PEAK_3 >().coefficients = *coefficients;
        break;

    case ChainPosition::PEAK_4:
        *chain.get< ChainPosition::PEAK_4 >().coefficients = *coefficients;
        break;

    case ChainPosition::PEAK_5:
        *chain.get< ChainPosition::PEAK_5 >().coefficients = *coefficients;
        break;

    case ChainPosition::LOW_CUT:
    case ChainPosition::HIGH_CUT:
    case ChainPosition::LOW_SHELF:
    case ChainPosition::HIGH_SHELF:
        break;

    default:
        break;
    }
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ FilterFactory::RefCtArrCoefficients
FilterFactory::getLowCutCoefficients(double sample_rate, CutBand& params)
{
    return juce::dsp::FilterDesign< float >::designIIRHighpassHighOrderButterworthMethod(params.freq_->get(),
                                                                                         sample_rate,
                                                                                         (params.slope_->getIndex() + 1)
                                                                                             * 2);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ FilterFactory::RefCtArrCoefficients
FilterFactory::getHighCutCoefficients(double sample_rate, CutBand& params)
{
    return juce::dsp::FilterDesign< float >::designIIRLowpassHighOrderButterworthMethod(params.freq_->get(),
                                                                                        sample_rate,
                                                                                        (params.slope_->getIndex() + 1)
                                                                                            * 2);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ FilterFactory::RefCtObjCoefficients
FilterFactory::getLowShelfCoefficients(double sample_rate, ShelfBand& params)
{
    return juce::dsp::IIR::Coefficients< float >::makeLowShelf(sample_rate,
                                                               params.freq_->get(),
                                                               params.q_->get(),
                                                               juce::Decibels::decibelsToGain(params.gain_->get()));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ FilterFactory::RefCtObjCoefficients
FilterFactory::getHighShelfCoefficients(double sample_rate, ShelfBand& params)
{
    return juce::dsp::IIR::Coefficients< float >::makeHighShelf(sample_rate,
                                                                params.freq_->get(),
                                                                params.q_->get(),
                                                                juce::Decibels::decibelsToGain(params.gain_->get()));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ FilterFactory::RefCtObjCoefficients
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
