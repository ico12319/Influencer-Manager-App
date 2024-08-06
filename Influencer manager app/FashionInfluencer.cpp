#include <stdio.h>
#include "FashionInfluencer.h"

FashionInfluencer::FashionInfluencer() : Influencer(){}

FashionInfluencer::FashionInfluencer(const std::string& name,size_t followers) : Influencer(name, followers, 4){}

Influencer* FashionInfluencer::clone() const{
    return new FashionInfluencer(*this);
}

int FashionInfluencer::calculateCampaignPrice() const{
    const double factor = 0.1;
    return (followers * engagementRate * factor);
}

InfluencerType FashionInfluencer::getType() const{
    return InfluencerType::FASHION_INFLUENCER;
}
