#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#ifdef _WIN64
#include <windows.h>
#endif

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
int getValidInt(const string& prompt, int minVal, int maxVal); //输入验证：获取有效整数（带范围检查）
string getNonEmptyString(const string& prompt); // 输入验证：获取非空字符串

int main(){

    // 设置控制台为UTF-8编码（Windows专用）
    #ifdef _WIN32
        SetConsoleOutputCP(65001);  // 设置输出编码为UTF-8
        SetConsoleCP(65001);        // 设置输入编码为UTF-8
    #endif

    loadFromFile();
    int choice;

    do{
        
        showMenu();
        choice = getValidInt("请输入您的选择(1-9): ", 1, 9);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            displayAllStudents();
            break;
        case 5:
            searchStudent();
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

        cout << "\n按回车键继续...";
        cin.ignore();

    } while (choice != 9);
    
    return 0;
};

//显示菜单
void showMenu() {
    system("cls"); // Windows清屏，如果是Linux/Mac用 system("clear");
    
    cout << "=========================================" << endl;
    cout << "        学生成绩管理系统 V1.1" << endl;
    cout << "=========================================" << endl;
    cout << "1. 添加学生信息" << endl;
    cout << "2. 删除学生记录" << endl;
    cout << "3. 修改学生成绩" << endl;
    cout << "4. 显示所有学生" << endl;
    cout << "5. 查找学生信息" << endl;
    cout << "6. 保存数据到文件" << endl;
    cout << "7. 从文件加载数据" << endl;
    cout << "8. 清空当前数据" << endl;
    cout << "9. 退出系统" << endl;
    cout << "=========================================" << endl;
}
void addStudent()
{
    cout << "\n=== 添加学生信息 ===" << endl;
            
    Student newStudent;
    
    newStudent.id = getValidInt("请输入学生学号(1-99999): ", 1, 99999);

    //检查学号唯一性
    for (int i = 0; i < students.size(); i++){
        if (students[i].id == newStudent.id){
            cout << "学号已存在，返回。" << endl;
            return;
        }
    }
    // 获取姓名（使用getline读取完整姓名）
    newStudent.name = getNonEmptyString("请输入学生姓名: ");
    
    // 获取成绩（0-100）
    newStudent.grade = getValidInt("请输入学生成绩(0-100): ", 0, 100);
    
    students.push_back(newStudent);
    cout << "学生信息添加成功！" << endl;
}

void deleteStudent()
{
    cout << "\n=== 删除学生记录 ===" << endl;

    if (students.empty()) {
        cout << "当前没有学生记录可删除。" << endl;
        return;
    }
      
    // 显示当前学生列表
    displayAllStudents();

    // 获取要删除的学号
    int delId = getValidInt("\n请输入要删除的学生的学号: ", 1, 99999);
    
    for (int i = 0; i < students.size(); i++){

        char confirm;
        cin >> confirm;
        cin.ignore();
       if (confirm == 'y' || confirm == 'Y') {
            students.erase(students.begin()+i);
            cout << "学生记录删除成功！" << endl;
        } else {
            cout << "已取消删除操作。" << endl;
        }
        return;
       
    }
    
    cout << "未找到学号为 " << delId << " 的学生。" << endl;
    
}

void updateStudent()
{
    cout << "\n=== 修改学生成绩 ===" << endl;
    
    if (students.empty()) {
        cout << "当前没有学生记录。" << endl;
        return;
    }

    // 显示当前学生列表
    displayAllStudents();
    
    // 获取要修改的学号
    int updateId = getValidInt("\n请输入要修改的学生学号: ", 1, 99999);
    
    // 查找学生
    for (auto& stu : students) {
        if (stu.id == updateId) {
            cout << "当前信息 - 姓名: " << stu.name << ", 成绩: " << stu.grade << endl;
            
            // 获取新成绩
            int newGrade = getValidInt("请输入新的成绩(0-100): ", 0, 100);
            
            // 确认修改
            cout << "确定要将 " << stu.name << " 的成绩从 " << stu.grade << " 修改为 " << newGrade << " 吗？(y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore();
            
            if (confirm == 'y' || confirm == 'Y') {
                stu.grade = newGrade;
                cout << "学生成绩修改成功！" << endl;
            } else {
                cout << "已取消修改操作。" << endl;
            }
            return;
        }
    }
    
    cout << "未找到学号为 " << updateId << " 的学生。" << endl;
}


void displayAllStudents() {
    cout << "\n=== 学生信息列表 ===" << endl;
    
    if (students.empty()) {
        cout << "当前没有学生记录。" << endl;
        return;
    }
    
    cout << "学号\t姓名\t成绩" << endl;
    cout << "----\t----\t----" << endl;
    
    int total = 0;
    int highest = -1, lowest = 101;
    
    for (const auto& stu : students) {
        cout << stu.id << "\t" << stu.name << "\t" << stu.grade << endl;
        
        total += stu.grade;
        if (stu.grade > highest) highest = stu.grade;
        if (stu.grade < lowest) lowest = stu.grade;
    }
    
    // 显示统计信息
    cout << "\n=== 统计信息 ===" << endl;
    cout << "学生总数: " << students.size() << " 人" << endl;
    if (!students.empty()) {
        double average = static_cast<double>(total) / students.size();
        cout << "平均成绩: " << average << " 分" << endl;
        cout << "最高成绩: " << highest << " 分" << endl;
        cout << "最低成绩: " << lowest << " 分" << endl;
    }
}

void searchStudent() {
    cout << "\n=== 查找学生信息 ===" << endl;
    
    if (students.empty()) {
        cout << "当前没有学生记录。" << endl;
        return;
    }
    
    cout << "1. 按学号查找" << endl;
    cout << "2. 按姓名查找" << endl;
    int searchType = getValidInt("请选择查找方式(1-2): ", 1, 2);
    
    if (searchType == 1) {
        // 按学号查找
        int searchId = getValidInt("请输入要查找的学号: ", 1, 99999);
        
        for (const auto& stu : students) {
            if (stu.id == searchId) {
                cout << "\n查找结果：" << endl;
                cout << "学号\t姓名\t成绩" << endl;
                cout << stu.id << "\t" << stu.name << "\t" << stu.grade << endl;
                return;
            }
        }
        cout << "❌ 未找到学号为 " << searchId << " 的学生。" << endl;
        
    } else {
        // 按姓名查找
        string searchName = getNonEmptyString("请输入要查找的姓名: ");
        
        bool found = false;
        cout << "\n查找结果：" << endl;
        cout << "学号\t姓名\t成绩" << endl;
        
        for (const auto& stu : students) {
            if (stu.name.find(searchName) != string::npos) {
                cout << stu.id << "\t" << stu.name << "\t" << stu.grade << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "❌ 未找到姓名包含 \"" << searchName << "\" 的学生。" << endl;
        }
    }
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

int getValidInt(const string &prompt, int minVal, int maxVal){
    int value;
    while(true){
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < minVal || value > maxVal) {
            cin.clear(); // 清除错误状态
            cin.ignore(1000, '\n'); // 忽略错误输入
            cout << "输入无效，请输入" << minVal << "到" << maxVal << "之间的整数" << endl;
        } else {
            cin.ignore(); // 清除缓冲区中的换行符
            return value;
        }
    }
}

string getNonEmptyString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        // 去除首尾空格
        size_t start = input.find_first_not_of(" \t\n\r");
        size_t end = input.find_last_not_of(" \t\n\r");
        
        if (start != string::npos && end != string::npos) {
            return input.substr(start, end - start + 1);
        } else {
            cout << "输入不能为空，请重新输入！" << endl;
        }
    }
}
