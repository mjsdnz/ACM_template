// Use C++17
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
namespace fs = std::filesystem;

bool is_hidden_file(const fs::path &path) {
    // 检查路径中的任何组件是否以.开头（除了当前目录.）
    bool first = true;
    for (const auto &component : path) {
        std::string comp_str = component.string();
        // 跳过当前目录.
        if (first && (comp_str == "." || comp_str == "..")) {
            first = false;
            continue;
        }
        if (!comp_str.empty() && comp_str[0] == '.') {
            return true;
        }
        first = false;
    }
    return false;
}

std::vector<std::string> get_files(std::string path) {
    std::vector<std::string> ans;
    for (const auto &entry : fs::recursive_directory_iterator(path)) {
        // 跳过以.开头的隐藏文件或目录
        if (is_hidden_file(entry.path())) {
            continue;
        }

        // 跳过headers目录中的文件
        std::string filepath = entry.path().string();
        if (filepath.find("headers") != std::string::npos) {
            continue;
        }
        if (filepath.find("files_output") != std::string::npos) {
            continue;
        }
        if (filepath.find(".cpp") == std::string::npos) {
            continue;
        }

        ans.push_back(entry.path());
    }
    return ans;
}

int main() {
    auto files = get_files("..");
    std::ofstream ofile("../output.txt");
    for (std::string filename : files) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filename << std::endl;
            return 1;
        }

        ofile << "\n----------------------------------------\n"
              << filename << "\n\n";
        std::string line;
        while (std::getline(file, line)) {
            ofile << line << std::endl;
        }

        file.close();
    }
    ofile.close();
}
