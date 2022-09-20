#include "Myclasses.h"
using namespace std;

int main(int argv,char* argc[]){
    srand((unsigned)time(0)); //Xrhsimopoiw thn time gia na exw ka8e fora diaforetikh timh.
    School myschool(atoi(argc[1]),atoi(argc[2]),atoi(argc[3]),atoi(argc[4]));
    cout << "Initial pairs are :" << endl;
    myschool.print();
    int i,j; 
    for(i=0;i<myschool.getL();i++){
        cout << "Selection number " << i+1 << endl;
        myschool.selectDemonStudents(); //Epilegei ma8htes pou 8a kanoun ata3ies
        cout << endl;
        for(j=0;j<myschool.getNumocclasses();j++) myschool.makeClassQuiet(j);
        for(j=0;j<myschool.getNumocclasses();j++){
            if(myschool.getClass(j).getStayedSame() == false) cout << "Class " << j+1 << " has been afected!" << endl;
        }
        myschool.reset();
        cout << "End of selection number " << i+1 << endl << endl;
    }
    cout << "Final pairs are :" <<endl;
    myschool.print();

    Class temp;
    for(j=0;j<myschool.getNumocclasses();j++){
        cout << "Class number " << j+1 << " deserves the following statement :\t";
        temp=myschool.getClass(j);
        if(temp.getMessyRank() < myschool.getTquiet()) cout << "What a quiet class!" << endl;
        else if(temp.getMessyRank() > myschool.getTmessy()) cout << "What a mess!" << endl;
        else cout << "Please be quiet!" << endl;
    }

    return 0;
}