#include <stdio.h>
#include "Controller.h"


static bool isEligible(const CampaignType& campaignType,const InfluencerType& influencerType){
    if(campaignType == CampaignType::PRODUCT_CAMPAIGN && (influencerType == InfluencerType::BUSINESS_INFLUENCER || influencerType == InfluencerType::FASHION_INFLUENCER)){
        return true;
    }
    else if(campaignType == CampaignType::SERVICE_CAMPAIGN && (influencerType == InfluencerType::BUSINESS_INFLUENCER || influencerType == InfluencerType::BLOGGER_INFLUENCER)){
        return true;
    }
    return false;
}

Controller::Controller(const InfluencerRepo& influencers,const CampaignRepo& campaigns){
    this->influencers = influencers;
    this->campaigns = campaigns;
}

std::string Controller::registerInfluencer(const std::string& typeName, const std::string& userName, int followers) {
    if(influencers.findByName(userName)!=nullptr)
        return userName + " is already registered in Influencer repository.";
    
    Influencer* influencer = nullptr;
    if(typeName == "BusinessInfluencer")
        influencer = new BusinessInfluencer(userName,followers);
    else if(typeName == "FashionInfluencer")
        influencer = new FashionInfluencer(userName,followers);
    else if(typeName == "BloggerInfluencer")
        influencer = new BloggerInfluencer(userName,followers);
    else{
        delete influencer;
        return typeName + " has not passed validation.";
    }
    influencers.addModel(influencer);
    return userName + " registered successfully to the application.";
}

std::string Controller::beginCampaign(const std::string& typeName, const std::string& brand){
    if(campaigns.findByName(brand) != nullptr)
        return brand + " campaign cannot be diplicated.";
    
    Campaign* campaign = nullptr;
    if(typeName == "ProductCampaign")
        campaign = new ProductCampaign(brand);
    else if(typeName == "ServiceCampaign")
        campaign = new ServiceCampaign(brand);
    else{
        delete campaign;
        return typeName + " is not a valid campaign in the application.";
    }
    campaigns.addModel(campaign);
    return brand + " started a " + typeName + ".";
}


std::string Controller::attractInfluencer(const std::string& brand, const std::string& userName) const{
    Influencer* influencer = influencers.findByName(userName);
    if(influencer == nullptr){
        return "Influencer Repo has no " + userName + " registered in the application.";
    }
    Campaign* campaign = campaigns.findByName(brand);
    if(campaign == nullptr){
        return "There is no campaign from " + brand + " in the application.";
    }
    bool isContributor = campaign->containsInfluencer(influencer);
    if(isContributor)
        return userName + " is already engaged for the " + brand + " campaign.";
    CampaignType campaignType = campaign->getType();
    InfluencerType influencerType = influencer->getType();
    if(!isEligible(campaignType, influencerType))
        return userName + " is not eligible for the " + brand + " campaign.";
    
    try{
        campaign->engage(influencer);
        int cPrice = influencer->calculateCampaignPrice();
        influencer->earnFee(cPrice);
        influencer->enrollCampaign(brand);
        return userName + " has been successfully attracted to the " + brand + " campaign.";
    }
    catch(const std::logic_error& e){
        return "The budget for " + brand + " is insufficient to engage " + userName + ".";
    }
}
