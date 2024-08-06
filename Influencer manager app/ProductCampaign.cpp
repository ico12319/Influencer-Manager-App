#include <stdio.h>
#include "ProductCampaign.h"

ProductCampaign::ProductCampaign() : Campaign(){}

ProductCampaign::ProductCampaign(const std::string& name) : Campaign(name, 60000){}

Campaign* ProductCampaign::clone() const{
    return new ProductCampaign(*this);
}

CampaignType ProductCampaign::getType() const{
    return CampaignType::PRODUCT_CAMPAIGN;
}
