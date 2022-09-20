#include <iostream>
#include <string>
#include <ctime>

class Student{
    std::string name;
    std::string gender;
    bool demonstudent; //An einai true o ma8hths einai ataktos alliws einai hsuxos.
    int Numofclass;
public:
    Student& copyStudent(Student& );
    void changeNumofClass(int );
    void setData(std::string ,std::string ,int );
    void print();
    void turnDemon(bool );
    bool isDemon();
    std::string getGender();
    std::string getName();
    int getNumofclass();
};

struct Pair{
    Student* boy;
    Student* girl;
    bool boyFirst; //Deixnei an prwta einai to agori h to koritsi
    Pair* nextpair;
public:
    Pair();
    Pair(Student& ,bool );
    Pair* addStudent(Pair* ,Student& ,bool );
    bool fusePairs(Pair* ,int );
    void print();
    Student* getBoy();
};

class Class{
    Pair* pairs; //Akolou8ia zeugariwn me anaparastash se sundedemenh lista
    Pair Head; //H arxh ths akolou8ias
    bool stayedSame; //Deixnei an se ka8e epanalhpsh ata3ias eginan allages sthn akolou8ia tou tmhmatos
    int Cstudents; //Plh8os ma8htwn
    int MessyRank; //Ba8mos ata3ias
public:
    Class();
    Student* getStudentz(int );
    Student* switchClass(Class* ,Student* ,int );
    int getCstudents();
    int getMessyRank();
    int messyPairs();
    int getNumOfPairs();
    bool fusePair(Class& ,int );
    bool getStayedSame();
    void changeStayedSame(bool );
    void singleMessyKid();
    void inClassPairResolution();
    void outOfClassPairResolution(Class* ,int ,int );
    void switchStudents(Student* );
    void dicreaseCstudents();
    void print();
    void addStudent(Student& );
    void increaseMessyrank();
};

class School{
    Class* classes; //Pinakas me ola ta tmhmata
    int numofstudents;
    int numofclasses; //Ari8mos tmhmatwn
    int Tquiet;
    int Tmessy;
    int L;
public:
    School(int ,int ,int ,int );
    ~School();
    void makeClassQuiet(int );
    void reset();
    void selectDemonStudents();
    void checkClasses();
    void print();
    int getTmessy();
    int getTquiet();
    Class getClass(int );
    int getL();
    int getNumocclasses();
};