#include "auxFiles/libraries.h"
#include "auxFiles/preprocess_functions.h"
#include "auxFiles/solutions.h"
#include "testFiles/timer.h"
#include "testFiles/test_functions.h"

#include <cstdio>
#include <fstream>
#include <sstream>

std::string decode(std::string code_str)
{
    int cur_cod = stoi(code_str.substr(0, 2), 0, 2) + 1;
    int pos = 2;
    std::string res = {};
    while (pos < code_str.length())
    {
        int cur_char = stoi(code_str.substr(pos, cost[cur_cod]), 0, 2);
        if (cur_char >= pow(2, cost[cur_cod]) - 1 - 2)
        {
            auto it = std::find(chageCode[cur_cod].begin(), chageCode[cur_cod].end(), code_str.substr(pos, cost[cur_cod]));
            pos += cost[cur_cod];
            cur_cod = static_cast<int>(it - chageCode[cur_cod].begin());
        }
        else
        {
            res += inverted_chars[cur_cod][cur_char];
            pos += cost[cur_cod];
        }
    }
    return res;
}

#define BYTE_SIZE 8

std::string readFile(const std::string &file)
{
    const std::string offset = "../files/input/";
    const std::string extension = "";

    std::ifstream inFile(offset + file + extension);
    if (!inFile.is_open())
    {
        std::cerr << "Error when opening input file" << std::endl;
        exit(-1);
    }

    std::string line;
    std::getline(inFile, line);
    return line;
}

void writeFile(const std::string &file, const std::string &minCode)
{
    const std::string offset = "../files/output/";
    const std::string extension = ".dat";
    std::ofstream outFile(offset + file + extension, std::ios::binary);
    if (!outFile.is_open())
    {
        std::cerr << "Error when writing in output file\n";
        exit(-1);
    }

    int pos = 0;
    {
        std::size_t size = minCode.size();
        outFile.write((char *)&size, sizeof(size));
    }
    while (pos < minCode.length())
    {
        auto byte_str = minCode.substr(pos, BYTE_SIZE);
        uint8_t hex = stoi(byte_str, nullptr, 2);

        outFile.write((char *)(&hex), sizeof(hex));
        pos += byte_str.size();
    }
    outFile.close();
}

void writeText(const std::string &code)
{
    const std::string offset = "../files/res/";
    const std::string extension = ".txt";
    std::ofstream outFile(offset + "res" + extension);

    if (!outFile.is_open())
    {
        std::cerr << "Error when writing text" << std::endl;
        exit(-1);
    }


    outFile<<code;
}

std::string decodeFile(const std::string &file)
{
    const std::string offset = "../files/output/";
    const std::string extension = ".dat";

    std::ifstream inFile(offset + file + extension, std::ios::binary);
    if (!inFile.is_open())
    {
        std::cerr << "Error when reading output file" << std::endl;
        exit(-1);
    }

    std::size_t size;
    inFile.read((char *)&size, sizeof(size));

    std::string res = {};
    for (int i = 0; i < size / BYTE_SIZE; ++i)
    {
        uint8_t hex;
        inFile.read((char *)(&hex), sizeof(hex));
        res += std::bitset<BYTE_SIZE>(hex).to_string();
    }

    if (size % BYTE_SIZE != 0)
    {
        uint8_t hex;
        inFile.read((char *)(&hex), sizeof(hex));
        hex <<= BYTE_SIZE - size % BYTE_SIZE;
        res += std::bitset<BYTE_SIZE>(hex).to_string().substr(0, size % BYTE_SIZE);
    }
    return res;
}

void writeHeuristic(const std::string &path){
    std::string codeStr = p1::minCod(readFile(path));
    writeFile(path,codeStr);
}

void writeDinamic(const std::string &path){
    std::string codeStr = p5::minCod(readFile(path));
    writeFile(path,codeStr);
}



void inputCod(const std::string &path){
    
    std::cout << "choose the codification method\n1)heuristic\n2)dinamic\n";
    int code_method = {};
    std::string codeStr = {};
    std::cin >> code_method;

    switch (code_method) {
        case 1:
        {
            writeHeuristic(path);
            break;
        }

        case 2:
        {
            writeDinamic(path);
            break;
        }
        default:
            std::cout<<"invalid codification method\n";
            return;
    }
}

void input()
{

    while (true)
    {
        std::cout << "Insert the wanted action\n1)Codify\n2)Decode\n3)exit\n";
        int option;
        std::cin >> option;
        if (option == 3)
            break;

        std::cout << "insert the file inside of files/: ";
        std::string path;
        std::cin >> path;

        switch (option)
        {
            case 1:
            {
                inputCod(path);
                break;
            }

            case 2:
            {
                std::string codeStr = decodeFile(path);
                std::cout<<"size of codification:"<<codeStr.size()<<'\n';
                writeText(decode(codeStr));

                // write decoded in a file res
                break;
            }
            default:{
                std::cout<<"insert a valid action \n";
                break;

            }
        }
    }
}

void test()
{
    std::vector<int> sizes{10,50,100,500};

    std::vector<double> resMem(sizes.size());
    std::vector<double> resDin(sizes.size());

    int i = 0;
    for (auto n : sizes)
    {
        std::string codify = randomEncode(n);

        Timer timeMem;
        std::string strMem = p1::minCod(codify);
        resMem[i] = timeMem.stop();

        assert(decode(strMem) == codify);

        Timer timerDin;
        std::string strDin = p5::minCod(codify);
        resDin[i] = timerDin.stop();
        assert(decode(strDin) == codify);
        i++;
    }
}


int main()
{
    preprocess();
    input();


    return 0;
}