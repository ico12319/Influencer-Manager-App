#include <stdio.h>
#include "BloggerInfluencer.h"

BloggerInfluencer::BloggerInfluencer() : Influencer(){}

BloggerInfluencer::BloggerInfluencer(const std::string& name,size_t followers) : Influencer(name, followers, 2){}

Influencer* BloggerInfluencer::clone() const{
    return new BloggerInfluencer(*this);
}

int BloggerInfluencer::calculateCampaignPrice() const{
    const double factor = 0.2;
    return (followers * factor * engagementRate);
}


InfluencerType BloggerInfluencer::getType() const{
    return InfluencerType::BLOGGER_INFLUENCER;
}
