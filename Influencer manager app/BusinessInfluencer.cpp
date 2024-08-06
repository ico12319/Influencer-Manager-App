#include <stdio.h>
#include "BusinessInfluencer.h"

BusinessInfluencer::BusinessInfluencer() : Influencer(){}

BusinessInfluencer::BusinessInfluencer(const std::string& name,size_t followers) : Influencer(name, followers, 3){}

Influencer* BusinessInfluencer::clone() const{
    return new BusinessInfluencer(*this);
}

int BusinessInfluencer::calculateCampaignPrice() const{
    const double factor = 0.15;
    return (followers * engagementRate * factor);
}

InfluencerType BusinessInfluencer::getType() const{
    return InfluencerType::BUSINESS_INFLUENCER;
}
