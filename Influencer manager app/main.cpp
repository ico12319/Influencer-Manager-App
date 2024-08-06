#include "Controller.h"

int main(int argc, const char * argv[]) {
    
    //std::string typeName = "BusinessInfluencer";
    //std::string userName = "Chicata13";
    //int followers = 103;
    //std::string typeName2 = "ServiceCampaign";
    //std::string brand = "Kisenko";
    //std::string typeName3 = "ProductCampaign";
    //std::string brand2 = "Kisenko";
    //Controller controller;
    //std::cout<<controller.registerInfluencer(typeName, userName, followers)<<std::endl;
    //std::cout<<controller.beginCampaign(typeName2, brand)<<std::endl;
    //std::cout<<controller.beginCampaign(typeName3, brand2)<<std::endl;
    
    InfluencerRepo iRepo;
    std::string userName1 = "Kisata";
    std::string typeName = "BusinessInfluencer";
    Influencer* i1 = new BusinessInfluencer(userName1,10000);
    iRepo.addModel(i1);
    
    CampaignRepo cRepo;
    std::string brand1 = "Nike";
    Campaign* camp = new ServiceCampaign(brand1);
    cRepo.addModel(camp);
    
    std::string brand = "Nike";
    std::string userName = "Kisata";
    Controller controller(iRepo,cRepo);
    std::cout<<controller.attractInfluencer(brand, userName);
    
    
}

