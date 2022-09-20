#include "Myclasses.h"
#include <fstream>
using namespace std;

////////////////////
///Constructors////
//////////////////

Student& Student::copyStudent(Student& student){
    this->name=student.getName();
    this->gender=student.getGender();
    this->Numofclass=student.getNumofclass();
    return *this;
}

Pair::Pair(){
    this->boy=NULL; //Sthn arxh h 8esh boy sto zeugari einai adeia.
    this->girl=NULL; //Sthn arxh h 8esh girl sto zeugari einai adeia
    this->boyFirst=true; //Bazw au8aireta pws to boyFirst einai true
    this->nextpair=NULL;
}

Pair::Pair(Student& student,bool flag){
    boyFirst=flag;
    if( student.getGender() == "boy"){
        boy=new Student;
        boy->copyStudent(student);
        girl=NULL;
    }
    else{
        girl=new Student;
        girl->copyStudent(student);
        boy=NULL;
    }
    nextpair=NULL;
}

Class::Class(){
    this->pairs=&Head;
    this->Cstudents=0;
    this->MessyRank=0;
    this->stayedSame=true;
}

School::School(int K,int L,int Tquiet,int Tmessy){
    this->numofclasses=K;
    this->numofstudents=0;
    this->L=L;
    this->Tmessy=Tmessy;
    this->Tquiet=Tquiet;
    this->classes=new Class[numofclasses];

    int i=0; //Epeidh den 3erw posoi einai oi ma8htes tous diabazw enan enan kai tous bazw me th seira se ka8e tmhma
    ifstream myfile; //Dhladh bazw ton prwto ma8hth sto 1o tmhma,ton 2o sto 2o,... ,ton K-osto sto K-osto tmhma
    string name,gender; //Otan ftasw ston (k+1)-osto ton bazw 3ana sto 1o tmhma,ton (k+2)-osto sto 2o,... ,ton 2K-osto sto K-osto tmhma
    Student student; //Stamataw otan den exw na diabasw allous ma8htes
    myfile.open("Students.txt"); //Diabazw tous ma8htes apto arxeio "Students.txt" gia eukolia
    while( (myfile >> name) ){ //Otan teleiwsei to arxeio stamataei h epanalhpsh
        myfile >> gender;
        student.setData(name,gender,i);
        this->numofstudents++;
        classes[i++].addStudent(student);
        if(i == numofclasses) i=0;
    }
    checkClasses(); //Elegxw an yparxoun ta3eis me peritto plh8os ma8htwn kai an uparxoun kanw tis aparaithtes allages
}

///////////////////
///Destructors////
/////////////////

//Eftia3a destructor mono gia thn school,dioti gia kapoio logo otan eftia3a destructor gia thn class kai pair mou bgazw error gia double free

School::~School(){
    if(numofclasses > 1) delete[] classes;
    else delete classes;
}

////////////////////
/////Accessors/////
//////////////////

void Student::print(){cout << "Name : " << this->name << "  ,gender : " << this->gender << " and number of class : " << this->Numofclass+1 << endl;}
string Student::getName(){return name;}
string Student::getGender(){return gender;}
int Student::getNumofclass(){return Numofclass;}

void Pair::print(){
    if(boyFirst == true){
        if(boy != NULL) cout << boy->getName() << " ";
        if(girl !=NULL) cout << girl->getName() << endl;
        else cout << endl;
    }
    else{
        if(girl !=NULL) cout << girl->getName() << " ";
        else cout << "      ";
        if(boy != NULL) cout << boy->getName() << endl;
        else cout << endl;
    }
}
Student* Pair::getBoy(){return boy;}

void Class::print(){
    pairs=&Head;
    while(pairs != NULL){
        pairs->print();
        pairs=pairs->nextpair;
    }
}
int Class::getNumOfPairs(){
    pairs=&Head;
    int num=0;
    while(pairs != NULL){
        num++;
        pairs=pairs->nextpair;
    }
    return num;
}
int Class::getCstudents(){return Cstudents;}
int Class::getMessyRank(){return MessyRank;}
bool Class::getStayedSame(){return stayedSame;}

void School::print(){
    int i;
    for(i=0;i<numofclasses;i++){
        cout << "\nPrinting class number " << i+1 << ":" << endl;
        classes[i].print();
    }
    cout << endl;
}
int School::getL(){return L;}
Class School::getClass(int i){return classes[i];}
int School::getTmessy(){return Tmessy;}
int School::getTquiet(){return Tquiet;}

////////////////////
///Mutatators//////
//////////////////

void Student::setData(string name,string gender,int numofclass){
    this->name=name;
    this->gender=gender;
    this->demonstudent=false;
    this->Numofclass=numofclass;
}

//H synarthsh Class::addStudent pros8etei sthn akolou8ia ths swsths ta3hs enan neo ma8hth
//Prwta elegxei an o ma8hths mporei na mpei sto 1o zeugari ths akolou8ias,meta sto 2o,... mexri na bre8ei h katallhlh 8esh
//Katallhlh 8esh enos ma8hth einai na einai zeugari me allon ma8hth tou anti8etou fulou kai na xei mprosta kai pisw ma8htes tou anti8etou fulou
//An den uparxei katallhlh 8esh dhmiourgeitai ena neo zeugari kai o ma8hths einai arxika monos tou sto zeugari meri na proste8ei deyteros tou anti8etou fulou

void Class::addStudent(Student& student){ //H synarthsh auth topo8etei enan neo ma8hth sth swsth 8esh sthn akolou8ia tou tmhmatos tou
    pairs=&Head;
    if( student.getGender() == "boy" && pairs->boy == NULL ){
        pairs->boy=new Student;
        pairs->boy->copyStudent(student);
    }
    else if(student.getGender() == "girl" && pairs->girl == NULL){
        pairs->girl=new Student;
        pairs->girl->copyStudent(student);
    }
    else pairs->nextpair=pairs->addStudent(pairs->nextpair,student,pairs->boyFirst);
    Cstudents++;
}

void School::checkClasses(){ //Synarthsh pou dhmiourgei,an mporei, zeugaria meta3u twn ma8htwn pou briskontai monoi tous sto zeugari se ka8e ta3h
    int i,j;
    for(i=0;i<numofclasses;i++){
        if(classes[i].getCstudents()%2 == 0) continue; //An h ta3h exei zugo plh8os ma8htwn den kanw tipota
        for(j=i+1;j<numofclasses;j++){
            if(classes[j].getCstudents()%2 != 0 && classes[i].fusePair(classes[j],i) == true) break;
        }
    }
}

bool Class::fusePair(Class& frontclass,int numofclass1){
    this->pairs=&(this->Head); //Arxika briskw to teleutaio zeugari ths akolou8ias ths 1hs ta3hs
    while(this->pairs->nextpair != NULL) this->pairs=this->pairs->nextpair;
    frontclass.pairs=&(frontclass.Head); //Meta briskw to teleutaio zeugari ths akolou8ias ths 2hs ta3hs
    Pair* secondtolast; //Edw krataw to proteleutaio zeugaris ths akolou8ias ths 2hs ta3hs
    while(frontclass.pairs->nextpair != NULL){
        secondtolast=frontclass.pairs;
        frontclass.pairs=frontclass.pairs->nextpair;
    }
    bool flag=this->pairs->fusePairs(frontclass.pairs,numofclass1); //Ennwnw ta duo zeugaria se ena an ginete
    if(flag == true){
        this->Cstudents++; //Ama egine h enwsh au3anw ton ari8mo twn ma8htwn sauthn thn ta3h kata 1
        frontclass.dicreaseCstudents();
        secondtolast->nextpair=NULL; //Diagrafw to teleutaio zeugari ths 2hs akolou8ias kai etsi bazw to prwtoleutaio na deixnei se NULL gia epomeno,afou to kanw pleon teleutaio
    }
    return flag; //Telos epistrefw true ama egine h enwsh kai false an den egine
}

void Class::dicreaseCstudents(){Cstudents--;}

//H synarthsh Pair::addStudent ektelei anadromika thn leitourgeia ths Class::addStudent gia ka8e zeugari ths akolou8ias mexri na bre8ei h swsth 8esh gia na baloume ton neo ma8hth

Pair* Pair::addStudent(Pair* pair,Student& student,bool flag){
    if(pair != NULL){ //H synarthsh me dedomeno oti ta agoria exoun mprosta kai pisw tous koritsia kai "vice versa" topo8etei ena koritsi dipla sto prwto agori pou einai mono tou kai ena agori sto prwto koritsi pou einai mono tou
        if( student.getGender() == "boy" && pair->boy == NULL ){//An ola ta koritsia kai agoria briskontai se zeugari,tote dhmiourgei ena neo zeugari topo8etwntas mono tou to koritsi h to agori antistoixa
            pair->boy=new Student;
            pair->boy->copyStudent(student);
        }
        else if(student.getGender() == "girl" && pair->girl == NULL){
            pair->girl=new Student;
            pair->girl->copyStudent(student);
        }
        else pair->nextpair=pair->addStudent(pair->nextpair,student,pair->boyFirst);
    }
    else pair=new Pair(student,!flag);
    return pair;
}

bool Pair::fusePairs(Pair* secondpair,int numofclass1){
    if(secondpair->getBoy() == NULL && this->boy != NULL){ //Ama to prwto zeugari exei agori kai to deutero koritsi enwse ta zeugaria
        this->girl=new Student(*(secondpair->girl));
        this->girl->changeNumofClass(numofclass1); //allazw ton ari8mo ta3hs tou paidiou,afou ton allazw tmhma
        delete secondpair;
        return true;
    }
    else if(secondpair->getBoy() != NULL && this->boy == NULL){ //Ama to prwto zeugari exei koritsi kai to deutero agori enwse ta zeugaria
        this->boy=new Student(*(secondpair->boy));
        this->boy->changeNumofClass(numofclass1); //allazw ton ari8mo ta3hs tou paidiou,afou ton allazw tmhma
        delete secondpair;
        return true;
    }
    return false; //Alliws mhn enwseis. Se ka8e periptwsh epestrepse an egine h enwsh(true) h an den egine(false)
}

void School::makeClassQuiet(int index){
    if(classes[index].getNumOfPairs() == 1) classes[index].outOfClassPairResolution(classes,index,numofclasses); //An exw mono 1 zeugari sthn akolou8ia anagkastika allazw tous ataktous ma8htes tmhma
    classes[index].singleMessyKid(); //Arxika antimeta8etw tous memonwmenous ma8htes pou kanoun ata3ies
    int numofmessypairs=classes[index].messyPairs();
    if(numofmessypairs == 0) return; //An den uparxoun atakta zeugaria epistrefw
    else if(numofmessypairs <= 2) classes[index].inClassPairResolution(); //An exw 1 h 2 atakta zeugaria antimeta8etw tous ma8htes me ma8htes tou idiou tmhmatos
    else classes[index].outOfClassPairResolution(classes,index,numofclasses); //Alliws antimeta8etw me ma8htes enos allou tmhmatos
}

void School::selectDemonStudents(){
    int k,z,j,i=rand()%numofstudents; //Epilegw tuxaio plh8os ma8htwn na kanoun ata3ies
    int indexclass,sumofstudents;
    if(i == 0) cout << "All students are quiet this time!" << endl; //Ama o ari8mos ma8htwn pou 8a ginoun ataktoi enai 0 emanizw katallhlo mhnuma
    else cout << "\nThe following students are messy\n\n";
    Student* studentz=new Student;
    for(j=0;j<i;j++){
        z=rand()%numofstudents;//Epilegw enan tuxaio ma8hth na kanei ata3ia
        z++; //To z 8elw na pairnei times apo 1 mexri Cstudents kai oxi apo 0 mexri Cstudents-1 gia eukolia ulopoihshs
        sumofstudents=0;
        for(indexclass=0;indexclass<numofclasses;indexclass++){//Arxika psaxnw na brw se poio tmhma anoikei o ma8hths z me ton e3hs tropo :
            sumofstudents+=classes[indexclass].getCstudents();//Estw pws to prwto tmhma exei X ma8htes.An z <= X ,tote o ma8hths brisketai sto prwto tmhma
            if(z <= sumofstudents) break;                    // An omws z > X kai Y oi ma8htes tou 2ou tmhmatos elegxw an z <= X+Y.An nai o ma8hths anoikei sto 2o tmhma alliws kanw to idio gia to epomeno tmhma mexri na bre8ei to swsto(dld an K oi ma8htes tou 3ou tmhmatos elegxw an z <= X+Y+K,ktl)
        }
        sumofstudents-=classes[indexclass].getCstudents();//Exontas brei to tmhma sto opoio anoikei o ma8hths 8elw na brw se poia 8esh brisketai sthn akolou8ia tou tmhmatos tou.Px an exw 2 tmhmata me 10 ma8htes to ka8ena kai psaxnw ton ma8hth 17,arkei na pw pws o ma8hths 17 brisketai sto tmhma 2 kai sth 8esh 7 ths akolou8ias tou 2ou tmhmatos.
        z-=sumofstudents;
        studentz=classes[indexclass].getStudentz(z-1); //Antigrafw ton ma8hth z sthn metablhth studentz me th xrhsh ths synarthshs copystudent
        if(studentz->isDemon() == false){ //Ektupwnw mono tous ma8htes pou den exoun hdh kanei ata3ia
            classes[studentz->getNumofclass()].changeStayedSame(false); //Shmeiwnw pws h akolou8ia tou ma8hth pou epilex8hke alla3e
            studentz->print();
            studentz->turnDemon(true);
        }
    }
}

void School::reset(){
    int i,z;
    Student* studentz=new Student;
    for(i=0;i<numofclasses;i++){ //Epanaferw olous tous ma8htes se katastash hremias (oxi ata3ias)
        classes[i].changeStayedSame(true);
        for(z=1;z<classes[i].getCstudents();z++){
            studentz=classes[i].getStudentz(z);
            studentz->turnDemon(false);
        }
    }
}
int School::getNumocclasses(){return numofclasses;}

Student* Class::getStudentz(int z){ //Euresh ma8hth z sthn akolou8ia enos tmhmatos
    pairs=&Head;
    for(int i=1;i<=z/2;i++) pairs=pairs->nextpair; //O ma8hths z 8a brisketai sto zeugari me ari8mo z/2.Px an z=5,tote o 5os ma8hths ths akolou8ias brisketai sto zeugari noumero 5/2=2.(8ewroume pws to prwto zeugari,dhladh to Head, einai to zeugari 0,to epomeno to 1,ktl)
    if(z%2 == 0 && pairs->boyFirst == true) return pairs->boy; //An to z einai zygos 8elw ton ma8hth pou brisketai aristera.Giauto elegxw an exw aristera agori h koritsi gia na epistrepsw ton swsto ma8hth
    else if(z%2 == 0 && pairs->boyFirst == false) return pairs->girl;
    else if(z%2 == 1 && pairs->boyFirst == true) return pairs->girl; //An to z einai peritto 8elw ton ma8hth pou brisketai de3ia,ara kanw paromoious elegxous
    else return pairs->boy;
}

int Class::messyPairs(){ //Epistrefw ton ari8mo twn zeugariwn pou einai atakta(oxi memonwmena paidia)
    int num=0;
    pairs=&Head;
    while(pairs != NULL){
        if(pairs->boy->isDemon() == true && pairs->girl->isDemon() == true ) num++;
        pairs=pairs->nextpair;
    }
    return num;
}

void Class::outOfClassPairResolution(Class* classes,int index,int Cclasses){ //Antimeta8esh ma8htwn ataktwn ma8htwn me ma8htes apo alla tmhmata
    classes[index].pairs=&(classes[index].Head);
    if(classes[index].pairs->nextpair == NULL){ //An exw mono ena zeugari sthn akolou8ia kai enan atakto ma8hth prepei na ton alla3w tmhma
        if( classes[index].pairs->boy->isDemon() == true){
            classes[index].MessyRank+=2;
            if(index+1 < Cclasses ) classes[index].pairs->boy=switchClass(classes,classes[index].pairs->boy,index+1); //Au8aireta epilegw na alla3w tmhma to agori kai na ton paw sto epomeno tmhma
            else classes[index].pairs->boy=switchClass(classes,classes[index].pairs->boy,0); //An eimai sto teleutaio tmhma tote to epomeno tmhma einai to prwto
        }
        else if( classes[index].pairs->girl->isDemon() == true){
            classes[index].MessyRank+=2;
            if(index+1 < Cclasses ) classes[index].pairs->girl=switchClass(classes,classes[index].pairs->girl,index+1); //Au8aireta epilegw na alla3w tmhma to agori kai na ton paw sto epomeno tmhma
            else classes[index].pairs->girl=switchClass(classes,classes[index].pairs->girl,0); //An eimai sto teleutaio tmhma tote to epomeno tmhma einai to prwto
        }
        return;
    }
    classes[index].pairs=&(classes[index].Head);
    while(classes[index].pairs != NULL){
        if(classes[index].pairs->boy->isDemon() == true && classes[index].pairs->girl->isDemon() == true ){
            classes[index].MessyRank+=2;
            if(index+1 < Cclasses ) classes[index].pairs->boy=switchClass(classes,classes[index].pairs->boy,index+1); //Au8aireta epilegw na alla3w tmhma to agori kai na ton paw sto epomeno tmhma
            else classes[index].pairs->boy=switchClass(classes,classes[index].pairs->boy,0); //An eimai sto teleutaio tmhma tote to epomeno tmhma einai to prwto
        }
        classes[index].pairs=classes[index].pairs->nextpair;
    }
}

Student* Class::switchClass(Class* classes,Student* student,int index){
    Student temp=*student;
    classes[index].pairs=&(classes[index].Head);
    while( classes[index].pairs != NULL ){
        if(classes[index].pairs->boy != NULL && student->getGender() == "boy"){ //Ama o ataktos ma8hths einai agori to antimeta8etw me to prwto agori pou briskw sto tmhma
            *student=*(classes[index].pairs->boy);
            *(classes[index].pairs->boy)=temp;
            student->turnDemon(false); //Efoson tous antimeta8esa ginontai hsuxoi
            classes[index].pairs->boy->turnDemon(false);
            break;
        }
        else if(classes[index].pairs->girl != NULL && student->getGender() == "girl"){ //Ama o ataktos ma8hths einai koritsi thn antimeta8etw me to prwto koritsi pou briskw sto tmhma
            *student=*(classes[index].pairs->girl);
            *(classes[index].pairs->girl)=temp;
            student->turnDemon(false); //Efoson tis antimeta8esa ginontai hsuxoi
            classes[index].pairs->girl->turnDemon(false); 
            break;
        }
        classes[index].pairs=classes[index].pairs->nextpair;
    }
    classes[index].changeStayedSame(false); //Shmeiwnw pws epireasthke h akolou8ia tou epomenou tmhmatos
    return student;
}

void Class::inClassPairResolution(){ //Sth synarthsh auth 3erw pws sthn ta3h uparxoun 1 h 2 zeugaria pou einai kai oi 2 ma8htes ataktoi,etsi tous antimeta8etw me allous ma8htes tou idiou tmhmatos
    pairs=&Head;
    while(pairs != NULL){
        if(pairs->boy->isDemon() == true && pairs->girl->isDemon() == true ){
            MessyRank++;
            switchStudents(pairs->boy);
        }
        pairs=pairs->nextpair;
    }
}

void Class::singleMessyKid(){ //Anitmeta8esh memonwmenwn ataktwn ma8htwn
    pairs=&Head;
    while(pairs != NULL){
        if(pairs->boy != NULL && pairs->boy->isDemon() == true && pairs->girl != NULL && pairs->girl->isDemon() == false){ //An enas ma8hths apo ena zeugari kanei fasaria apla ton antimeta8etw menan allon tou idiou fulou kai tmhmatos
            this->switchStudents(pairs->boy);
        }
        else if(pairs->boy != NULL && pairs->boy->isDemon() == false && pairs->girl != NULL && pairs->girl->isDemon() == true){
            this->switchStudents(pairs->girl);
        }
        pairs=pairs->nextpair;
    }
}

void Class::switchStudents(Student* studentz){
    pairs=&Head;
    if(pairs->nextpair == NULL) return;//Ama h akolou8ia apoteleitai apo ena zeugos mono prepei anagkastika na ala3w tous ma8htes tmhma
    Student temp=*studentz; //Arxikopoiw thn proswrinh metablhth me thn student
    while(pairs != NULL){
        if(pairs->boy != NULL && studentz->getGender() == "boy" && studentz != pairs->boy){ //Ama o ataktos ma8hths einai agori to antimeta8etw me to prwto agori pou briskw sto tmhma
            *studentz=*(pairs->boy);
            *(pairs->boy)=temp;
            studentz->turnDemon(false); //Efoson tous antimeta8esa ginontai hsuxoi
            pairs->boy->turnDemon(false);
            break;
        }
        else if(pairs->girl != NULL && studentz->getGender() == "girl" && studentz != pairs->girl){ //Ama o ataktos ma8hths einai koritsi thn antimeta8etw me to prwto koritsi pou briskw sto tmhma
            *studentz=*(pairs->girl);
            *(pairs->girl)=temp;
            studentz->turnDemon(false); //Efoson tis antimeta8esa ginontai hsuxoi
            pairs->girl->turnDemon(false); 
            break;
        }
        pairs=pairs->nextpair;
    }
    this->MessyRank++;
}
void Class::increaseMessyrank(){MessyRank++;}
void Class::changeStayedSame(bool flag){stayedSame=flag;}

bool Student::isDemon(){return demonstudent;}
void Student::turnDemon(bool flag){demonstudent=flag;}
void Student::changeNumofClass(int newnum){Numofclass=newnum;}