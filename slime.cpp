//A basic model of amoebic behaviour in physarum polycephalum

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <ctime>

using namespace std;


//This function prints the 50 x 100 part of the array. Spaces represent empty cells,
// + symbols interior cells, * symbols boundary cells
void print(int array[52][102])
{
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



void checkOnEdge(int array[52][102], int s, int bubblei, int bubblej, bool &isOnEdge){
//checks each surrounding square in turn, incrementing t each time one is found to be empty
//if the number of empty cells, t, is greater than or equal to s, the cell is on the edge
    
    cout << "checking edge" << endl;
    
    int t = 0;
    
    //top
    if(array[bubblej + 1][bubblei] == 0)
    {   cout << "top bubble empty" << endl;
        t=t+1;
        
    }
    else
        t=t;
    
    //right
    if(array[bubblej][bubblei + 1] == 0)
       { cout << "right bubble empty" << endl;
        t=t+1;
           
       }
    else
        t=t;    

    //below
    if(array[bubblej - 1][bubblei] == 0)
       { t=t+1;
       cout << "bottom bubble empty" << endl;}
    else
        t=t;    

    //left
    if(array[bubblej][bubblei - 1] == 0)
        {  cout << "left bubble empty" << endl;
            t=t+1;}
    else
        t=t; 
        
    //check

    if(t < s)
       { isOnEdge = 0;
         cout << "t = " << t << "Not on Edge " << isOnEdge << endl;
           
       }
    else   
      { isOnEdge = 1; 
       cout << "t = " << t << " On Edge " << isOnEdge << endl;
          
      }
}


void checkTrapped(int array[52][102], int bubblei, int bubblej, bool &isTrapped){
//checks each surrounding square in turn, incrementing t each time one is found to be empty
//if the number of empty cells, t, is greater than or equal to s, the cell is on the edge
    cout << "checking trapped" << endl;
    
    int t = 0;
    
    cout << "j+1 " << array[bubblej + 1][bubblei] << "   i+1 " << array[bubblej][bubblei + 1] << "   j-1 " << array[bubblej - 1][bubblei] << "   i-1 " << array[bubblej][bubblei - 1] << endl;
    
    //top
    if(array[bubblej + 1][bubblei] != 1  && array[bubblej][bubblei + 1] != 1 && array[bubblej - 1][bubblei] != 1 && array[bubblej][bubblei - 1] != 1)
         { 
         isTrapped = true;
         cout << " trapped " << isTrapped << endl;
             
         }
         
    else   
       { 
        isTrapped = false; 
        cout << "not trapped " << isTrapped << endl;
           
       }

}


void countSize(int array[52][102]){
    //counts the size of the slime
    
    int slimeSize = 0;
 for(int j = 1; j < 51; j++)
   {
    for(int i = 1; i < 101; i++) 			
	{
		    if(array[j][i] == 1 || array[j][i] == 2)
                {slimeSize = slimeSize + 1;}
		}
		
 	}
 	cout << "seed size " << slimeSize;
}


void chooseCell (int array[52][102], int food, int &outerCelli, int &outerCellj, int &entryCelli, int &entryCellj){
  //choose a boundary (type 2) cell to become the point of entry.
  //Randomly selects an adjacent empty cell to be the 'bubble'
  //Initially, just random though intend to add potential for eg chemotaxis.
  
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
      
      //labelMatrix - 
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

    if(array[bubblej + 1][bubblei] != 1  && array[bubblej][bubblei + 1] != 1 && array[bubblej - 1][bubblei] != 1 && array[bubblej][bubblei - 1] !=1)
         { 
         cout << "actually trapped, no choice " << endl;
             
         }
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
     
    
    
    // checkTrapped(array[52][102], bubblei, bubblej, isTrapped);
    // checkOnEdge(temp1, s, bubblei, bubblej, isOnEdge);
    
    }while(chosenNextBubble == false);
     
 }
 

void migration(int array[52][102], int s, int n, int food, char printBubble)
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
  
  chooseCell(array, food, outerCelli, outerCellj, entryCelli, entryCellj);

 	//the bubble enters the slime
 	
 	//test code 
//  	temp1[entryCellj][entryCelli] = 5;
//     temp1[outerCellj][outerCelli] = 6;
//     cout << "entry cell is " << 	temp1[entryCellj][entryCelli] << entryCelli << entryCellj << endl;
//     cout << "outer cell is " << temp1[outerCellj][outerCelli] << outerCelli << outerCellj << endl;
    
//     print(temp1);
    
//     system("sleep 0.2");

 	temp1[entryCellj][entryCelli] = 0;
    temp1[outerCellj][outerCelli] = 2;
    

   //renders the whole slime as plasmoid, no membrane
   	for(int j = 1; j < 51; j++)
 	{
 		for(int i = 1; i < 101; i++) 			
		{
		    if (temp1[j][i] == 2){
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
      
            
       chooseNextBubble(temp1, bubblei, bubblej, bubbleNexti, bubbleNextj, chosenNextBubble);
      
       //cout << "choosing" << endl;
      
      
      temp1[bubbleNextj][bubbleNexti] = 0;
      temp1[bubblej][bubblei] = 3;

     
      k = k+1;
      
               countSize(temp1);
      
    if(printBubble == 'y'){
     //prints the path of the bubble through the plasmoid, for reference 
      copy(temp1, plasmoid);
      print(plasmoid);
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
		    
		    else
			  temp2[j][i] = 0;				
		}
 	}

  //Copies the completed temp array back to the main array.
  copy(temp2, array);
}


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

void foodZones(int array[52][102], int food, vector<vector<int> > foodLocator){
    //stuff goes here
    
 int a = 0;

    
  cout << "number of food sources " << food << endl;
    //create a vector containing every edge element of the slime
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
		
		cout << "number of edge cells " << edgeNum << endl;
    //the location of each food source

      do{
        
        int foodLoci = foodLocator[a][0];
        int foodLocj = foodLocator[a][1];
        cout << endl << "food coord is " << foodLoci << " " << foodLocj << endl;
        
        vector<int> distVector; 
        
        int b = 0;
           do{
               
               int edgei = edgeVector[b][0];
               int edgej = edgeVector[b][1];
               
               cout << "edge coord is " << edgei << " " << edgej << endl;
               
               double dist = sqrt((double)((edgei - foodLoci)*(edgei - foodLoci) + (edgej - foodLocj)*(edgej - foodLocj)));

               cout << "distance  " << dist << endl;
               distVector.push_back (dist);
               b = b+1;
           }while(b < edgeNum);
        
        //scan the vector of distances to obtain the minimum distance co-ordinate for 
        //that food source. Store in vector of minimum distance co-ords, then use to
        //generate the 
        
        
        int x = *min_element(distVector.begin(), distVector.end() );
        cout << "min element is " << x  << endl << endl;
        
        
        a = a+1;
        
  	}while(a < food);
}

int main()
{

	int todo[52][102] = {0};
	int backup[52][102] = {0};
	int m = -1;
	int s = -1;
	int a = 0;
	int food = -1;
	int seedSize = -1;
	char printBubble;
	int n = -1;
	int limit = -1;
	int steps;
	char again;
    char cont;
    char migrate;
    char continu = 'n';
    bool comparison;
    bool repeat = false;
	string decoration;

  //Instructions 
	cout << endl << "This program is a C++ implementation of Gunji's " <<endl
	<< endl << "cellular automata model of slime synthesis" << endl 
       << endl << "The model consists of 2 phases:" << endl
       << endl << "1. Growth: a seed is randomly initialised, and the"
       << endl << "slime grows for m steps (typically m=8)" << endl
       << endl << "2. Migration phase: the total size of the slime does not increase"
       << endl << "and instead empty cells are absorbed into the slime and transported through the membrane."
       << endl << "The empty cell moves through the slime by changing places with random adjacent cells," << endl
       << endl << "halting only when the number of adjacent empty cells is greater than or equal to s (typically s=3)"
       << endl << "or when the number of steps the empty cell has made is greater than or equal to n (typically n=6)." 
       << endl << "At this point, the boundaries of the cell are redefined, and the process is repeated"
       << endl << endl;
  //Loop to check if user wants to keep simulating.
  do
	{ 	
	    int gen0[52][102] = {0};

    //Loop to determine growth phase.
    
        do
		{ 
      cout << "Growth Phase" <<endl<< "What is the size of the initial seed (~60) ";
		  cin >> seedSize;
		}while(seedSize == -1);
   
       
       do{
           cout << "How many food sources?" << endl;
           cin >> food;
       }while(food == -1);
       	
		
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
          
          print(gen0);
          
          //checkSeeds(gen0);
          
    //Picks food sources
      
      vector<vector<int> > foodLocator;
        
        if(food != 0){
         do{
            int ranFoodi = rand() %101;
            int ranFoodj = rand() %51;
        
              if(gen0[ranFoodj][ranFoodi] == 1 || gen0[ranFoodj][ranFoodi] == 4){
                        }
             else if (gen0[ranFoodj][ranFoodi] == 0){
                    gen0[ranFoodj][ranFoodi] = 4; //4 is the food square
                    
                    //creates a vector to hold co-ordinate values
                    vector<int> coord;
                    coord.push_back(ranFoodi);
                    coord.push_back(ranFoodj);
                    
                    
                    ////tests co-ordinate values
                    // cout << "coords " << ranFoodi << " " << ranFoodj << endl; 
                    // cout << "coords " << coord.at( 0 )  << " " << coord.at( 1 ) << endl; 
                    // cout << "coords size " << coord.size() << endl;
                    
                    foodLocator.push_back(coord);
                    
                    // cout << "a is " << a << endl;
                    cout << "vector coords " << foodLocator[a][0] << " " << foodLocator[a][1] << endl;
                    // cout << "vector size " << coord.size() << endl <<endl;
                    a = a+1;
             }         
         }while(a < food);

                
        }        
          
                
			cout << "#################" << endl << "Time = " << i 
			     << ":" << endl << decoration << endl << endl;
			  copy(gen0, todo); 
			  copy(todo, backup);			
		      print(todo); 

	        do{ 
                
                cout <<endl<< "How many steps for the initial growth phase, m (typically 8, must be >0) ";
		        cin >> m;
	            
	         }while(m == -1);
			     
	    do{	

	     cout << "#################" << endl << "Time = " << i ;  
      //Initializes the arrays by copying the gen0 array to the todo array.
    //   if(i == 0){
		  //     copy(gen0, todo); 
    //   }
		  copy(todo, backup);			
		  print(todo);
		  growth(todo, m);
		  i++;
		  
      //Pauses the system for 1/2 a second in order to give the screen
      //time to refresh.
      system("sleep .5");

        cout << endl;
		}while(i < m); 
    //Loop to check for proper inputs.
    
    //Label the food zones according to the positions of the slime edges
        foodZones(todo, food, foodLocator); 
                
    
    
      cout << "Migration Phase" << endl << endl;
       
       do{
          cout << "Choose a value for s (the number of empty neighbouring cells required for an"<<endl <<"empty cell to be rejected from the slime, typically 3)?: ";
		  cin >> s;
         }while(s == -1);
         
           do{
          cout << "Choose a maximum value for the number of cells a bubble moves before stopping"<<endl <<"(typically 20)?: ";
		  cin >> n;
         }while(n == -1); 
         
           do{
          cout << "Pick a limit for the number of cycles"<<endl <<"(typically 300)?: ";
		  cin >> limit;
         }while(limit == -1); 
         
         do{
          cout << "Print the path of the bubble through the slime (y/n) ";
		  cin >> printBubble;
         }while(printBubble !='y' && printBubble !='n'); 

  do{  
   do {

        cout << "#################" << endl << "Time = " << steps + m; 
			     //<< ":" << endl << decoration << endl << endl;
       
       if(repeat == true){
      do{
          steps = 0;
          cout << "How many more cycles? "<<endl;
		  cin >> limit;
		  repeat = false;
         }while(limit == -1); 
       }
       
       migration(todo, s, n, food, printBubble);
       cout << "printing" << endl;
       print(todo);
       system("sleep .2");
       cout << endl;
       
       i++;
       steps++;
        
       }while(steps < limit);

        do
            {
                cout << "Continue simulation? (y/n): ";
	            cin >> continu;
            }while(continu != 'y' && continu != 'n');
    
    repeat = true;
    limit = -1;

	}while(continu == 'y');

    do
    {
      cout << "Run another simulation? (y/n): ";
	  cin >> again;
	        
    }while(again != 'y' && again != 'n');
    

    
	}while(again == 'y');
	

	return 0;
}	
