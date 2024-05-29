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
