#include<ctime>
#include<cstddef>
#include<cstdlib>
#include<fstream>
#include<iostream>

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

  bool inputName(const std::string tab);
  bool inputSurname(const std::string tab);
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

bool inputConversion(const std::string file_name, std::string* tab,
		     const int size){
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

std::string randomValue(const std::string* tab, const int size){
  std::string return_value{};
  int random_value{rand() % size};
  return_value = tab[random_value];
  return return_value;
}

int generateValue(const int max, const int min = 1){
  int return_value{min + rand() % (max - min + 1)};
  return return_value;
}

int main(){
  srand(static_cast<unsigned>(time(0)));

  int size{20};
  
  std::cout << "How many personal data sets do you want?: ";
  size_t n{};
  std::cin >> n;
  PersonalInfo* people = new PersonalInfo [n];
  
  std::string file_name = "";
  std::cout << "Input file name with set of names: ";
  std::cin >> file_name;
  std::string* tab = new std::string [size];
  inputConversion(file_name, tab, size);
  for(size_t i = 0; i < n; i++){
    std::string value = randomValue(tab, size);
    people[i].name = value;
  }
  if(tab){
    delete [] tab;
  }

  std::cout << "Input file name with set of surnames: ";
  std::cin >> file_name;
  tab = new std::string [size];
  inputConversion(file_name, tab, size);
  for(size_t i = 0; i < n; i++){
    std::string value = randomValue(tab, size);
    people[i].surname = value;
  }
  if(tab){
    delete [] tab;
  }
  
  std::cout << "Set minimal year of birth: ";
  int min_year_of_birth;
  std::cin >> min_year_of_birth;
  std::cout << "Set maximal year of birth: ";
  int max_year_of_birth{};
  std::cin >> max_year_of_birth;
  for(size_t i = 0; i < n; i++){
    people[i].birth.year = generateValue(max_year_of_birth, min_year_of_birth);
    people[i].birth.month = generateValue(12);
    //people[i].birth.generateDay();
  }

  delete [] people;
  
  /*
  std::cout << "Input file name with set of cities";
  std::cin >> file_name;
  tab = new std::string [size];
  inputConversion(file_name, tab, size);
  for(size_t i = 0; i < n; i++){
    std::string value = randomValue(tab);
    people[i].domicile.inputCity(value);
  }
  if(tab){
    delete tab;
  }

  std::cout << "Input name of file containing set of streets";
  std::cin >> file_name;
  tab = new std::string [size];
  inputConversion(file_name, tab, size);
  for(size_t i = 0; i < n; i++){
    std::string value = randomValue(tab);
    people[i].domicile.inputStreet(value);
  }
  if(tab){
    delete tab;
    tab = nullptr;
  }

  std::cout << "Set maximal house number";
  size_t max_house_number{};
  std::cin >> max_house_number;
  for(size_t  i = 0; i < n; i++){
    people[i].domicile.house_number = generateValue(max_house_number);
  }

  for(size_t i = 0; i < n; i++){
    people[i].generatePhoneNumber();
  }
  */
  
  return 0;
}
