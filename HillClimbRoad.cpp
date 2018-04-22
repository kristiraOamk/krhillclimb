#include <iostream>
#include <HillClimbUtility.h>
#include "HillClimbRoad.h"

namespace hillclimb{
    
    HillClimbRoad::HillClimbRoad(const int winWidth, const int winHeight){
        DEFAULT_ROAD_LENGTH=100;
        addPart(0,300);

        addPart(100,400);
        addPart(200,300);
        addPart(300,400);
        //while(getPartCount()<DEFAULT_ROAD_LENGTH);
        generatePartsAhead();       
        generatePartsAhead();
        generatePartsAhead();
        generatePartsAhead();
    }
    
    int HillClimbRoad::getPartCount()
    {
        return static_cast<int>(this->partCoords.size());
    }
    
    std::vector<Coordinates> HillClimbRoad::getPartCoords(){
        return this->partCoords;
    }
    
    void HillClimbRoad::addPart(double x, double y){
        Coordinates partCoord={
            partCoord.x=x,
            partCoord.y=y
        };
        this->partCoords.push_back(partCoord);
        
    }
    
    void HillClimbRoad::move(const double x) {
       //move the x's of parts
       //deletePartsBehind
       //generatePartsAhead
       for (auto& coords: this->partCoords){
           coords.x -=x;
       }
   }

   //ROAD_LENGHT_FACTOR = choose some road length factor


   double HillClimbRoad::calculateNewPartX(double ex) {
       //randomize length of the new part using some factor
       double roadX=ex+100;
       std::cout <<"roadX "<< roadX<<"\n";
       return roadX;
   }

   double HillClimbRoad::calculateNewPartY() {
       //randomize y position of the end point of the new part
       return 500;//+(partCoords.size()*partCoords.size());
   }

   void HillClimbRoad::generatePartsAhead() {


        int partnumber=getPartCount();
        std::vector<Coordinates> beginCoords = getPartCoords();//partCoordPair at current index + 1
        auto beginnin = beginCoords[partnumber-1];//partCoords.size()-1];
        double xx=calculateNewPartX(beginnin.x);
        if(partnumber%2==0)addPart(xx,300);
        else addPart(xx,400);



   }

   void deletePartsBehind() {
      //delete parts whose x < -DEFAULT_ROAD_LENGTH * ROAD_LENGTH_FACTOR
   }

   

   void reset()
   {
       //clear partCoords
       //add two horizontal parts
       //generatePartsAhead
   }
   
}
