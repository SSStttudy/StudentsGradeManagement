#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//学生结构体
struct Student {
    int id;         //学号
    string name;    //学生姓名
    int grade;      //学生成绩
};

//全局变量
vector<Student> students; 
const string DATA_FILE = "students.txt";  // 数据文件名

//函数声明
void showMenu();
void addStudent();
void deleteStudent();
void updateStudent();
void displayAllStudents();
void searchStudent();
void saveToFile();
void loadFromFile();
void clearData();



int main(){
    loadFromFile();
    int choice;

    do{
        
        showMenu();
        cout << "请输入您的选择：";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            cout << "修改学生成绩(未完成)" <<endl;
            break;
        case 4:
            displayAllStudents();
            break;
        case 5:
            cout << "查找学生信息(未完成)" <<endl;
            break;
        case 6:
            saveToFile();
            break;
        case 7:
            loadFromFile();
            break;
        case 8:
            cout << "清空当前数据" <<endl;
            break;  
        case 9:
            cout << "退出系统" <<endl; 
            return 0; 
        default:
            cout << "无效选择，请重新输入！" << endl; 
        }
    } while (choice != 9);
    
    return 0;
};

//显示菜单
void showMenu(){
    cout << "=============================" <<endl;
    cout << "学生成绩管理系统" <<endl;
    cout << "1.添加学生信息" <<endl;
    cout << "2.删除学生记录" <<endl;
    cout << "3.修改学生成绩" <<endl;
    cout << "4.显示所有学生" <<endl;
    cout << "5.查找学生信息" <<endl;
    cout << "6.保存数据到文件" <<endl;
    cout << "7.从文件加载数据" <<endl;
    cout << "8.清空当前数据" <<endl;
    cout << "9.退出系统" <<endl;
    cout << "=============================" <<endl;
}

void addStudent()
{
    cout << "添加学生信息" <<endl;
            
    Student newStudent;
    cout << "请输入学生学号：";
    cin >> newStudent.id;
    //检查学号唯一性
    for (int i = 0; i < students.size(); i++){
        if (students[i].id == newStudent.id){
            cout << "学号已存在，返回。" << endl;
            return;
        }
    }
    cout << "请输入学生姓名：";
    cin >> newStudent.name;
    cout << "请输入学生成绩：";
    cin >> newStudent.grade;
    students.push_back(newStudent);
    cout << "学生信息添加成功！" <<endl;
}

void deleteStudent()
{
    cout << "删除学生记录" <<endl;
            
    //根据id删除学生
    int delId;
    cout << "请输入要删除的学生的学号：";
    cin >> delId;
    for (int i = 0; i < students.size(); i++)
    {
        if(students[i].id == delId){
            students.erase(students.begin() + i);
            cout << "学生记录删除成功！" <<endl;
            return;
        }
    }
    cout << "未找的该学号的学生，返回。" <<endl;
    
}

void updateStudent()
{
}

void displayAllStudents()
{
    
    if (students.empty())
    {
        cout << "当前没有学生记录。" << endl;
        return;
    }else{
        cout << "学号\t姓名\t成绩" <<endl;
        for (int i = 0; i < students.size(); i++){
            cout << students[i].id << "\t" << students[i].name << "\t" << students[i].grade << endl;
        }
    }
    return;
}

void searchStudent()
{
}

void saveToFile()
{
    cout << "保存数据到文件" <<endl;
    // 1. 创建文件流对象
    // 2. 打开文件（使用DATA_FILE常量）
    ofstream outFile(DATA_FILE);
    // 3. 检查是否打开成功
    if(!outFile.is_open()) {
        cout << "保存失败：无法打开文件！" << endl;
        return;
    }
    
    // 4. 遍历students，将每个学生的信息写入文件
    for(const auto& stu : students){
        outFile << stu.id << " " << stu.name << " " << stu.grade << endl;
    }
    // 5. 关闭文件
    outFile.close();

    cout << "数据已保存到文件！" << endl;        
}

void loadFromFile()
{
    cout << "从文件加载数据" <<endl;
            
    ifstream inFile(DATA_FILE);

    if(!inFile.is_open()) {
        cout << "保存失败：无法打开文件！" << endl;
        return;
    }

    students.clear();

    Student stu;
    while (inFile >> stu.id >> stu.name >> stu.grade)
    {
        students.push_back(stu);
    }
    
    // 5. 关闭文件
    inFile.close();
    cout << "从文件加载了 " << students.size() << " 条学生记录" << endl;
}

void clearData()
{
    cout << "清空当前数据" <<endl;
            
    students.clear();

    cout << "成功清空" << endl;

}
