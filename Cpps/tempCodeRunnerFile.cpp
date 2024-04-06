
Weapon* View::FightView::ChooseWeapon(vector<pair<Weapon*,int>> Weapons){
    vector<string> options;
    for(pair<Weapon*,int> x : Weapons){
        if(x.second > 1){
            options.push_back(x.first->getShortStat() + " x" + to_string(x.second) +"\n");
        }else{
            options.push_back(x.first->getShortStat() + "\n");
        }
    }
    options.push_back("Back");
    
    int option=0;
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option%vecSize){
                cout << green << options[i] << reset;
            }else{
                cout << options[i];
            }
        }
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    if(option % vecSize == vecSize-1)
        return nullptr;
        
    return Weapons[option % vecSize].first;
}

int View::FightView::PlayerMenu(){
    // 1. weapons   2.consumables  3.show enemies  4.endround
    int option = 0;
    vector<string> options = {"Weapons","Consumables","show enemies","End Round"};
    
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option%vec