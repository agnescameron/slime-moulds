//A basic model of amoebic behaviour in physarum polycephalum, based on that
//proposed by Gunji et. al. Simulation prints 'slime graphic' to termial. The
//Gunji model is developed by introducing random distributions of food, as
//opposed to the original model, which dictates a particular morphology of
//places where empty cells can and cannot enter the slime, and therefore particular
//patterns of migration

//Agnes Cameron, 2017

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <ctime>
#include <ctype.h>
#include <sstream>

using namespace std;


//This function prints the 50 x 100 part of the array. Spaces represent empty cells,
// + symbols interior cells, * symbols boundary cells
void print(int array[52][102], int simsteps)
{
 cout << "#################" << endl << "Time = " << simsteps << endl;
 for(int j = 1; j < 51; j++)
   {
    for(int i = 1; i < 101; i++) 			
	{

 		
 		    if(array[j][i] == 6)
				cout << '!'; 
 		    else if(array[j][i] == 5)
				cout << '@'; 
		    else if(array[j][i] == 4)
				cout << '8'; 
		    else if(array[j][i] == 3)
				cout << 'o';
			else if(array[j][i] == 2)
				cout << '*';
			else if(array[j][i] == 1)
				cout << '+';
			else
			    cout << ' ';
		}
		cout << endl;
 	}
 	cout << endl << endl;
}

//Copies one array to another.
void copy(int array1[52][102], int array2[52][102])
{
    for(int i = 0; i < 102; i++)  
  {
		for(int j = 0; j < 52; j++)
			array2[j][i] = array1[j][i]; 
	}
}

//This is the first phase of slime generation
void growth(int array[52][102], int m)
{

  //Copies the main array to a temp array so changes can be entered into a grid
  //without effecting the other cells and the calculations being performed on them.
  int temp[52][102];
  copy(array, temp);
	
	for(int i = 1; i < 101; i++)
 	{
 		for(int j = 1; j < 51; j++)
		{	
		    // if the cell is empty
		    if (array[j][i] == 0){
		         
		         // if the empty cell borders a boundary, it becomes a boundary
		         if (array[j-1][i] ==2 || array[j][i-1] ==2 || array[j+1][i] ==2 || array[j][i+1] == 2)
		             temp[j][i] = 2;
		      // if the empty cell borders a plasma, it becomes a boundary
		         else if (array[j-1][i] ==1 || array[j][i-1] ==1 || array[j+1][i] ==1 || array[j][i+1] == 1)
		             temp[j][i] = 2;
		         //otherwise, the cell remains the same
		         else   
		           temp[j][i] = array[j][i]; 
		    }         
		    
		    else if (array[j][i] == 1 || array[j][i] == 4){
		    //if the cell is in the plasma, it remains in the plasma
                    temp[j][i] = array[j][i];

		    }
		    
		    
		    //if the cell is a boundary cell, it becomes absorbed into the plasma
		    else{
		        temp[j][i] = 1;
		    }
							
		}
 	}
  //Copies the completed temp array back to the main array.
  copy(temp, array);
}

//this selects the area that the bubble can enter when food present
void markUpEdge(int array[52][102], vector<int> pointCoords){
    // this function takes the minimum distances between food sources and edge cells
    //and marks up possible bubble entrance points. The mechanism for this is to allow
    //entrance from bubbles within a 5x5 square (eg +- 2). This mimics the chemotactic motion of the slime
        int minPointi = pointCoords[0];
        int minPointj = pointCoords[1];

        
            for(int i=-2; i < 2; i++){
                for(int j = -2; j<2; j++){
                    if(array[minPointj + j][minPointi + i] == 2){
                        array[minPointj + j][minPointi + i] = 5;
                    }
                }
            }
    
}

//calcuates the minimum distance between an edge and a food source
void foodZones(int array[52][102], int food, vector<vector<int> > foodLocator){
    //stuff goes here
    
 int a = 0;

    //create a vector containing every edge element (cell type 2) of the slime
    int edgeNum = 0;
    vector<vector<int> > edgeVector;
    
    	for(int j = 1; j < 51; j++)
        	{
            for(int i = 1; i < 101; i++) 			
	        	{
                    if(array[j][i] == 2){
                    vector<int> coord;
                    
                    //write co-ordinates of each edge to the vector
                    coord.push_back(i);
                    coord.push_back(j);
                    
                    //push back the co-ordinates of the edge cell
                    edgeVector.push_back (coord);
                    edgeNum = edgeNum + 1;
	        	}
		    }
		}

      do{
        //cycles through food sources one-by one to test against edge cells
        int foodLoci = foodLocator[a][0];
        int foodLocj = foodLocator[a][1];
        
        //fresh initialise distVector (distance between edge cell and food source) each time
        vector<float> distVector; 
        
        int b = 0;
           do{
               //calculates the distance of each edge point from the food source
               int edgei = edgeVector[b][0];
               int edgej = edgeVector[b][1];
               
               
               double dist = sqrt((double)((edgei - foodLoci)*(edgei - foodLoci) + (edgej - foodLocj)*(edgej - foodLocj)));

               //cout << "distance  " << dist << endl;
               distVector.push_back (dist);
               b = b+1;
           }while(b < edgeNum);
        
        //scan the vector of distances to obtain the minimum distance co-ordinate for
        //that food source. Store in vector of minimum distance co-ordinates
        auto distPointer = minmax_element (distVector.begin(),distVector.end());
        int point = (distPointer.first-distVector.begin());
        
        vector <int> pointCoords;
        
        //stores minimum distance points
        int pointCoordi = edgeVector[point][0];
        int pointCoordj = edgeVector[point][1];
        
        //creates a vector of co-ordinates    
        pointCoords.push_back(pointCoordi);
        pointCoords.push_back(pointCoordj);
        
        //marks the edge with type-5 cells to show clearly the potential points
        //of entry for bubbles into the plasmodium. 
        markUpEdge(array, pointCoords);
        
        a = a+1;
        
  	}while(a < food);
}

//checks if a cell is on the edge of the slime
void checkOnEdge(int array[52][102], int s, int bubblei, int bubblej, bool &isOnEdge){
//for a bubble which has entered the plasmodium, checks whether it has reached the edge
//checks each surrounding square in turn, incrementing t each time one is found to be empty
//if the number of empty cells, t, is greater than or equal to s, the cell is on the edge
    int t = 0;
    
    //top
    if(array[bubblej + 1][bubblei] == 0)
        t=t+1;
    else
        t=t;
    
    //right
    if(array[bubblej][bubblei + 1] == 0)
        t=t+1;
    else
        t=t;    

    //below
    if(array[bubblej - 1][bubblei] == 0)
        t=t+1;
    else
        t=t;    

    //left
    if(array[bubblej][bubblei - 1] == 0)
        t=t+1;
    else
        t=t; 

    if(t < s)
       isOnEdge = 0;
       
    else   
       isOnEdge = 1; 
      
}

//checks if the bubble has become trapped (memorised flow)
void checkTrapped(int array[52][102], int bubblei, int bubblej, bool &isTrapped){
//checks each surrounding square in turn, incrementing t each time one is found to be empty
//if the number of empty cells, t, is greater than or equal to s, the cell is on the edge
  //  cout << "checking trapped" << endl;
    
    int t = 0;

    //top
    if(array[bubblej + 1][bubblei] != 1  && array[bubblej][bubblei + 1] != 1 && array[bubblej - 1][bubblei] != 1 && array[bubblej][bubblei - 1] != 1)
         isTrapped = true;

    else   
        isTrapped = false; 

}

//calculates the size of the slime
void countSize(int array[52][102]){
    
    int slimeSize = 0;
     for(int j = 1; j < 51; j++)
       {
        for(int i = 1; i < 101; i++) 			
    	{
		    if(array[j][i] == 1 || array[j][i] == 2 || array[j][i] == 3 || array[j][i] == 6)
                {slimeSize = slimeSize + 1;}
    		}
    		
     	}
 	cout << "seed size " << slimeSize;
}

//chooses the entrance point to the slime for an empty cell
void chooseCell (int array[52][102], int food, int &outerCelli, int &outerCellj, int &entryCelli, int &entryCellj, vector<vector<int> > foodLocator){
  //chooses a boundary (type 2) cell to become the point of entry
  //Randomly selects an adjacent empty cell to be the 'bubble'
  //if there are no food sources, choice is random
  //otherwise, the point of entry is determined by the 
  //position of the food source
  
  bool chosenCell = false;
  bool chosenBubble = false;
  
  if(food == 0){
  //amoebic motion

     //choose the boundary cell to be a point of entry  
       do{

        int rani = rand() %102;
        int ranj = rand() %52;
  
       if (array[ranj][rani] == 2 && (array[ranj + 1][rani] == 0 || array[ranj][rani + 1] == 0 || array[ranj - 1][rani] == 0 || array[ranj][rani - 1] == 0)){
          entryCelli = rani;
          entryCellj = ranj;
      
         chosenCell = true;

        }
  
       else {
          chosenCell = false;
        }
    }while(chosenCell == false);
  }
  
  else{
      //finds the areas of edge closest to food sources
      
      foodZones(array, food, foodLocator);
     // cout << "got after foodZones " << endl;
       do{
        int rani = rand() %102;
        int ranj = rand() %52;
  
       if (array[ranj][rani] == 5){
          entryCelli = rani;
          entryCellj = ranj;
          chosenCell = true;
        }

      }while(chosenCell == false);
  }
   //choose the empty cell to swap with, by randomly guessing neighbouring squares: if the square
    //is empty, the cell is chosen

   do{
    //   srand ( time(NULL) );
    int ranChoice = rand() %4;

//tests cell above  
    if (ranChoice == 0){
      if(array[entryCellj + 1][entryCelli] == 0){
         outerCelli = entryCelli;
         outerCellj = entryCellj + 1;
         

         chosenBubble = true;
      }
      else
         chosenBubble = false;
      }
      
//tests cell right  
    else if (ranChoice == 1){
      if(array[entryCellj][entryCelli +1] == 0){
         outerCelli = entryCelli + 1;
         outerCellj = entryCellj;

         chosenBubble = true;
      }
      else
         chosenBubble = false;
      }
      
      
//tests cell below
    else if (ranChoice == 2){
      if(array[entryCellj - 1][entryCelli] == 0){
         outerCelli = entryCelli;
         outerCellj = entryCellj - 1;

         chosenBubble = true;
      }
      else
         chosenBubble = false;
      }
      
      
 //tests cell left
    else{
      if(array[entryCellj][entryCelli-1] == 0){
         outerCelli = entryCelli - 1;
         outerCellj = entryCellj;

         chosenBubble = true;
      }
      else
         chosenBubble = false;
      }
    
     
  }while(chosenBubble == false);
  
 }
 
 
void chooseNextBubble(int array[52][102], int &bubblei, int &bubblej, int &bubbleNexti, int &bubbleNextj, bool chosenNextBubble)
 { 

  do{

    int ranChoice = rand() %4;

//tests cell above  
    if (ranChoice == 0){
      if(array[bubblej + 1][bubblei] == 1){
         bubbleNexti = bubblei;
         bubbleNextj = bubblej + 1;
         chosenNextBubble = true;
      }
      else
         chosenNextBubble = false;
      }
      
//tests cell right  
    else if (ranChoice == 1){
      if(array[bubblej][bubblei +1] == 1){
         bubbleNexti = bubblei + 1;
         bubbleNextj = bubblej;
         chosenNextBubble = true;
      }
      else
         chosenNextBubble = false;
      }
      
      
//tests cell below
    else if (ranChoice == 2){
      if(array[bubblej - 1][bubblei] == 1){
         bubbleNexti = bubblei;
         bubbleNextj = bubblej - 1;
         chosenNextBubble = true;
      }
      else
         chosenNextBubble = false;
      }
      
      
 //tests cell left
    else if (ranChoice == 3) {
      if(array[bubblej][bubblei - 1] == 1){
         bubbleNexti = bubblei - 1;
         bubbleNextj = bubblej;
         chosenNextBubble = true;
      }
      else
         chosenNextBubble = false;
      }
      
    }while(chosenNextBubble == false);
     
 }


void migration(int array[52][102], int s, int n, int food, char printBubble, vector<vector<int> > foodLocator, int simsteps)
{
//This is the migratory phase of slime simulation. During this phase, the slime no longer
//expands, and instead re-forms itself by randomly absorbing surrounding empty cells 
    
    
  //allows all the cells in the slime to convert to plasmoid, then be converted back    
  int temp1[52][102];
  int temp2[52][102];
  int plasmoid[52][102] = {0};
  
  
  copy(array, temp1);
  copy(temp1, temp2);
  //picks an entry point for the bubble into the cell
  
  int outerCelli;
  int outerCellj;
  int entryCelli;
  int entryCellj; 
  
  chooseCell(array, food, outerCelli, outerCellj, entryCelli, entryCellj, foodLocator);

 	//the bubble enters the slime
 	temp1[entryCellj][entryCelli] = 0;
    temp1[outerCellj][outerCelli] = 2;
    

   //renders the whole slime as plasmoid, no membrane
   	for(int j = 1; j < 51; j++)
 	{
 		for(int i = 1; i < 101; i++) 			
		{
		    if (temp1[j][i] == 2 || temp1[j][i] == 5){
		        temp1[j][i] = 1;
		    }

		}
		
 	}
 	
  // temp1[outerCellj][outerCelli] = 1;
 	
    int bubblei = entryCelli;
    int bubblej = entryCellj;
    int k = 0;

    
    
//sets the path of the bubble
    int bubbleNexti;
    int bubbleNextj;
    bool isOnEdge;
    bool isTrapped;
    bool chosenNextBubble;
    
    //the bubble progresses through the slime by randomly picking new plasmoid cells
    //the bubble cannot travel back along the same path: here these values are temporarily set
    //to the transient 'swap-state' 3. 
    // Upon reaching n, the slime edge (defined by s), or becoming unable to move, the bubble stops 
   do{
       
       
      checkOnEdge(temp1, s, bubblei, bubblej, isOnEdge);
     // cout << "checked edge, edge is " << isOnEdge << endl;
            if(isOnEdge == true){
               //temp1[bubblej][bubblei] = 0;
               // cout << "got to edge" << endl;
                
                break;
            }
      
       
      checkTrapped(temp1, bubblei, bubblej, isTrapped);
     // cout << "checked trapped, is Trapped is " << isTrapped << endl;
            if(isTrapped == true){
               // temp1[bubblej][bubblei] = 0;
                //cout << "got trapped" << endl;
                
                break;
            }
      
      //chooses next cell for the bubble to enter      
      chooseNextBubble(temp1, bubblei, bubblej, bubbleNexti, bubbleNextj, chosenNextBubble);
      
      //adds the previous cell to memorised flow, enters new cell
      temp1[bubbleNextj][bubbleNexti] = 0;
      temp1[bubblej][bubblei] = 3;

     
      k = k+1;
      
      //checking step
      //countSize(temp1);
      
    if(printBubble == 'y'){
     //prints the path of the bubble through the plasmoid, for reference 
      copy(temp1, plasmoid);
      print(plasmoid, simsteps);
      system("sleep 0.05");
      
   }
   
      bubblei = bubbleNexti;
      bubblej = bubbleNextj;
      
   }while(k<n);

  //re-draws the boundaries of the slime according to the new configuration
	for(int j = 1; j < 51; j++)
 	{
 		for(int i = 1; i < 101; i++) 			
		{
		    //if the cell is currently plasmoidal, but borders an empty cell, it becomes a new boundary cell
     	    if ((temp1[j][i] == 1 || temp1[j][i] == 3) && (temp1[j + 1][i] == 0 || temp1[j][i + 1] == 0 || temp1[j - 1][i] == 0 || temp1[j][i - 1] == 0)){
                temp2[j][i] = 2;
		    }
		    
		    else if(temp1[j][i] == 1 || temp1[j][i] == 3){
		        temp2[j][i] = 1;
		        
		    }
		    
		    else if(temp1[j][i] == 4){
		        temp1[j][i] = 4;
		    }
		    
		    else if(temp1[j][i] == 6){
		        temp1[j][i] = 1;
		    }
		    
		     else if(temp1[j][i] == 5){
		        temp1[j][i] = 5;
		    }
		    
		    else
			  temp2[j][i] = 0;				
		}
 	}

  //Copies the completed temp array back to the main array.
  copy(temp2, array);
}

// checks the number of food sources (debugging)
void checkFood(int array[52][102]){
    int foodNum = 0;
 for(int j = 1; j < 51; j++)
   {
    for(int i = 1; i < 101; i++) 			
	{
		    if(array[j][i] == 4)
                {foodNum = foodNum + 1;}
		}
		
 	}
 	cout << "food sources" << foodNum;
}

// check the number of initial 'seeds'
void checkSeeds(int array[52][102]){
    int seedNum = 0;
 for(int j = 1; j < 51; j++)
   {
    for(int i = 1; i < 101; i++) 			
	{
		    if(array[j][i] == 1)
                {seedNum = seedNum + 1;}
		}
		
 	}
 	cout << "number of seed cells " << seedNum;
}

int main()
{

	int genNext[52][102] = {0};
	int backup[52][102] = {0};
	int m;
	int s;
	int food;
	int seedSize;
	char printBubble;
	int n;
	int limit;
	int steps = 0;
	int stepsprev = 0;
	char again;
    char cont;
    char migrate;
    char continu = 'y';
    bool comparison;
    bool repeat = false;
    bool seedSizeChosen = false;
    bool foodChosen = false;
    bool mChosen = false;
	string decoration;

  //Instructions 
	cout << endl << "This program is a C++ implementation of Gunji's cellular automata model for slime moulds" << endl 
       << endl << "The model consists of 2 phases:" << endl
       << endl << "1. Growth: a seed is randomly initialised, and the slime grows for m steps (typically m=8)" << endl
       << endl << "2. Migration phase: the total size of the slime does not increase and instead empty"
       << endl << "cells are absorbed into the slime and transported through the membrane."
       << endl << "The empty cell moves through the slime by changing places with random adjacent cells,"
       << endl << "halting only when the number of adjacent empty cells is greater than or equal to s (typically s=3)"
       << endl << "or when the number of steps the empty cell has made is greater than or equal to n (typically n=6)." 
       << endl << "At this point, the boundaries of the cell are redefined, and the process is repeated"
       << endl << "The inclusion of food sources initiates 'chemotactic' behaviour, in which the slime " 
       << endl << "accepts empty cells preferentially in the direction of food" << endl << endl << endl;
  //Loop to check if user wants to keep simulating.
  do
	{ 	
	    int gen0[52][102] = {0};

    //Loop to determine growth phase.
    
        do
		{ 
      cout << "Growth Phase" <<endl<< "What is the size of the initial seed (~60) ";
		  cin >> seedSize;
		   if (cin.fail())
                 {
                 cout << "incorrect input, please enter a numerical value" << endl;

                 // get rid of failure state
                 cin.clear(); 

                 // discard input
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
		  	else{
		        seedSizeChosen = true;
		  	}
		}while(seedSizeChosen == false);
   
       
       do{
           //user inputs food sources
           cout << "How many food sources? ";
           cin >> food;
            if (cin.fail())
                 {
                 cout << "incorrect input, please enter a numerical value" << endl;

                 // get rid of failure state
                 cin.clear(); 

                 // discard input
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
		  	else{
		        foodChosen = true;
		  	}
       }while(foodChosen == false);
       	
		
    //Clears the screen so the program can start fresh.
    system("clear");
    int i = 0;
      //Picks squares as 'seeds' for the slime.
            
              srand ( time(NULL) );
            
                int rani = rand() %102;
                int ranj = rand() %52;
                int n = 1;
           
            
    //Draws the seeds        
            
        do{
            
            ranj = ranj + 1 - rand() %3;
            rani = rani + 1 - rand() %3;
                
            if (gen0[ranj][rani] == 0 && isgreater((float)rani, 1.0) && isgreater((float)ranj, 1.0) && isless((float)rani, 101.0) && isless((float)ranj, 51.0)){    
				gen0[ranj][rani] = 1;
				n = n + 1;
            }
          }while(n <= seedSize);  
          
          print(gen0, i);
          
    //Picks food sources    
      vector<vector<int> > foodLocator(0);
      	int a = 0;  
        if(food != 0){
         do{
            int ranFoodi = 1 + rand() %100;
            int ranFoodj = 1 + rand() %50;
        
              if(gen0[ranFoodj][ranFoodi] == 1 || gen0[ranFoodj][ranFoodi] == 4){
                        }
             else if (gen0[ranFoodj][ranFoodi] == 0){
                    gen0[ranFoodj][ranFoodi] = 4; //4 is the food square
                    
                    //creates a vector to hold co-ordinate values
                    vector<int> coord;
                    coord.push_back(ranFoodi);
                    coord.push_back(ranFoodj);
                    
                    //writes the location of each food source to a vector
                    foodLocator.push_back(coord);
                    a = a+1;
             }         
         }while(a < food);

                
        }        
          
            //records the stage in the growth    
			//cout << "#################" << endl << "Time = " << i 
			//     << ":" << endl << decoration << endl << endl;
			  copy(gen0, genNext); 
			  copy (genNext, backup);			
		      print (genNext, i); 

	        do{ 
                
                cout <<endl<< "How many steps for the initial growth phase, m (typically 4, must be >0) ";
		        cin >> m;
		        
	        if (cin.fail())
                 {
                 cout << "incorrect input, please enter a numerical value" << endl;

                 // get rid of failure state
                 cin.clear(); 

                 // discard input
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
		  	else{
		        mChosen = true;
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		  	}
	         }while(mChosen == false);
			     
	    do{	

	     cout << "#################" << endl << "Time = " << i  << endl;  
      //Initializes the arrays by copying the gen0 array to the genNext array.

		  copy (genNext, backup);			
		  print (genNext, i);
		  growth (genNext, m);
		  i++;
		  
      //Pauses the system for 1/2 a second in order to give the screen
      //time to refresh.
      system("sleep .5");

        cout << endl;
		}while(i < m); 

    //Label the food zones according to the positions of the slime edges
        foodZones (genNext, food, foodLocator); 
                
    //the phase in which the slime migrates towards food sources
     cout << "Migration Phase" << endl << endl;
     bool printBubbleChosen = false;
     bool nChosen = false;
     bool sChosen = false;
     bool limitChosen = false;
     bool againChosen = false;
     bool continuChosen = false;
     int simsteps = 0;  
       
       do{
          cout << "Choose a value for s (the number of empty neighbouring cells required for an"<<endl <<"empty cell to be rejected from the slime, typically 3)?: ";
		  cin >> s;
		  
		   if (cin.fail())
                 {
                 cout << "incorrect input, please enter a numerical value" << endl;

                 // get rid of failure state
                 cin.clear(); 

                 // discard input
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
		  	else{
		        sChosen = true;
		        //cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		  	}
         }while(sChosen == false);
         
           do{
          cout << "Choose a maximum value for the number of cells a bubble moves before stopping"<<endl <<"(typically 1000)?: ";
		  cin >> n;
		  
		   if (cin.fail())
                 {
                 cout << "incorrect input, please enter a numerical value" << endl;

                 // get rid of failure state
                 cin.clear(); 

                 // discard input
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
		  	else{
		        nChosen = true;
		        //in case user has included decimal, truncates to nearest integer
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		  	}
         }while(nChosen == false); 
         
         do{
          cout << "Pick a limit for the number of cycles"<< endl <<"(typically 1500)?: ";
		  cin >> limit;
		  
		   if (cin.fail())
                 {
                 cout << "incorrect input, please enter a numerical value" << endl;

                 // get rid of failure state
                 cin.clear(); 

                 // discard input
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
		  	else{
		        limitChosen = true;
		        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		  	}
         }while(limitChosen == false); 
         
         do{
        //user decides whether they want to see empty cell migration (for debugging)     
          cout << "Print the path of the bubble through the slime (y/n) ";
		  cin >> printBubble;
		    if(printBubble == 'y' || printBubble == 'n'){
		        printBubbleChosen = true;
		       // cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    }
		    else{
		        cout << "incorrect input, please enter y or n " << endl;
		        //cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		    }
         }while(printBubbleChosen == false); 
         

  do{  
   do {
        simsteps = steps + m + stepsprev;

       if(repeat == true){
      do{
          steps = 0;
          cout << "How many more cycles? "<<endl;
		  cin >> limit;
		  repeat = false;

		   if (cin.fail())
                 {
                 cout << "incorrect input, please enter a numerical value" << endl;

                 // get rid of failure state
                 cin.clear(); 

                 // discard input
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
		  	else{
		        limitChosen = true;
		        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
		  	}
		  	
         }while(limitChosen == false); 

       }
       
       migration (genNext, s, n, food, printBubble, foodLocator, simsteps);
       print (genNext, simsteps);
       system("sleep .05");
       cout << endl;
       
       i++;
       steps++;
        
       }while(steps < limit);

        do
            {
                 //decides whether to continue current simulation
                cout << "Continue simulation? (y/n): ";
	            cin >> continu;
	            
	            if(continu == 'y' || continu == 'n'){
		        continuChosen = true;
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    }
	            else{
		        cout << "incorrect value, please enter y or n " << endl;
		        continuChosen = false;
		        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    }
            }while(continuChosen == false);
    
    repeat = true;
    stepsprev = simsteps - m + 1;
    steps = 0;
    limitChosen = false;

	}while(continu == 'y');

    do
    {
      cout << "Run another simulation? (y/n): ";
	  cin >> again;
	  
	  //decides whether to run another, separate simulation
	  if(again == 'y' || again == 'n'){
		  againChosen = true;
		  cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    }
	  else{
		  cout << "incorrect value, please enter y or n " << endl;
		  //cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    }
	  
	  stepsprev = 0;
	        
    }while(againChosen == false);
    
    continu = 'y';
    repeat = false;
    
	}while(again == 'y');
	
	return 0;
}	
