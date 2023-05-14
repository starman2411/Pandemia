#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string>

bool probability(int percent){
    int a=rand()%100;
    if (a<percent) return(true);
    return(false);
}

string translator(int num){
    int a;
    bool trigger=false;
    trigger=(num < 0);
    if(num != 0){
    string s;

    while(abs(num) > 0){
        a = abs(num) % 10;
        s.insert(s.begin(), 1, char(a + 48));
        num = abs(num) / 10;

    }
    if (trigger) s.insert(s.begin(),1,'-');
    return s;}
    else return "0";
}

string Rtranslator(double R){
    string s;
    int b = int(R);
    int a = int(R * 100) - b * 100;
    s = translator(b);
    s.insert(s.end(), 1, ',');
    return s + translator(a);
}

void communicating_with_user(){
    char ch;
    char sh;
    cout << "Enter the population (>50): " << endl;
        cin >> population;
        while(population < 50) {
            cout << "Please, enter a number greater than 50!" << endl;
            cin >> population;
        }
        cout << "OK!" << endl;
        cout << "Enter the number of days required for recovery (natural): " << endl;
        cin >> users_recovery_time;
        cout << "Enter the infecting distance (natural): " << endl;
        cin >> users_infecting_distance;
        cout << "Enter the probability of infecting (percent): " << endl;
        cin >> users_infecting_prob;
        cout << "Choose if the HUB will be working (Y|N): " << endl;
        cin >> ch;
        if((ch == 'Y')||(ch == 'y'))
            {hubwork = true;
        cout << "Enter the probability of infecting in the HUB (percent):" << endl;
        cin >> users_infecting_prob_H;
        cout << "Enter the number of people in the HUB: " << endl;
        cin >> users_number_of_people_H;
        cout << "Enter the time, the person spends in the HUB: "<< endl;
        cin >> users_time_H;}
        else hubwork == false;
        cout << "Enter the name of the file, where you want to save your data: " << endl;
        cin >> name_of_file;
        cout << "Do you want some atmosphere? (Y|N) (turn on sound)" << endl;
        cin >> sh;
        if((sh == 'Y')||(sh == 'y')) music_flag = true;

}



#endif // FUNCTIONS_H_INCLUDED
