#ifndef FIND_H
#define FIND_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <tuple>

using namespace std;

// Hàm để tách chuỗi theo dấu '#'
vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

string getValueFromFile(const string &filename, const string &id, int position, bool printBeforeFirstHash)
{
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        vector<string> tokens = split(line, '#');
        if (tokens.size() > 0 && tokens[0] == id)
        {
            if (position > 0 && position < tokens.size())
            {
                if (printBeforeFirstHash && tokens.size() > 1)
                {
                    cout << tokens[0] << endl;
                }
                return tokens[position];
            }
            else
            {
                return "Invalid position";
            }
        }
    }
    return "ID not found";
}
// Function to check if any line contains a specified string at a given position
bool containsStringAtPosition(const string &filename, const string &searchString, int position)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    string line;
    while (getline(file, line))
    {
        vector<string> tokens = split(line, '#');
        if (position > 0 && position < tokens.size() && tokens[position] == searchString)
        {
            return true;
        }
    }
    return false;
}
// Hàm thay thế giá trị tại vị trí được chỉ định bởi userID và ghi lại file
bool replaceValueInFile(const string &filename, const string &id, int position, const string &newValue)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Cannot open file" << endl;
        return false;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(file, line))
    {
        vector<string> tokens = split(line, '#');
        if (tokens.size() > 0 && tokens[0] == id)
        {
            if (position > 0 && position < tokens.size())
            {
                tokens[position] = newValue;
                found = true;
            }
            else
            {
                cout << "Invalid position" << endl;
                return false;
            }
        }
        // Ghép lại các tokens thành dòng và thêm vào danh sách các dòng
        ostringstream oss;
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            if (i != 0)
            {
                oss << '#';
            }
            oss << tokens[i];
        }
        lines.push_back(oss.str());
    }
    file.close();

    if (!found)
    {
        cout << "ID not found" << endl;
        return false;
    }

    // Ghi lại các dòng đã chỉnh sửa vào file
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cout << "Cannot open file for writing" << endl;
        return false;
    }

    for (const auto &modifiedLine : lines)
    {
        outFile << modifiedLine << endl;
    }
    outFile.close();

    return true;
}
// Helper function with no arguments left to process
void WriteToFileHelper(std::ostringstream &oss)
{
    // No arguments left to process
}

// Recursive helper function to handle arguments
template <typename T, typename... Args>
void WriteToFileHelper(std::ostringstream &oss, T first, Args... args)
{
    oss << first; // Append the first argument
    // If there are more arguments, add a separator and recurse
    if (sizeof...(args) > 0)
    {
        oss << "#";
        WriteToFileHelper(oss, args...);
    }
}
// Function to check if a line already exists in the file
bool LineExistsInFile(const string &fileName, const string &line)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    string fileLine;
    while (getline(file, fileLine))
    {
        if (fileLine == line)
        {
            return true; // Line already exists
        }
    }
    return false; // Line does not exist
}
// Function to check if a line already exists in the file
bool LineStartsWith(const std::string &line, const std::string &prefix)
{
    return line.find(prefix) == 0;
}

// Function to update or append line in the file
void UpdateOrAppendLine(const std::string &fileName, const std::string &newLine)
{
    std::ifstream fileIn(fileName);
    std::ofstream fileOut(fileName + ".tmp"); // Temp file for writing changes

    if (!fileIn.is_open() || !fileOut.is_open())
    {
        throw std::runtime_error("Unable to open file");
    }

    std::string line;
    bool updated = false;

    while (std::getline(fileIn, line))
    {
        if (LineStartsWith(line, newLine.substr(0, newLine.find('#'))))
        {
            // Replace the line with new content
            fileOut << newLine << '\n';
            updated = true;
        }
        else
        {
            fileOut << line << '\n'; // Copy existing line
        }
    }

    if (!updated)
    {
        // Append new line if not updated
        fileOut << newLine << '\n';
    }

    fileIn.close();
    fileOut.close();

    // Rename temp file to original
    std::remove(fileName.c_str());
    std::rename((fileName + ".tmp").c_str(), fileName.c_str());
}

// Main function to write to file
template <typename... Args>
void WriteFile(const std::string &fileName, Args... args)
{
    std::ostringstream oss;             // String stream to construct the output line
    WriteToFileHelper(oss, args...);    // Call the helper function
    std::string outputLine = oss.str(); // Get the constructed string

    // Check if the line already exists in the file
    if (LineExistsInFile(fileName, outputLine))
    {
        return;
    }

    try
    {
        UpdateOrAppendLine(fileName, outputLine); // Update or append line in file
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Failed to write to file: " + std::string(e.what()));
    }
}

void printFormattedTable(const std::string &filename, const std::vector<std::string> &columnNames)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Không thể mở file: " << filename << std::endl;
        return;
    }

    // Tìm độ dài lớn nhất của các chuỗi trong dữ liệu đầu vào (file và columnNames)
    int maxStringLength = 0;

    // Xử lý từng dòng trong file
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = split(line, '#');
        for (const auto &token : tokens)
        {
            if (token.size() > maxStringLength)
            {
                maxStringLength = token.size();
            }
        }
    }

    // Xử lý từng tên cột trong columnNames
    for (const auto &columnName : columnNames)
    {
        if (columnName.size() > maxStringLength)
        {
            maxStringLength = columnName.size();
        }
    }

    file.close();

    // Độ dài cho các dòng định dạng trong bảng
    int lineLength = maxStringLength + 3;

    // In bảng định dạng
    std::cout << "+" << std::string(lineLength * columnNames.size() + columnNames.size() - 1, '-') << "+" << std::endl;

    // In tiêu đề cột
    std::cout << "|";
    for (const auto &columnName : columnNames)
    {
        std::cout << " " << std::setw(maxStringLength) << std::left << columnName << " |";
    }
    std::cout << std::endl;

    std::cout << "+" << std::string(lineLength * columnNames.size() + columnNames.size() - 1, '-') << "+" << std::endl;

    // In dữ liệu từ file
    file.open(filename); // Mở lại file để đọc từ đầu
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = split(line, '#');
        std::cout << "|";
        for (const auto &token : tokens)
        {
            std::cout << " " << std::setw(maxStringLength) << std::left << token << " |";
        }
        std::cout << std::endl;
    }
    file.close();

    std::cout << "+" << std::string(lineLength * columnNames.size() + columnNames.size() - 1, '-') << "+" << std::endl;
}
void append(string list[], int size, string value)
{
    // Tìm vị trí đầu tiên trong mảng chưa được sử dụng (tức là phần tử có giá trị rỗng)
    int i = 0;
    while (i < size && !list[i].empty())
    {
        i++;
    }

    // Nếu tìm được vị trí chưa được sử dụng, gán giá trị mới vào đó
    if (i < size)
    {
        list[i] = value;
    }
    else
    {
        // Nếu mảng đã đầy, bạn có thể xử lý tùy theo yêu cầu, ví dụ như báo lỗi
        cout << "Mang da day, khong the them phan tu moi!" << endl;
    }
}
string toString(const string arr[], int size)
{
    if (size == 0)
    {
        return ""; // Trả về chuỗi rỗng nếu mảng không có phần tử
    }

    string result = arr[0]; // Bắt đầu với phần tử đầu tiên của mảng

    // Nối các phần tử còn lại của mảng vào chuỗi kết quả, cách nhau bằng dấu phẩy
    for (int i = 1; i < size; i++)
    {
        result += "," + arr[i];
    }

    return result;
}
// string filename = "data.txt";
//     vector<string> columnNames = {"idProduct", "ten san pham", "gia", "so luong con lai", "Kieu", "size", "color", "brand"};

//     // Gọi hàm để in ra bảng với dữ liệu từ file và tên các cột
//     printFormattedTable(filename, columnNames);
#endif
