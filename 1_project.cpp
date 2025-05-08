#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
struct data {
  string username, password;
} account;

void Print_To_Me();
void Print_From_Me();
void Reply_Question();
void Delete_Chat();
void Add_Question();
void Active_users();
void open_the_chat();
void Logout();
void Menu();
bool check_username(string isUsernamefound, string isPasswordfound,
                    bool secondline, bool firstline);
void login();
void signup();
void Welcome();

int main() {

  Welcome();
  Menu();

  return 0;
}

bool check_username(string isUsernamefound, string isPasswordfound,
                    bool secondline = false, bool firstline = false) {

  string line;
  ifstream check("C:/Users/hp/OneDrive/Desktop/Project/all user.txt");
  while (getline(check, line)) {
    if (line == isUsernamefound) {
      firstline = true;
      getline(check, line);
      if (line == isPasswordfound)
        secondline = true;
    }
  }
  check.close();
  if (firstline == true && secondline == true)
    return true;
  return false;
}

void Print_To_Me() {
  bool printed = false;
  ifstream to_me("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
  string line;
  cout << endl;
  while (getline(to_me, line)) {
    if (line.find("to: [" + account.username + "]") != string::npos) {
      cout << line << endl;
      printed = true;
      while (getline(to_me, line)) {
        if (line.find("\t\t") != string::npos)
          cout << line << endl;
        else if (line.find("to: [" + account.username + "]") != string::npos)
          cout << line << endl;
        else
          break;
      }
    }
  }
  if (printed == false)
    cout << "\n\033[34mThere Isn't Recieved Messages\n\033[0m\n";
  cout << endl;
  to_me.close();
  Menu();
}
void Print_From_Me() {

  ifstream from_me("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
  string line;
  bool printed = false;
  cout << endl;
  while (getline(from_me, line)) {
    if (line.find("from: [" + account.username + "] to: [") != string::npos) {
      cout << line << endl;
      printed = true;
      while (getline(from_me, line)) {
        if (line.find("\t\t") != string::npos)
          cout << line << endl;
        else if (line.find("from: [" + account.username + "] to: [") !=
                 string::npos)
          cout << line << endl;
        else
          break;
      }
    }
  }
  if (printed == false)
    cout << "\n\033[34mThere Isn't Sent Messages\n\033[0m\n";
  cout << endl;

  from_me.close();
  Menu();
}

void Reply_Question() {
  if (filesystem::file_size(
          "C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt") == 0)
    cout << "\n\033[34mThere Is No Message To Reply on.\033[0m\n\n";
  else {
    string line, Reply, to;
    long long Question_id;

    ifstream file("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt",
                  ios::app);
    cout << endl;
    while (getline(file, line))
      cout << line << endl;
    file.close();

    bool checkusername = false, checkID = false;
    string USER;

    while ((checkusername == false)) {
      cout << "\n\n\nReply To: ";
      cin >> to;
      ifstream check("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
      while (getline(check, USER)) {
        if (USER.find("from: [" + to + "]") != string::npos) {
          checkusername = true;
          break;
        }
      }
      check.close();
    }

    while ((checkID == false)) {

      while (true) {
        cout << "\nQuestion ID: ";
        cin >> Question_id;
        if (cin.fail()) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else
          break;
      }
      ifstream check("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
      while (getline(check, USER)) {
        if (USER.find("message ID[" + to_string(Question_id) + "]:") !=
            string::npos) {
          checkID = true;
          break;
        }
      }
      check.close();
    }
    cout << "\nmessage: ";

    cin.ignore();
    getline(cin, Reply);
    string new_id, prev_line = "";

    string findId;

    set<long long> IDs;

    ifstream your_ID("C:/Users/hp/OneDrive/Desktop/Project/Messages ID.txt");
    while (getline(your_ID, new_id))
      IDs.insert(stoll(new_id));
    your_ID.close();

    long long max_id = -1;
    for (long long i : IDs)
      if ((i <= (Question_id / 1000) * 1000 + 1000) && i >= max_id)
        max_id = i;
    max_id++;
    IDs.insert(max_id);
    ofstream print_id("C:/Users/hp/OneDrive/Desktop/Project/Messages ID.txt");
    for (long long i : IDs)
      print_id << i << endl;
    print_id.close();
    auto it = IDs.end();
    --it;
    bool last_line;
    if (Question_id / 1000 == *it / 1000)
      last_line = true;
    else
      last_line = false;

    findId =
        "message ID[" + to_string((Question_id / 1000) * 1000 + 1001) + "]:";

    vector<string> lines;
    ifstream myfile("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
    while (getline(myfile, line)) {
      if (line.find(findId) != string::npos) {
        lines.pop_back();
        lines.push_back("\t\tfrom: [" + account.username +
                        "]----->\tmessage ID[" + to_string(max_id) +
                        "]: " + Reply);
        lines.push_back(prev_line);
        lines.push_back(line);
      } else {
        prev_line = line;
        lines.push_back(line);
      }
    }
    if (last_line == true)
      lines.push_back("\t\tfrom: [" + account.username + "]-----> message ID[" +
                      to_string(max_id) + "]: " + Reply);
    myfile.close();

    ofstream new_print("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
    for (int i = 0; i < lines.size(); i++)
      new_print << lines[i] << endl;
    new_print.close();
  }
  Menu();
}

void Delete_Chat() {
  if (filesystem::file_size(
          "C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt") == 0)
    cout << "\n\033[34mThe Chat Was Deleted Before.\033[0m\n\n";
  else {
    ofstream chat("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
    chat << "";
    chat.close();

    ofstream ID("C:/Users/hp/OneDrive/Desktop/Project/Messages ID.txt");
    ID << "";
    ID.close();
    cout << "\033[34mThe Chat is Deleted.\033[0m\n";
  }
  Menu();
}

void Add_Question() {
  string question, to, isUsernamefound;
  string str_id, line;
  cout << "\nTo: ";
  cin >> to;
  isUsernamefound = "Username:  " + to;

  while (!check_username(isUsernamefound, "", true)) {
    cout << "Invalid Username, Please Insert Correct one.\n\nTo: ";
    cin >> to;
    isUsernamefound = "Username:  " + to;
  }

  cout << "\nQuestion: ";

  cin.ignore();
  getline(cin, question);
  cout << "\nWould you like to submit it anonymously? "
          "Enter[\033[1m\033[32mY\033[0m/\033[1m\033[32mN\033[0m] ";
  char ch;
  cin >> ch;
  while (!(ch == 'Y' || ch == 'N' || ch == 'y' || ch == 'n')) {
    cout << "\nWould you like to submit it anonymously? "
            "Enter[\033[1m\033[32mY\033[0m/\033[1m\033[32mN\033[0m] ";
    cin >> ch;
  }

  ifstream myfile("C:/Users/hp/OneDrive/Desktop/Project/Messages ID.txt",
                  ios::app);
  if (filesystem::file_size(
          "C:/Users/hp/OneDrive/Desktop/Project/Messages ID.txt") == 0)
    str_id = '1';
  while (getline(myfile, line))
    if (!(line.find(" ") != string::npos))
      str_id = line;
  myfile.close();

  long long id = (((stoll(str_id) / 1000) * 1000) + 1) + 1000;

  ofstream file("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt", ios::app);
  file << "from: [";

  if (ch == 'n' || ch == 'N')
    file << account.username;
  else
    file << "anonymous";

  file << "] to: [" << to << "]\n\t\t-----> message ID[" << id
       << "]: " << question << endl;
  file.close();

  ofstream print_id("C:/Users/hp/OneDrive/Desktop/Project/Messages ID.txt",
                    ios::app);
  print_id << id << endl;
  print_id.close();

  Menu();
}

void Active_users() {
  string username_found = "Username:  ", temp_line;
  set<string> arr;

  ifstream file("C:/Users/hp/OneDrive/Desktop/Project/active user.txt",
                ios::app);
  while (getline(file, temp_line)) {
    if (temp_line.find(username_found) != string::npos) {
      temp_line.erase(0, 11);
      arr.insert(temp_line);
    }
  }
  file.close();
  cout << "The Active Users is: \n";
  for (string i : arr)
    cout << "\t\t     " << "\033[32m" << i << endl;
  cout << "\033[0m" << endl;
  Menu();
}
void open_the_chat() {
  cout << endl;
  if (filesystem::file_size(
          "C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt") == 0)
    cout << "\n\033[34mThere Is No Chat For Now.\033[0m\n\n";
  else {
    ifstream chat("C:/Users/hp/OneDrive/Desktop/Project/Chat Box.txt");
    string line;
    while (getline(chat, line))
      cout << line << endl;
    chat.close();
  }
  cout << endl;
  Menu();
}
void Logout() {
  string username_found = "Username:  " + account.username, temp_line;
  vector<string> arr;

  ifstream file("C:/Users/hp/OneDrive/Desktop/Project/active user.txt",
                ios::app);
  while (getline(file, temp_line)) {
    if (username_found == temp_line) {
      getline(file, temp_line);
      getline(file, temp_line);
      getline(file, temp_line);
    } else
      arr.push_back(temp_line);
  }
  file.close();
  ofstream myfile("C:/Users/hp/OneDrive/Desktop/Project/active user.txt");
  for (int i = 0; i < arr.size(); i++)
    myfile << arr[i] << endl;
  myfile.close();

  cout << "\033[34m\n\nYour account is logged out!, Thank you\033[0m\n\n\n";
}

void Menu() {

  cout << "Menu:"
       << "\n\t\t\033[1m\033[31m1\033[0m: Print Question To Me"
       << "\n\t\t\033[1m\033[31m2\033[0m: Print Question From Me"
       << "\n\t\t\033[1m\033[31m3\033[0m: Reply On Question"
       << "\n\t\t\033[1m\033[31m4\033[0m: Delete Chat"
       << "\n\t\t\033[1m\033[31m5\033[0m: Add Question"
       << "\n\t\t\033[1m\033[31m6\033[0m: Active Users"
       << "\n\t\t\033[1m\033[31m7\033[0m: Open The Chat"
       << "\n\t\t\033[1m\033[31m8\033[0m: Logout"
       << "\n\nPlease Enter Number In Range \033[1m\033[31m1\033[0m - "
          "\033[1m\033[31m8\033[0m : ";

  string choice;
  cin >> choice;
  while (!(choice == "1" || choice == "2" || choice == "3" || choice == "4" ||
           choice == "5" || choice == "6" || choice == "7" || choice == "8")) {
    cout << "\n\nPlease Enter Number In Range \033[1m\033[31m1\033[0m - "
            "\033[1m\033[31m8\033[0m: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> choice;
  }

  if (choice == "1")
    Print_To_Me();
  else if (choice == "2")
    Print_From_Me();
  else if (choice == "3")
    Reply_Question();
  else if (choice == "4")
    Delete_Chat();
  else if (choice == "5")
    Add_Question();
  else if (choice == "6")
    Active_users();
  else if (choice == "7")
    open_the_chat();
  else if (choice == "8")
    Logout();
}

void login() {

  cout << "\nPlease enter your username ----> ";
  cin >> account.username;
  cout << "\nPlease enter your password ----> ";
  cin >> account.password;

  string isUsernamefound = "Username:  " + account.username;
  string isPasswordfound = "Password:  " + account.password;

  if (check_username(isUsernamefound, isPasswordfound) == true)
    cout << "\033[32m\nwelocome! ,you are active now\033[0m\n";
  else {
    cout << "\033[31mInvalid username or password\033[0m\n";
    login();
  }

  ofstream file("C:/Users/hp/OneDrive/Desktop/Project/active user.txt",
                ios::app);
  file << "Username:  " << account.username
       << "\nPassword:  " << account.password << "\n\n\n";
  file.close();
}

void signup() {

  string username, password, DateOfBirth, name;

  string isPasswordfound, isUsernamefound;

  int i = 0;

  cout << "\nWe need informations about you so please Reply our question\n\n";

  cout << "Please enter your first and last name ---->  ";

  cin.ignore();
  getline(cin, name);

  cout << "Please enter your date of birth (dd/mm/yyyy) ----> ";

  cin >> DateOfBirth;

  do {
    if (i++ == 0) {
      cout << "Please enter a uniqe username ----> ";
      cin >> username;
    } else {
      cout << "The username you inserted has already been used\n "
           << "Please enter a uniqe username ----> ";
      cin >> username;
    }

    isUsernamefound = "Username:  " + username;
    isPasswordfound = "Password:  ";
  } while (check_username(isUsernamefound, isPasswordfound, true) == true);

  cout << "Please enter your password ----> ";
  cin >> password;
  cout << "\nwelocome! " << name
       << " ,your new account is completed,please login\n\n";

  ofstream file("C:/Users/hp/OneDrive/Desktop/Project/all user.txt", ios::app);
  file << "\n\nUsername:  " << username << "\nPassword:  " << password
       << "\nName:  " << name << "\nDate of Birth: " << DateOfBirth << "\n";
  file.close();
  login();
}

void Welcome() {

  cout << "\n\nWelcome in our app\n"
       << "MENU:\n\t "
       << "\033[1m\033[31m1\033[0m - "
          "Login\n\t "
       << "\033[1m\033[31m2\033[0m - "
          "sign up\n\n";

  string choice;

  cout << "Please Insert a Number In Range "
       << "\033[1m\033[31m1\033[0m - "
       << " \033[1m\033[31m2\033[0m : ";

  cin >> choice;

  while (choice != "1" && choice != "2") {
    cout << "Please Insert a Number In Range "
         << "\033[1m\033[31m1\033[0m - "
         << " \033[1m\033[31m2\033[0m : ";
    cout << "\033[35m";
    cin >> choice;
    cout << "\033[0m";
  }

  if (choice == "1")
    login();

  else if (choice == "2")
    signup();
}
