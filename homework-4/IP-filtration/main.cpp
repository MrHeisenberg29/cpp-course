#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

std::vector<int> split_ip(const std::string& str)
{
    std::vector<int> result;
    result.reserve(4);
    size_t start = 0;
    size_t end = str.find('.');
    try
    { 
        while (end != std::string::npos)
        {
                result.push_back(boost::lexical_cast<int>(str.substr(start, end - start)));
                start = end + 1;
                end = str.find('.', start);
        }
        result.push_back(boost::lexical_cast<int>(str.substr(start)));
    }
    catch (const boost::bad_lexical_cast& e)
    {
        return {};
    }
   
    return result;
}

bool is_greater(const std::vector<int>& a, const std::vector<int>& b) 
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (a[i] > b[i]) return true;
        if (a[i] < b[i]) return false;
    }
    return false;
}

void quick_sort(std::vector<std::vector<int>>& arr, int low, int high) 
{
    if (low < high) 
    {
        std::vector<int> pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) 
        {
            if (is_greater(arr[j], pivot) || arr[j] == pivot) 
            {
                i++;
                std::vector<int> temp = std::move(arr[i]);
                arr[i] = std::move(arr[j]);
                arr[j] = std::move(temp);
            }
        }

        std::vector<int> temp = std::move(arr[i + 1]);
        arr[i + 1] = std::move(arr[high]);
        arr[high] = std::move(temp);
        int pi = i + 1;
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main() 
{
    std::vector<std::vector<int>> ip_pool;
    std::string line;

    while (std::getline(std::cin, line)) 
    {
        if (line.empty()) continue;
        size_t tab_pos = line.find('\t');
        if (tab_pos != std::string::npos) 
        {
            std::string ip_str = line.substr(0, tab_pos);
            std::vector<int> current_ip = split_ip(ip_str);
            ip_pool.push_back(std::move(current_ip));
        }
    }

    if (!ip_pool.empty())
    {
        quick_sort(ip_pool, 0, ip_pool.size() - 1);
    }

    for (size_t i = 0; i < ip_pool.size(); ++i)
    {
        const auto& ip = ip_pool[i];
        std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << "\n";
    }

    for (size_t i = 0; i < ip_pool.size(); ++i) 
    {
        const auto& ip = ip_pool[i];
        if (ip[0] == 1) 
        {
            std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << "\n";
        }
    }

    for (size_t i = 0; i < ip_pool.size(); ++i) 
    {
        const auto& ip = ip_pool[i];
        if (ip[0] == 46 && ip[1] == 70) 
        {
            std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << "\n";
        }
    }

    for (size_t i = 0; i < ip_pool.size(); ++i) 
    {
        const auto& ip = ip_pool[i];
        if (ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46) 
        {
            std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << "\n";
        }

    }

    return 0;
}