#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>  // typeidを使うために必要

/// <summary>
/// 型が一致しているかどうかを判定する
/// </summary>
/// <typeparam name="T">調べる変数</typeparam>
/// <typeparam name="U">型</typeparam>
/// <returns></returns>
template <typename T, typename U>
bool IsSameType(const U& value) 
{
    // typeidを使って型を調べる
    return std::is_same<T, U>::value;
}

template <typename T>
void Create(const std::string& filename, const std::vector<T>& dataList)
{
    // バイナリモードでファイルを開く
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);

    if (!outFile)
    {
        std::cerr << "ファイルを開くことができませんでした。" << std::endl;
        return;
    }

    for (const auto& data : dataList)
    {
        // 各メンバー変数を処理
        outFile.write(reinterpret_cast<const char*>(&data.id), sizeof(data.id));

        // 文字列の長さを書き込む
        size_t nameLength = data.name.size();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));

        // 文字列自体を書き込む
        outFile.write(data.name.c_str(), nameLength);
    }

    outFile.close();
    std::cout << "バイナリデータが " << filename << " ファイルに書き込まれました。" << std::endl;
}

template <typename T>
auto Load(const std::string& filename) -> std::vector<T>
{
    std::ifstream inFile(filename, std::ios::binary);
    std::vector<T> dataList;

    if (!inFile) {
        std::cerr << "ファイルが開けませんでした。" << std::endl;
        return dataList;
    }

    while (true) 
    {
        T data;

        // 各メンバー変数を読み込む
        if (!inFile.read(reinterpret_cast<char*>(&data.id), sizeof(data.id))) break;

        // 文字列の長さを読み込む
        size_t nameLength;
        if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;

        // 文字列自体を読み込む
        std::vector<char> nameBuffer(nameLength);
        inFile.read(nameBuffer.data(), nameLength);
        data.name.assign(nameBuffer.begin(), nameBuffer.end());

        dataList.push_back(data);
    }

    inFile.close();
    std::cout << "バイナリ形式のdatファイルを正常に読み込みました。" << std::endl;

    return dataList;
}


struct Data
{
    int id = 0;
    std::string name;
};

int main()
{
    // ファイル名
    const std::string filename = "output_binary.dat";

    // データを作成
    std::vector<Data> dataList =
    {
        {0, "こいし"},
        {1, "さとり"}
    };

    // バイナリデータを作成
    Create(filename, dataList);

    // バイナリデータを読み込み
    auto loadedDataList = Load<Data>(filename);

    // 読み込んだデータを表示
    for (const auto& data : loadedDataList)
    {
        std::cout << "ID: " << data.id << "\n";
        std::cout << "名前: " << data.name << "\n";
    }

    return 0;
}