  //Picks food sources
      vector<vector<int> > foodLocator(food, vector<int>(2));
        
        if(food != 0){
         do{
            int ranFoodi = rand() %101;
            int ranFoodj = rand() %51;
        
              if(gen0[ranFoodj][ranFoodi] == 1 || gen0[ranFoodj][ranFoodi] == 4){
                        }
             else if (gen0[ranFoodj][ranFoodi] == 0){
                    gen0[ranFoodj][ranFoodi] = 4; //4 is the food square
                    vector<int> coord(ranFoodi, ranFoodj);
                    
                    cout << "coords " << ranFoodi << " " << ranFoodj << endl; 
                    foodLocator.push_back (coord);
                    
                    cout << "vector coords " << foodLocator[a][0] << " " << foodLocator[a][1] << endl;
                    a = a+1;
             }         
         }while(a < food);

                
        }        