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


std::string Controller::fundCampaign(const std::string& brand, const std::string& amountStr) const{
    Campaign* campaign = campaigns.findByName(brand);
    if(campaign == nullptr)
        return "Trying to fund an invalid campaign.";
    
    double amount;
    try{
        amount = std::stod(amountStr);
    }
    catch(...){
        return "Funding amount must be a valid number.";
    }
    
    try{
        campaign->gain(amount);
        return brand + " campaign has been successfully funded with " + amountStr + " $";
    }
    catch(...){
        return "Funding amount must be greater than zero.";
    }
    
    
}


std::string Controller::closeCampaign(const std::string& brand){
    Campaign* campaign = campaigns.findByName(brand);
    if(campaign == nullptr)
        return "Trying to close an invalid campaign.";
    double budget = campaign->getBudget();
    if(budget <= 10000)
        return brand + " campaign cannot be closed as it has not met its financial targets.";
    std::vector<std::string> contributors = campaign->getContributors();
    const size_t size = contributors.size();
    for(size_t i = 0;i<size;i++){
        Influencer* infl = influencers.findByName(contributors[i]);
        if(infl){
            infl->earnFee(2000);
            infl->endParticipation(brand);
        }
    }
    campaigns.remove(campaign);
    return brand + " campaign has reached its target.";
}


std::string Controller::concludeAppContract(const std::string& userName){
    Influencer* infl = influencers.findByName(userName);
    if(infl == nullptr)
        return userName + " has still not signed a contract";
    size_t activeCampaigns = infl->getParticipationsCount();
    if(activeCampaigns > 0)
        return userName + " cannot conclude contract while enrolled in active campaigns.";
    
    influencers.remove(infl);
    return userName + " concluded their contract.";
}


void Controller::applicationReportCommand() {
    influencers.sortInfluencersByIncomeThenByFollowers();
    influencers.printInfluencersAndActiveCampaigns();
}
