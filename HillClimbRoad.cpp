#include <iostream>
#include <HillClimbUtility.h>
#include "HillClimbRoad.h"

namespace hillclimb{
    
    HillClimbRoad::HillClimbRoad(const int winWidth, const int winHeight){
               
    }
    
    int HillClimbRoad::getPartCount()
    {
        return static_cast<int>(this->partCoords.size());
    }
    
    std::vector<Coordinates> HillClimbRoad::getPartCoords(){
        if(getPartCount()==0)generatePartsAhead();
        return this->partCoords;
    }
    
    void HillClimbRoad::addPart(double x, double y){
        Coordinates partCoord={
            .x=x,
            .y=y
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


   int calculateNewPartX() {
       //randomize length of the new part using some factor
       return 0;
   }

   void calculateNewPartY() {
       //randomize y position of the end point of the new part
   }

   void HillClimbRoad::generatePartsAhead() {
      //generate parts as many as MAX_PART_COUNT - currentPartCount
        addPart(0,500);
        addPart(1500,500);
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

/*
#include <iostream>
#include "HillClimbRoad.h"

namespace hillclimb{

   //ROAD_LENGHT_FACTOR = choose some road length factor

   HillClimbRoad::HillClimbRoad(int winWidth, int winHeight)
        :winWidth(winWidth), winHeight(winHeight){}

   function getPartCount

   function getPartCoords

   function addPart

   function calculateNewPartX {
       //randomize length of the new part using some factor
   }

   function calculateNewPartY {
       randomize y position of the end point of the new part
   }

   function generatePartsAhead {
      generate parts as many as MAX_PART_COUNT - currentPartCount
   }

   deletePartsBehind() {
      delete parts whose x < -DEFAULT_ROAD_LENGTH * ROAD_LENGTH_FACTOR
   }

   move(x) {
       move the x's of parts
       deletePartsBehind
       generatePartsAhead
   }

   reset
       clear partCoords
       add two horizontal parts
       generatePartsAhead
   }
}
*/