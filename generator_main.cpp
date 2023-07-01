#include<ctime>
#include<cstddef>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>

struct DateOfBirth{
  int year{};
  int month{};
  int day{};

  void generateDay();
  
  DateOfBirth(){
    year = 0;
    month = 0;
    day = 0;
  }
  ~DateOfBirth(){
    year = 0;
    month = 0;
    day = 0;
  }

};

struct DomicileInformation{
  std::string city = "";
  std::string street = "";
  int house_number{};

  bool inputCity(const std::string tab);
  bool inputStreet(const std::string tab);

  DomicileInformation(){
    city = "";
    street = "";
    house_number = 0;
  }
  ~DomicileInformation(){
    city = "";
    street = "";
    house_number = 0; 
  }
};

struct PersonalInfo{
  std::string name {};
  std::string surname {};
  DateOfBirth birth {};
  DomicileInformation domicile {};
  std::string phone_number {};

  void generatePhoneNumber();
  bool outputPersonalInfo(const std::string file_name);

  PersonalInfo(){
    name = "";
    surname = "";
    phone_number = "";
  }
  ~PersonalInfo(){
    name = "";
    surname = "";
    phone_number = "";
  }
};

//Rewriting data set from file into table 
bool inputConversion(const std::string file_name, std::string* tab,
		     const int size){
  //Oppening file
  //Checking if file is good
  //Assigning file elements into table elements
  std::ifstream fin(file_name);
  if(!fin.good()){
    std::cerr << "File stream error";
    fin.ignore();
    fin.clear();
    fin.close();
    return false;
  }
  for(int i = 0; i < size; i++){
    if(!(fin >> tab[i])){
      std::cerr << "File stream error";
      fin.ignore();
      fin.clear();
      fin.close();
      return false;
    }
  }
  fin.close();
  return true;
}

//Returning random value from table containing data set
std::string randomValue(const std::string* tab, const int size){
  std::string return_value{};
  int random_value{rand() % size};
  return_value = tab[random_value];
  return return_value;
}

//Generating pseudorandom number from range set by a user 
int generateValue(const int max, const int min = 1){
  int return_value{min + rand() % (max - min + 1)};
  return return_value;
}

//Generating pseudorandom day of birth depending on month of birth
void DateOfBirth::generateDay(){
  if((month < 8 && month%2==1) || (month >= 8 && month%2==0)){
    day = generateValue(31);
  }
  else if((month > 2 && month%2==0) || (month > 8 && month%2==1)){
    day = generateValue(30);
  }
  else{
    //Checking if it is leap-year or not 
    if(year%4==0){
      day = generateValue(29);
    }
    else{
      day = generateValue(28);
    }
  }
}

//Generating phone number digit by digit
void PersonalInfo::generatePhoneNumber(){
  for(size_t i = 0; i < 9; i++){
    phone_number.append(std::to_string(generateValue(9,0)));
  }
}

//Writing out data sets 
bool PersonalInfo::outputPersonalInfo(const std::string file_name){
  //Writing out data sets variable by variable
  //Format: name surname day.month.year city street house_number phone_number
  std::ofstream fout(file_name, std::ios::app);
  if(!fout.good()){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << name)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << ' ' << surname)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << ' ' << birth.day)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << '.' << birth.month)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << '.' << birth.year)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << ' ' << domicile.city)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << ' ' << domicile.street)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << ' ' << domicile.house_number)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  if(!(fout << ' ' << phone_number)){
    std::cerr << "File stream error";
    fout.clear();
    fout.close();
    return false;
  }
  fout << '\n';
  fout.close();
  return true;
}

int main(){
  srand(static_cast<unsigned>(time(0)));

  //Number of records in file
  int size{20};

  std::cout << "How many personal data sets do you want?: ";
  //Number of exemplary personal data sets
  size_t n{};
  std::cin >> n;

  if(n >0){
    PersonalInfo* people = new PersonalInfo [n];     //Table of exemplary
                                                     //personal data
    
    // ###NAMES###
    std::string file_name = "";
    std::cout << "Input file name with set of names: ";
    std::cin >> file_name;
    std::string* tab = new std::string [size];       //Table holding values from
                                                     //read file 
    if(!(inputConversion(file_name, tab, size))){
      std::cerr << "Main error handling";
      return 101;
    }
    for(size_t i = 0; i < n; i++){
      std::string value = randomValue(tab, size);    //Getting random element
      people[i].name = value;                        //Assigning random element
    }
    if(tab){
      delete [] tab;                                 //Clearing table before
    }                                                //assignig new values to it
    
    // ###SURNAMES###
    std::cout << "Input file name with set of surnames: ";
    std::cin >> file_name;
    tab = new std::string [size];
    if(!(inputConversion(file_name, tab, size))){
      std::cerr << "Main error handling";
      return 102;
    }
    for(size_t i = 0; i < n; i++){
      std::string value = randomValue(tab, size);
      people[i].surname = value;
    }
    if(tab){
      delete [] tab;
    }
    
    // ###DATE_OF_BIRTH###
    std::cout << "Set minimal year of birth: ";
    int min_year_of_birth;
    std::cin >> min_year_of_birth;
    std::cout << "Set maximal year of birth: ";
    int max_year_of_birth{};
    std::cin >> max_year_of_birth;
    for(size_t i = 0; i < n; i++){
      people[i].birth.year = generateValue(max_year_of_birth,min_year_of_birth);
      people[i].birth.month = generateValue(12);
      people[i].birth.generateDay();
    }
    
    // ###CITIES###
    std::cout << "Input file name with set of cities: ";
    std::cin >> file_name;
    tab = new std::string [size];
    if(!(inputConversion(file_name, tab, size))){
      std::cerr << "Main error handling";
      return 103;
    }
    for(size_t i = 0; i < n; i++){
      std::string value = randomValue(tab, size);
      people[i].domicile.city = value;
    }
    if(tab){
      delete [] tab;
    }
    
    // ###STREETS###
    std::cout << "Input name of file containing set of streets: ";
    std::cin >> file_name;
    tab = new std::string [size];
    if(!(inputConversion(file_name, tab, size))){
      std::cerr << "Main error handling";
      return 104;
    }
    for(size_t i = 0; i < n; i++){
      std::string value = randomValue(tab, size);
      people[i].domicile.street = value;
    }
    if(tab){
      delete [] tab;
      tab = nullptr;
    }
    
    // ###HOUSE_NUMBER###
    std::cout << "Set maximal house number: ";
    int max_house_number{};
    std::cin >> max_house_number;
    for(size_t  i = 0; i < n; i++){
      people[i].domicile.house_number = generateValue(max_house_number);
    }
    
    // ###PHONE_NUMBER###
    for(size_t i = 0; i < n; i++){
      people[i].generatePhoneNumber();
    }
    
    // ###DATA_OUTPUT###
    std::cout << "Input name of output file: ";
    std::cin >> file_name;
    for(size_t i = 0; i < n; i++){
      if(!(people[i].outputPersonalInfo(file_name))){
	std::cerr << "Main error handling";
	return 100;
      }
    }

    //Clearing table containing exemplary personal data
    delete [] people;
    people = nullptr;
  } 
 
  return 0;
}
