#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include <cstring>

using namespace std;

const string DADT_FILE = "s.txt";

struct Student {
    int id;         //学号
    char name[50];    //学生姓名
    int grade;      //学生成绩
};

struct FileHeader {
    char magic[4];          // 文件标识符，例如 "STU1"
    int version;            // 版本号
    int recordCount;        // 记录数量
    long long checksum;     // 校验和
};

void saveBinary (const vector<Student> stus){

    //二进制文件处理方法
    //写入
    //1. 打开文件
    ofstream outFile(DADT_FILE,ios::binary | ios::trunc);
    if(!outFile.is_open()) {
        cout << "保存失败：无法打开文件！" << endl;
        return;
    }
    //2. 写入空文件头（占位）
    FileHeader header;
    strcpy(header.magic, "STU1");
    header.version = 1;
    header.recordCount = stus.size();
    header.checksum = 0;
    outFile.write((char*)&header, sizeof(FileHeader));
    //3. 写入学生数据，同时计数并计算校验和
    for (const auto& s:stus){
        outFile.write((char*)&s, sizeof(Student));
        
        // 计算校验和（简单示例：将所有int相加）
        header.checksum += s.id + s.grade;
        for (int i = 0; s.name[i] != '\0' && i < 50; i++) {
            header.checksum += s.name[i];
        }
    }
    //4. 回到文件开头，写入真实的文件头
    outFile.seekp(0);  // 移动到文件开头
    outFile.write((char*)&header, sizeof(FileHeader));
    //5. 关闭文件
    outFile.close();
    cout << "成功保存 " << stus.size() << " 条记录到二进制文件" << endl;
}

vector<Student> loadBinary() {
    vector<Student> stus;
    
    // 1. 打开二进制文件
    ifstream inFile(DADT_FILE, ios::binary);
    if (!inFile.is_open()) {
        cout << "文件不存在或无法打开！" << endl;
        return stus;
    }
    
    // 2. 读取文件头
    FileHeader header;
    inFile.read((char*)&header, sizeof(FileHeader));
    
    // 3. 验证文件标识符
    if (strncmp(header.magic, "STU1", 4) != 0) {
        cout << "文件格式错误！" << endl;
        return stus;
    }
    
    cout << "版本: " << header.version 
         << ", 记录数: " << header.recordCount 
         << ", 校验和: " << header.checksum << endl;
    
    // 4. 读取学生数据
    for (int i = 0; i < header.recordCount; i++) {
        Student s;
        inFile.read((char*)&s, sizeof(Student));
        stus.push_back(s);
    }
    
    // 5. 验证校验和（可选）
    // 可以在这里重新计算校验和并与header.checksum比较
    
    inFile.close();
    cout << "成功读取 " << stus.size() << " 条记录" << endl;
    return stus;
}

void testBinaryFile() {
    // 创建测试数据
    vector<Student> students = {
        {1001, "张三", 85},
        {1002, "李四", 92},
        {1003, "王五", 78}
    };
    
    // 测试保存
    saveBinary(students);
    
    // 测试读取
    vector<Student> loaded = loadBinary();
    
    // 显示读取的数据
    for (const auto& s : loaded) {
        cout << "ID: " << s.id 
             << ", 姓名: " << s.name 
             << ", 成绩: " << s.grade << endl;
    }
}

int main(){
    testBinaryFile();
    return 0;
}
